#include "stm8s_one-wire.h"

//Thermometer commands
#define THERM_CMD_CONVERTTEMP           0x44
#define THERM_CMD_WSCRATCHPAD           0x4E
#define THERM_CMD_RSCRATCHPAD           0xBE
#define THERM_CMD_COPYSCRATCHPAD        0x48

//Thermometer mode
#define THERM_MODE_9BIT                 0x1F
#define THERM_MODE_10BIT                0x3F
#define THERM_MODE_11BIT                0x5F
#define THERM_MODE_12BIT                0x7F

//Thermometer functions
void Therm_Init(void);
/*
void Therm_ReadRom(uint8_t *bytes);        //Размер массива bytes - 8 байт
*/
void Therm_ReadScratchpad();
int8 Temperature();