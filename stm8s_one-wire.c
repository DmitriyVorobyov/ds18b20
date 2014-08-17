#include "stm8s_one-wire.h" 

void _ow_high(void)
{
  OW_ODR |= (uint8)OW_BUSMASK;
}

void _ow_low(void)
{
  OW_ODR &= (uint8)(~OW_BUSMASK);
}

void _ow_input_mode(void)
{
  OW_DDR &= (uint8)(~OW_BUSMASK);
}

void _ow_output_mode(void)
{
  OW_DDR |= (uint8)OW_BUSMASK;
}

void OW_InitBus(void)
{
  OW_CR1 |= OW_BUSMASK;
  OW_CR2 &= ~OW_BUSMASK;
  Delay_Init();
}

uint8 OW_Reset(void)
{
  uint8 i = 0xff;
  
  _ow_output_mode();
  _ow_low();
  
  Delay_us(480);
  
  _ow_input_mode();
  Delay_us(60);
  
  i = (OW_IDR & OW_BUSMASK);
  
  Delay_us(480);
  
  return i;
}

void OW_WriteByte(uint8 byte)
{
  uint8 i=0;
  while(i<8) {
    _ow_output_mode();
    _ow_low();
    Delay_1us(1);
    
    if(byte & 0x01) _ow_input_mode();
    Delay_us(60);
    _ow_input_mode();
    byte >>= 1;
    i++;
    Delay_1us(1);
  }
}

uint8 OW_ReadByte(void)
{
  uint8 i=0, byte=0x00;
  while(i<8) {
    _ow_output_mode();
    _ow_low();
    Delay_1us(1);
    
    _ow_input_mode();
    Delay_us(15);
    if(OW_IDR & OW_BUSMASK) byte |= 1<<i;
    Delay_us(45);
    i++;
    Delay_1us(1);
  }
  return byte;
}