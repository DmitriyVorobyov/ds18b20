#include "stm8s.h"
#include "delay.h"

//
#define F_CPU_MHz                       16
#define OW_DDR                          PC_DDR
#define OW_ODR                          PC_ODR
#define OW_IDR                          PC_IDR
#define OW_CR1                          PC_CR1
#define OW_CR2                          PC_CR2
#define OW_BUSMASK                      0x10

//One Wire Commands
#define OW_CMD_SEARCHROM                0xF0
#define OW_CMD_READROM                  0x33
#define OW_CMD_MATCHROM                 0x55
#define OW_CMD_SKIPROM                  0xCC

/*
void _ow_high(void);
void _ow_low(void);
void _ow_input_mode(void);
void _ow_output_mode(void);
*/

//OneWire
void OW_InitBus(void);
uint8 OW_Reset(void);
void OW_WriteByte(uint8 byte);
uint8 OW_ReadByte(void);

