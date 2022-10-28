#ifndef ADC_INT_H
#define ADC_INT_H

#define ADC_CHANNEL_0       0
#define ADC_CHANNEL_1       1
#define ADC_CHANNEL_2       2
#define ADC_CHANNEL_3       3
#define ADC_CHANNEL_4       4
#define ADC_CHANNEL_5       5
#define ADC_CHANNEL_6       6
#define ADC_CHANNEL_7       7
#define ADC_CH0_CH0_G10X    8
#define ADC_CH1_CH0_G10X    9
#define ADC_CH0_CH0_G200X   10
#define ADC_CH1_CH0_G200X   11
#define ADC_CH2_CH2_G10X    12
#define ADC_CH3_CH2_G10X    13
#define ADC_CH2_CH2_G200X   14
#define ADC_CH3_CH2_G200X   15
#define ADC_CH0_CH1_G1X     16
#define ADC_CH1_CH1_G1X     17
#define ADC_CH2_CH1_G1X     18
#define ADC_CH3_CH1_G1X     19
#define ADC_CH4_CH1_G1X     20
#define ADC_CH5_CH1_G1X     21
#define ADC_CH6_CH1_G1X     22
#define ADC_CH7_CH1_G1X     23
#define ADC_CH1_CH2_G1X     24
#define ADC_CH2_CH2_G1X     25
#define ADC_CH3_CH2_G1X     26
#define ADC_CH4_CH2_G1X     27


void ADC_voidInit(void);

void ADC_voidStartConversion(uint8 u8ChannelNumCpy);

uint16 ADC_u16ReadAsync(void);

uint16 ADC_ReadSync(void);

void ADC_voidInterruptEnable(void);

void ADC_voidInterruptDisable(void);





#endif 
