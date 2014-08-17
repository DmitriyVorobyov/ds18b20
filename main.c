#include "stm8s.h"
#include "stm8s_uart2.h"
#include "stm8s_spi.h"
#include "eight-segment_display.h"
#include "ds18b20.h"
#include "rfm22.h"

/////////////////////////////////
int8 temp = 0;
uint8 dtemp[5];
uint8 byte;

uint8 max_command_size = 255;
uint8 N = 0; 
uint8 command[256];

////////////////////////////////
void DTemp(int8 temp);
////////////////////////////////

int main( void )
{ 
  Clk_Init();
  Spi_Init();
  RFM22_Init();
  
  
  /*
  //enable packet sent and valid packet received interrupts
  Spi_TransmitByte(RFM22_REG_05_INTERRUPT_ENABLE_1,0x06);
  //enable valid preamble detected and sync word detected interrupts
  Spi_TransmitByte(RFM22_REG_06_INTERRUPT_ENABLE_2,0x00);
  Spi_TransmitByte(0x0B,0x1D);
  Spi_TransmitByte(0x0C,0x1F);
  while(1) {
    RFM22_TransmitByte('a');
  }*/
  
  
  Spi_TransmitByte(0x0B,0x1F);
  Spi_TransmitByte(0x0C,0x1D);
  Spi_TransmitByte(RFM22_REG_07_OPERATING_And_FUNCTION_CONTROL_1,0x04);
  while(1) {
    if(!(PC_IDR & 0x10)) {
      byte = Spi_ReceiveByte(0x7F);
      byte = Spi_ReceiveByte(RFM22_REG_03_INTERRUPT_STATUS_1);
      byte = Spi_ReceiveByte(RFM22_REG_04_INTERRUPT_STATUS_2);
      Spi_TransmitByte(RFM22_REG_07_OPERATING_And_FUNCTION_CONTROL_1,0x04);
    }
  }

  
  asm("rim\n");
  while(1) {
  }
}

void DTemp(int8 temp)
{
  uint8 i = 0;
  if(temp & 0x80) dtemp[i] = '-';
  else dtemp[i] = '+';
  temp &= ~0x80;
  
  if(temp == 0x00) {
    dtemp[0] = 48;
    dtemp[1] = 0;
    return;
  }
  i++;
  
  dtemp[i] = temp/100 + 48;
  temp %= 100;
  if(dtemp[i] != 48) i++;
  
  dtemp[i] = temp/10 + 48;
  if((dtemp[i] != 48) || (i == 2)) i++;
  
  dtemp[i] = temp%10 + 48;
  i++;
  
  dtemp[i] = 0x00;
}

uint8 cmpcommand(uint8 *str)
{
  uint8 i=0;
  while(!(command[i] ^ str[i]) && (i < max_command_size)) i++;
  if(command[i] || str[i]) return 1;
  return 0;
}

void Uart_Commands()
{
  asm("sim\n");
  if(!cmpcommand("readtemp")){
    Therm_ConvertTemp();
    Therm_ReadScratchpad();
    temp = Temperature();
    DTemp(temp);
    Uart2_TransmitString("Temperature: ");
    Uart2_TransmitString(dtemp);
    Uart2_TransmitByte('\n');
  }
  asm("rim\n");
}

#pragma vector = 23
__interrupt void UART2_RXFULL(void)
{
  command[N] = UART2_DR;
  if(command[N] == '\r') {
    command[N] = 0;
    Uart_Commands();
    N = 0;
  }
  else N++;
  
  UART2_SR &= ~UART2_RXNE;
}