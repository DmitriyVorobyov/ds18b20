#include "stm8s_spi.h"

//
#define RFM22_REG_00_DEVICE_TYPE                                      0x00
#define RFM22_REG_01_DEVICE_VERSION                                   0x01
#define RFM22_REG_02_DEVICE_STATUS                                    0x02

//Interrupt Registers
#define RFM22_REG_03_INTERRUPT_STATUS_1                               0x03
#define RFM22_REG_04_INTERRUPT_STATUS_2                               0x04
#define RFM22_REG_05_INTERRUPT_ENABLE_1                               0x05
#define RFM22_REG_06_INTERRUPT_ENABLE_2                               0x06

//
#define RFM22_REG_07_OPERATING_And_FUNCTION_CONTROL_1                 0x07
#define RFM22_REG_08_OPERATING_And_FUNCTION_CONTROL_2                 0x08
#define RFM22_REG_09_CRYSTAL_OSCILLATOR_LOAD_CAPACITANCE              0x09
#define RFM22_REG_0A_MICROCONTROLLER_OUTPUT_CLOCK                     0x0A
#define RFM22_REG_0B_GPIO0_CONFIGURATION                              0x0B
#define RFM22_REG_0C_GPIO1_CONFIGURATION                              0x0C
#define RFM22_REG_0D_GPIO2_CONFIGURATION                              0x0D
#define RFM22_REG_0E_IO_PORT_CONFIGURATION                            0x0E
#define RFM22_REG_0F_ADC_CONGIGURATION                                0x0F
#define RFM22_REG_10_ADC_SENSOR_AMPLIFIER_OFFSET                      0x10
#define RFM22_REG_11_ADC_VALUE                                        0x11
#define RFM22_REG_12_TEMPERATURE_SENSOR_CONTROL                       0x12
#define RFM22_REG_13_TEMPERATURE_VALUE_OFFSET                         0x13
#define RFM22_REG_14_WAKE_UP_TIMER_PERIOD_1                           0x14
#define RFM22_REG_15_WAKE_UP_TIMER_PERIOD_2                           0x15
#define RFM22_REG_16_WAKE_UP_TIMER_PERIOD_3                           0x16
#define RFM22_REG_17_WAKE_UP_TIMER_VALUE_1                            0x17
#define RFM22_REG_18_WAKE_UP_TIMER_VALUE_2                            0x18
#define RFM22_REG_19_LOW_DUTY_CYCLE_MODE_DURATION                     0x19
#define RFM22_REG_1A_LOW_BATTERY_DETECTOR_THRESHOLD                   0x1A
#define RFM22_REG_1B_BATTERY_VOLTAGE_LEVEL                            0x1B
#define RFM22_REG_1C_IF_FILTER_BANDWIDTH                              0x1C
#define RFM22_REG_1D_AFC_LOOP_GEARSHIFT_OVERRIDE                      0x1D
#define RFM22_REG_1E_AFC_TIMING_CONTROL                               0x1E
#define RFM22_REG_1F_CLOCK_RECOVERY_GEARSHIFT_OVERRIDE                0x1F
#define RFM22_REG_20_CLOCK_RECOVERY_OVERSAMPLING_RATIO                0x20
#define RFM22_REG_21_CLOCK_RECOVERY_OFFSET_2                          0x21
#define RFM22_REG_22_CLOCK_RECOVERY_OFFSET_1                          0x22
#define RFM22_REG_23_CLOCK_RECOVERY_OFFSET_0                          0x23
#define RFM22_REG_24_CLOCK_RECOVERY_TIMING_LOOP_GAIN_1                0x24
#define RFM22_REG_25_CLOCK_RECOVERY_TIMING_LOOP_GAIN_0                0x25
#define RFM22_REG_26_RECEIVED_SIGNAL_STRENGTH_INDICATOR               0x26
#define RFM22_REG_27_RSSI_THRESHOLD_FOR_CLEAR_CHANNEL_INDICATOR       0x27
#define RFM22_REG_28_ANTENNA_DIVERSITY_REGISTER_1                     0x28
#define RFM22_REG_29_ANTENNA_DIVERSITY_REGISTER_2                     0x29

//Packet Handler Registers
#define RFM22_REG_30_DATA_ACCESS_CONTROL                              0x30
#define RFM22_REG_31_EZMAC_STATUS                                     0x31
#define RFM22_REG_32_HEADER_CONTROL_1                                 0x32
#define RFM22_REG_33_HEADER_CONTROL_2                                 0x33
#define RFM22_REG_34_PREAMBLE_LENGTH                                  0x34
#define RFM22_REG_36_SYNC_WORD_3                                      0x36
#define RFM22_REG_37_SYNC_WORD_2                                      0x37
#define RFM22_REG_38_SYNC_WORD_1                                      0x38
#define RFM22_REG_39_SYNC_WORD_0                                      0x39
#define RFM22_REG_3A_TRANSMIT_HEADER_3                                0x3A
#define RFM22_REG_3B_TRANSMIT_HEADER_2                                0x3B
#define RFM22_REG_3C_TRANSMIT_HEADER_1                                0x3C
#define RFM22_REG_3D_TRANSMIT_HEADER_0                                0x3D
#define RFM22_REG_3E_TRANSMIT_PACKET_LENGTH                           0x3E
#define RFM22_REG_3F_CHECK_HEADER_3                                   0x3F
#define RFM22_REG_40_CHECK_HEADER_2                                   0x40
#define RFM22_REG_41_CHECK_HEADER_1                                   0x41
#define RFM22_REG_42_CHECK_HEADER_0                                   0x42
#define RFM22_REG_43_HEADER_ENABLE_3                                  0x43
#define RFM22_REG_44_HEADER_ENABLE_2                                  0x44
#define RFM22_REG_45_HEADER_ENABLE_1                                  0x45
#define RFM22_REG_46_HEADER_ENABLE_0                                  0x46
#define RFM22_REG_47_RECEIVED_HEADER_3                                0x47
#define RFM22_REG_48_RECEIVED_HEADER_2                                0x48
#define RFM22_REG_49_RECEIVED_HEADER_1                                0x49
#define RFM22_REG_4A_RECEIVED_HEADER_0                                0x4A
#define RFM22_REG_4B_RECEIVED_PACKET_LENGTH                           0x4B


