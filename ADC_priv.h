#ifndef ADC_PRIV_H
#define ADC_PRIV_H


#define ADCSRA   *((volatile uint8 *)0x26 )
#define ADMUX    *((volatile uint8 *)0x27 )
#define ADCL     *((volatile uint8 *)0x24 )
#define ADCH     *((volatile uint8 *)0x25 )
#define SFIOR    *((volatile uint8 *)0x50 )



#define ADC_8BIT    0
#define ADC_10BIT   1

#define ADC_ARFF    0
#define ADC_AVCC    1
#define ADC_2_56V   2

#define PRESCALL_2      1
#define PRESCALL_4      2
#define PRESCALL_8      3
#define PRESCALL_16     4
#define PRESCALL_32     5
#define PRESCALL_64     6
#define PRESCALL_128    7

#define ADC_DISABLE   0
#define ADC_ENABLE    1

#define ADC_FREE_RUNNING       0
#define ADC_ANALOG_COMP        32  // 1<<5
#define ADC_EXTINT0            64  // 2<<5
#define ADC_TIM0_CMP           96  // 3<<5
#define ADC_TIM0_OVERFLOW      128
#define ADC_TIM_COMP_MATCHB    160
#define ADC_TIM1_OVERFLOW      192
#define ADC_TIM1_CAPTURE_EVENT 224






#endif
