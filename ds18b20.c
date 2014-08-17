#include "ds18b20.h"

//////////////////////////////////////////
uint8 temp_bytes[8];
uint8 wait_ms;
//////////////////////////////////////////

void Therm_Init(void)
{
  OW_InitBus();
  
  OW_Reset();
  OW_WriteByte(OW_CMD_SKIPROM);
  OW_WriteByte(0);
  OW_WriteByte(0);
  OW_WriteByte(THERM_MODE_9BIT);
  wait_ms = 100;  //9 bits - 100 ms
                  //10 bits - 200 ms
                  //11 bits - 400 ms
                  //12 bits - 800 ms
}

/*
void Therm_ReadRom(uint8_t *bytes)
{
  asm("sim\n");
  
  uint8_t i = 0xff, j;
  
  i = OW_Reset();
  if(!i) {
    OW_WriteByte(OW_CMD_READROM);
  
    for(j=0;j<8;j++)
      bytes[j] = OW_ReadByte();
  }
  
  asm("rim\n");
}*/

void Therm_ConvertTemp()
{
  asm("sim\n");
  
  uint8 i = 0xff;
  uint16 j = wait_ms;
  i = OW_Reset();
  if(!i) {
    OW_WriteByte(OW_CMD_SKIPROM);
    OW_WriteByte(THERM_CMD_CONVERTTEMP);
    
    while(--j) Delay_us(1000);
    _ow_input_mode();
    while(!(OW_IDR & OW_BUSMASK));
  }
}

void Therm_ReadScratchpad()
{
  asm("sim\n");
  
  uint8 i = OW_Reset();
  if(!i) {
    OW_WriteByte(OW_CMD_SKIPROM);
    OW_WriteByte(THERM_CMD_RSCRATCHPAD);
    
    for(i=0;i<9;i++)
      temp_bytes[i] = OW_ReadByte();
  }
  
  asm("rim\n");
}

int8 Temperature()
{
  temp_bytes[1] = (temp_bytes[1] << 4) | (temp_bytes[0] >> 4);
  temp_bytes[0] &= 0x15;
  
  if(temp_bytes[1] & 0x80) {
    temp_bytes[1] = ~temp_bytes[1]; 
    temp_bytes[1]++; 
    temp_bytes[1] |= 0x80;
  }
  
  return (temp_bytes[1]);
}