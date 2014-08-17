#include "stm8s_clk.h"

void Clk_Init(void)
{
  CLK_CKDIVR = 0;
  CLK_SWCR |= CLK_SWEN;
  CLK_SWR = 0xb4;
  while(!(CLK_SWCR & CLK_SWIF));
  CLK_SWCR &= ~CLK_SWIF;
}