#define RFM22_REG_50_ANALOG_TEST_BUS                                  0x50
#define RFM22_REG_51_DIGITAL_TEST_BUS                                 0x51
#define RFM22_REG_52_TX_RAMP_CONTROL                                  0x52
#define RFM22_REG_53_PLL_TUNE_TIME                                    0x53
#define RFM22_REG_55_CALIBRATION_CONTROL                              0x55
#define RFM22_REG_56_MODEM_TEST                                       0x56
#define RFM22_REG_57_CHARGEPUMP_TEST                                  0x57
#define RFM22_REG_58_CHARGEPUMP_CURRENT_TRIMMING_OVERRIDE             0x58
#define RFM22_REG_59_DIVIDER_CURRENT_TRIMMING                         0x59
#define RFM22_REG_5A_VCO_CURRENT_TRIMMING                             0x5A
#define RFM22_REG_5B_VCO_CALIBRATION_OVERRIDE                         0x5B
#define RFM22_REG_5C_SYNTHESIZER_TEST                                 0x5C
#define RFM22_REG_5D_BLOCK_ENABLE_OVERRIDE_1                          0x5D
#define RFM22_REG_5E_BLOCK_ENABLE_OVERRIDE_2                          0x5E
#define RFM22_REG_5F_BLOCK_ENABLE_OVERRIDE_3                          0x5F


#define RFM22_REG_60_CHANNEL_FILTER_COEFFICIENT_ADDRESS               0x60
#define RFM22_REG_61_CHANNEL_FILTER_COEFFICIENT_VALUE                 0x61
#define RFM22_REG_62_CRYSTAL_OSCILLATOR_CONTROL_TEST                  0x62
#define RFM22_REG_63_RC_OSCILLATOR_COARSE_CALIBRATION_OVERRIDE        0x63
#define RFM22_REG_64_RC_OSCILLATOR_FINE_CALIBRATION_OVERRIDE          0x64
#define RFM22_REG_65_LDO_CONTROL_OVERRIDE                             0x65
#define RFM22_REG_66_LDO_LEVEL_SETTING                                0x66
#define RFM22_REG_67_DELTASIGMA_ADC_TUNING_1                          0x67
#define RFM22_REG_68_DELTASIGMA_ADC_TUNING_2                          0x68

#define RFM22_REG_69_AGC_OVERRIDE_1                                   0x69
#define RFM22_REG_6A_AGC_OVERRIDE_2                                   0x6A
#define RFM22_REG_6B_GFSK_FIR_FILTER_COEFFICIENT_ADDRESS              0x6B
#define RFM22_REG_6C_GFSK_FIR_FILTER_COEFFICIENT_VALUE                0x6C
#define RFM22_REG_6D_TX_POWER                                         0x6D
#define RFM22_REG_6E_TX_DATA_RATE_1                                   0x6E
#define RFM22_REG_6F_TX_DATA_RATE_0                                   0x6F
#define RFM22_REG_70_MODULATION_MODE_CONTROL_1                        0x70
#define RFM22_REG_71_MODULATION_MODE_CONTROL_2                        0x71
#define RFM22_REG_72_FREQUENCY_DEVIATION                              0x72
#define RFM22_REG_73_FREQUENCY_OFFSET_1                               0x73
#define RFM22_REG_74_FREQUENCY_OFFSET_2                               0x74
#define RFM22_REG_75_FREQUENCY_BAND_SELECT                            0x75
#define RFM22_REG_76_NORMINAL_CARRIER_FREQUENCY_1                     0x76
#define RFM22_REG_77_NORMINAL_CARRIER_FREQUENCY_0                     0x77
#define RFM22_REG_79_FREQUENCY_HOPPING_CHANNEL_SELECT                 0x79
#define RFM22_REG_7A_FREQUENCY_HOPPING_STEP_SIZE                      0x7A
#define RFM22_REG_7C_TX_FIFO_CONTROL_1                                0x7C
#define RFM22_REG_7D_TX_FIFO_CONTROL_2                                0x7D
#define RFM22_REG_7E_RX_FIFO_CONTROL                                  0x7E
#define RFM22_REG_7F_FIFO_ACCESS                                      0x7F

void RFM22_Init(void);
void RFM22_TransmitByte(uint8 byte);
uint8 RFM22_ReceiveByte(void);