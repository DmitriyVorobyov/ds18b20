#include "eight-segment_display.h"

//PB
//PA(3,4,5,6)

//          a
//         ---
//      f | g | b
//         ---
//      e |   | c
//         ---  _
//          d   h

//ESD_SEGMENTS[8] = {a, b, c, d, e, f, g, h}
uint8 esd_segments[8] = {0x80, 0x08, 0x02, 0x01, 0x04, 0x20, 0x40, 0x10};
uint8 esd_symbols[12] = {0x3F, //0
                           0x06, //1
                           0x5B, //2
                           0x4F, //3
                           0x66, //4
                           0x6D, //5
                           0x7D, //6
                           0x07, //7
                           0x7F, //8
                           0x6F, //9
                           0x40, //-
                           0x3D  //E
};

void Esd_Init(void)
{
  PB_DDR = 0xff;
  PB_CR1 = 0xff;
  PA_DDR |= 0x78;
  PA_CR1 |= 0x78;
}

uint8 haha(uint8 symbol)
{
  uint8 new_symbol = 0;
  for(int i=0;i<8;i++) {
    if(symbol & 0x01) new_symbol |= esd_segments[i];
    symbol >>= 1;
  }
  
  return new_symbol;
}

void Esd_DisplaySymbol(uint8 symbol)
{
  if(symbol>47 && symbol<58)
    PB_ODR = haha(esd_symbols[symbol-48]);
  else if(symbol == '-')
    PB_ODR = haha(esd_symbols[10]);
  else if(symbol == '.') 
    PB_ODR = esd_segments[7];
  else PB_ODR = haha(esd_symbols[11]); 
}

void Esd_DisplayString(uint8 *s)
{
  /*
  if(s[0] == 0) {
    Esd_DisplaySymbol('E');
    return;
  }*/
  
  uint8 i = 1, j = 0x08;
  while(s[i] != '\n') i++;
  //if(i>4) i = 3;
  //else i--;
  i--;
  
  while(i != 0xff) {
    Esd_DisplaySymbol(s[i]);
    PA_ODR &= ~j;
    PA_ODR |= j;
    j <<= 1;
    i--;
  }
}