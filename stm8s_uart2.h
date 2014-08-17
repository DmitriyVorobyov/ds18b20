#include "stm8s.h"

//UASRT2_SR
#define UART2_TXE               0x80  //1 - data is transferred to the shift register
#define UART2_TC                0x40  //1 - transmission is complete
#define UART2_RXNE              0x20  //1 - received data is ready to be read

//USART2_CR1
#define UART2_M                 0x10  //word length(0 - 8 data bits; 1 - 9 data bits)
#define UART2_PCEN              0x04  //parity control bit (0 - disable; 1 - enable)

//UART2_CR2
#define UART2_RIEN              0x20  //received interrupt enable (0 - interrupt is inhibited;
                                      //1 - interrupt generated if OR=1 or RXNE=1 in the UART2_SR register
#define UART2_TEN               0x08  //transmitter enable
#define UART2_REN               0x04  //receiver enable

//UART2_CR3
#define UART2_STOP_BIT5         0x20  //00 - one stop bit; 01 - reserved;
#define UART2_STOP_BIT4         0x10  //10 - two stop bits; 11 - 1.5 stop bits

void Uart2_Init(void);
void Uart2_TransmitByte(uint8 byte);
void Uart2_TransmitString(uint8 *string);
