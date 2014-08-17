#include "stm8s.h"

//CLK_ICKR (Internal clock register)
#define CLK_REGAN               0x20
#define CLK_LSIRDY              0x10
#define CLK_LSIEN               0x08
#define CLK_FHW                 0x04
#define CLK_HSIRDY              0x02
#define CLK_HSIEN               0x01

//CLK_ECKR (External clock register)
#define CLK_HSERDY              0x02
#define CLK_HSEEN               0x01

//CLK_CMSR (Clock master status register)
//0xE1 - HSI selected as master clock sourse
//0xD2 - LSI selected as master clock sourse
//0xB4 - HSE selected as master clock sourse

//CLK_SWR (Clock master switch register)
//0xE1 - HSI selected as master clock sourse
//0xD2 - LSI selected as master clock sourse
//0xB4 - HSE selected as master clock sourse

//CLK_SWCR (Switch control register)
#define CLK_SWIF                0x08
#define CLK_SWIEN               0x04
#define CLK_SWEN                0x02
#define CLK_SWBSY               0x01

//CLK_CKDIVR (Clock divider register)
#define CLK_HSIDIV_BIT1         0x10
#define CLK_HSIDIV_BIT0         0x08
#define CLK_CPUDIV_BIT2         0x04
#define CLK_CPUDIV_BIT1         0x02
#define CLK_CPUDIV_BIT0         0x01

//CLK_PCKENR1 (Peripheral clock gating register 1)
//CLK_PCKENR2 (Peripheral clock gating register 2)
//CLK_CSSR (Clock security system register)
//CLK_CCOR (Configurable clock output register)
//CLK_CANCCR (CAN external clock control register)
//CLK_HSITRIMR (HSI clock calibration trimming register)
//CLK_SWIMCCR (SWIM clock control register)

void Clk_Init(void);