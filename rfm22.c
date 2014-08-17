#include "rfm22.h"

uint8 buffer[256];
uint8 buffersize;
uint8 abc;

void RFM22_Init(void)
{
  //enable packet sent and valid packet received interrupts
  Spi_TransmitByte(RFM22_REG_05_INTERRUPT_ENABLE_1,0x0E);
  //enable valid preamble detected and sync word detected interrupts
  Spi_TransmitByte(RFM22_REG_06_INTERRUPT_ENABLE_2,0x80);
  
  Spi_TransmitByte(RFM22_REG_07_OPERATING_And_FUNCTION_CONTROL_1,0x01);
  
  Spi_TransmitByte(RFM22_REG_1C_IF_FILTER_BANDWIDTH,0xAD);
  Spi_TransmitByte(RFM22_REG_1D_AFC_LOOP_GEARSHIFT_OVERRIDE,0x40);
  
  Spi_TransmitByte(RFM22_REG_20_CLOCK_RECOVERY_OVERSAMPLING_RATIO,0x4B);
  Spi_TransmitByte(RFM22_REG_21_CLOCK_RECOVERY_OFFSET_2,0x01);
  Spi_TransmitByte(RFM22_REG_22_CLOCK_RECOVERY_OFFSET_1,0xB4);
  Spi_TransmitByte(RFM22_REG_23_CLOCK_RECOVERY_OFFSET_0,0xE8);
  Spi_TransmitByte(RFM22_REG_24_CLOCK_RECOVERY_TIMING_LOOP_GAIN_1,0x02);
  Spi_TransmitByte(RFM22_REG_25_CLOCK_RECOVERY_TIMING_LOOP_GAIN_0,0xBD);
  Spi_TransmitByte(0x2A,0x2C);
  Spi_TransmitByte(0x2C,0x28);
  Spi_TransmitByte(0x2D,0x1F);
  Spi_TransmitByte(0x2E,0x29);
  
  Spi_TransmitByte(RFM22_REG_30_DATA_ACCESS_CONTROL,0xAC);
  Spi_TransmitByte(RFM22_REG_32_HEADER_CONTROL_1,0x00);
  Spi_TransmitByte(RFM22_REG_33_HEADER_CONTROL_2,0x42);
  
  Spi_TransmitByte(RFM22_REG_34_PREAMBLE_LENGTH,0x08);
  Spi_TransmitByte(0x35,0x2A);
  Spi_TransmitByte(RFM22_REG_36_SYNC_WORD_3,0x2D);
  Spi_TransmitByte(RFM22_REG_37_SYNC_WORD_2,0xD4);
  Spi_TransmitByte(RFM22_REG_38_SYNC_WORD_1,0x00);
  Spi_TransmitByte(RFM22_REG_39_SYNC_WORD_0,0x00);
  Spi_TransmitByte(0x3A,0x05);
  Spi_TransmitByte(0x3B,0x99);
  Spi_TransmitByte(0x3C,0xB6);
  Spi_TransmitByte(0x3D,0x06);
  Spi_TransmitByte(0x3E,0x01);
  Spi_TransmitByte(0x3F,0x05);
  Spi_TransmitByte(0x40,0x99);
  Spi_TransmitByte(0x41,0xB6);
  Spi_TransmitByte(0x42,0x06);
  Spi_TransmitByte(0x43,0xFF);
  Spi_TransmitByte(0x44,0xFF);
  Spi_TransmitByte(0x45,0xFF);
  Spi_TransmitByte(0x46,0xFF);
  
  Spi_TransmitByte(RFM22_REG_6E_TX_DATA_RATE_1,0x0A);
  Spi_TransmitByte(RFM22_REG_6F_TX_DATA_RATE_0,0x3D);
  
  Spi_TransmitByte(RFM22_REG_70_MODULATION_MODE_CONTROL_1,0x0C);
  Spi_TransmitByte(RFM22_REG_71_MODULATION_MODE_CONTROL_2,0x23);
  Spi_TransmitByte(RFM22_REG_72_FREQUENCY_DEVIATION,0x50);
  
  //carrier frequency settings
  Spi_TransmitByte(RFM22_REG_75_FREQUENCY_BAND_SELECT,0x53);
  Spi_TransmitByte(RFM22_REG_76_NORMINAL_CARRIER_FREQUENCY_1,0x4B);
  Spi_TransmitByte(RFM22_REG_77_NORMINAL_CARRIER_FREQUENCY_0,0x00);
}

void RFM22_TransmitByte(uint8 byte)
{ 
  Spi_TransmitByte(RFM22_REG_7F_FIFO_ACCESS, byte);
  Spi_TransmitByte(RFM22_REG_07_OPERATING_And_FUNCTION_CONTROL_1,0x09);
  
  while(PC_IDR & 0x10);
  abc = Spi_ReceiveByte(RFM22_REG_03_INTERRUPT_STATUS_1);
  abc = Spi_ReceiveByte(RFM22_REG_04_INTERRUPT_STATUS_2);
}

uint8 RFM22_ReceiveByte(void)
{
}