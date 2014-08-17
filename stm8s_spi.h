#include "stm8s.h"

//SPI_CR1
#define SPI_SPILSBFIRST         0x80 //1 - LSB is transmitted first
#define SPI_SPE                 0x40 //1 - Peripheral enable
#define SPI_BR_BIT5             0x20 //baud rate control
#define SPI_BR_BIT4             0x10 
#define SPI_BR_BIT3             0x08
#define SPI_MSTR                0x04 //1 - master configuration
#define SPI_CPOL                0x02 //Clock polarity; 1 - SCK to 1 when idle; 0 SCK to 0 whe idle
#define SPI_CPHA                0x01 //Clock phase;

//SPI_CR2
#define SPI_BDM                 0x80 //Bidirectional data mod selected
                                     //0 - 2-line unidirectional data mod selected
                                     //1 - 1-line bidirectional data mod selected
#define SPI_BDOE                0x40 //Select the direction of transfer in bidirectional mod when BDM = 1
#define SPI_CRCEN               0x20 
#define SPI_CRCNEXT             0x10 
#define SPI_RXONLY              0x04 
#define SPI_SSM                 0x02 //1 - software slave management enable
#define SPI_SSI                 0x01 //Internal slave select; 1 - master mode

//SPI_ICR
#define SPI_TXIE                0x80 //Tx buffer empty interrupt enable; 1 - interrupt not masked
#define SPI_RXIE                0x40 //RX buffer not empty interrupt enable; 1 -interrupt not masked
#define SPI_ERRIE               0x20 //1 - Error interrupt is enable(CRCERR, OVR, MODF)
#define SPI_WKIE                0x10 //1 - Wakeup interrupt enable

//SPI_SR
#define SPI_BSY                 0x80 //1 - SPI is busy in communications; This flag is set and reset by hardware
#define SPI_OVR                 0x40 //1 - Overrun occurred; This flag is set by hardware and reset by a software sequence
#define SPI_MODF                0x20 //1 - Mode fault occurred; This flag is set by hardware and reset by a software sequence
#define SPI_CRCERR              0x10 //1 - CRC value received does not match the SPI_RXCRCR value;
                                     //This flag is set by hardware and cleared by software writing 0
#define SPI_WKUP                0x08 //1 - Wakeup event occurred
#define SPI_TXE                 0x02 //1 - transmit buffer empty
#define SPI_RXNE                0x01 //1 - receive buffer not empty

void Spi_Init(void);
void Spi_TransmitByte(uint8 adress, uint8 byte);
uint8 Spi_ReceiveByte(uint8 adress);
void Spi_BurstReceive(uint8 *buffer, uint8 buffersize);
void Spi_BurstTransmit(uint8 *buffer, uint8 buffersize);