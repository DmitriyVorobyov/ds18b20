#include "stm8s_spi.h"

void Spi_Init(void)
{
  PC_DDR |= 0x20 | 0x40; //SCK; SDI(MOSI)
  PC_CR1 |= 0x20 | 0x40;
  PC_CR2 |= 0x20 | 0x40;
  
  PC_DDR &= ~0x80; //SDO(MISO)
  
  PG_DDR |= 0x02; //nSEL;
  PG_ODR |= 0x02; 
  PG_CR1 |= 0x02;
  PG_CR2 |= 0x02;

  SPI_CR1 &= ~(SPI_BR_BIT3 | SPI_BR_BIT4 | SPI_BR_BIT5); //fmaster/16
  
  SPI_CR1 &= ~SPI_CPOL;
  SPI_CR1 &= ~SPI_CPHA;
  
  SPI_CR2 &= ~SPI_SPILSBFIRST;
  
  SPI_CR2 |= SPI_SSM | SPI_SSI;
  
  SPI_CR1 |= SPI_MSTR;
  
  //SPI_ICR |= SPI_TXIE | SPI_RXIE;
}

void Spi_TransmitByte(uint8 adress, uint8 byte)
{
  adress |= 0x80;
  
  PG_ODR &= ~0x02;
  SPI_CR1 |= SPI_SPE;
  
  while(!(SPI_SR & SPI_TXE));
  SPI_DR = adress;
  
  while(!(SPI_SR & SPI_TXE));
  SPI_DR = byte;
  
  while(!(SPI_SR & SPI_RXNE));
  adress = SPI_DR;
 
  while(!(SPI_SR & SPI_RXNE));
  adress = SPI_DR;
  
  while(!(SPI_SR & SPI_TXE) && (SPI_SR & SPI_BSY));
  
  SPI_CR1 &= ~SPI_SPE;
  PG_ODR |= 0x02;
}

uint8 Spi_ReceiveByte(uint8 adress)
{
  uint8 data;
  
  PG_ODR &= ~0x02;
  SPI_CR1 |= SPI_SPE;
  
  while(!(SPI_SR & SPI_TXE));
  SPI_DR = adress;
  
  while(!(SPI_SR & SPI_TXE));
  SPI_DR = data;
  
  while(!(SPI_SR & SPI_RXNE));
  data = SPI_DR;
  
  while(!(SPI_SR & SPI_RXNE));
  data = SPI_DR;
  
  while(!(SPI_SR & SPI_TXE) && (SPI_SR & SPI_BSY));
  
  SPI_CR1 &= ~SPI_SPE;
  PG_ODR |= 0x02;
  
  return data;
}

void Spi_BurstReceive(uint8 *buffer, uint8 buffersize)
{
  uint8 i;
  
  PG_ODR &= ~0x02;
  SPI_CR1 |= SPI_SPE;
  SPI_DR = buffer[0];
  
  while(!(SPI_SR & SPI_TXE));
  SPI_DR = buffer[0];
  while(!(SPI_SR & SPI_RXNE));
  buffer[0] = SPI_DR;
  
  buffersize--;
  
  for(i=0;i<buffersize;i++) {
    while(!(SPI_SR & SPI_TXE));
    SPI_DR = buffer[i];
    while(!(SPI_SR & SPI_RXNE));
    buffer[i] = SPI_DR;
  }
  
  while(!(SPI_SR & SPI_RXNE));
  buffer[buffersize] = SPI_DR;

  SPI_CR1 &= ~SPI_SPE;
  PG_ODR |= 0x02;
}

void Spi_BurstTransmit(uint8 *buffer, uint8 buffersize)
{
  buffer[0] |= 0x80;
  Spi_BurstReceive(buffer,buffersize);
}