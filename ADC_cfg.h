#ifndef ADC_CFG_H
#define ADC_CFG_H

#define ADC_MUX_CHANNEL    ADC_CHANNEL_0

#define ADC_RES_BIT         ADC_10BIT

#define ADC_VOLTAGE_REFERENCE  ADC_2_56V

#define ADC_PRESCALLER       PRESCALL_2

#define ADC_AUTO_TRIGGER    ADC_DISABLE


#if ADC_AUTO_TRIGGER == ADC_ENABLE

#define ADC_AUTO_TRIGGER_SRC   ADC_FREE_RUNNING
#endif


#endif
