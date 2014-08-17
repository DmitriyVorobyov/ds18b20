#include "stm8s_uart2.h"

void Uart2_Init(void)
{
  PD_DDR |= 0x20;  //pin PD5 - Tx
  PD_DDR &= ~0x40; //pin PD6 - Rx
  
  PD_CR1 |= 0x20;
  PD_CR2 &= ~0x20;
  PD_CR1 |= 0x40;
  PD_CR2 &= ~0x40;
  
  UART2_CR1 &= ~(UART2_M | UART2_PCEN);
  
  UART2_CR2 |= UART2_TEN | UART2_REN | UART2_RIEN;
  
  UART2_BRR2 = 0x03;  //9600 baud rate
  UART2_BRR1 = 0x68;
}

void Uart2_TransmitByte(uint8 byte)
{
  while(!(UART2_SR & UART2_TXE));
  UART2_DR = byte;
}

void Uart2_TransmitString(uint8 *string)
{
  uint8 i=0;
  while(string[i] != 0x00) {
    Uart2_TransmitByte(string[i]);
    i++;
  }
}