#include "STD_Types.h"
#include "BIT_Math.h"

#include "ADC_int.h"
#include "ADC_cfg.h"
#include "ADC_priv.h"

uint16 ADC_u16AdcValue = 0 ;

void ADC_voidInit(void)
{ 
	ADMUX &=0b11100000;	 
	ADMUX |= (0x1F)&ADC_MUX_CHANNEL;
	
	#if ADC_VOLTAGE_REFERENCE == ADC_ARFF 
	CLR_BIT(ADMUX , 6);
	CLR_BIT(ADMUX , 7);
	#elif ADC_VOLTAGE_REFERENCE == ADC_AVCC 
	SET_BIT(ADMUX , 6);
	CLR_BIT(ADMUX , 7);
	#else 
    SET_BIT(ADMUX , 6);
	SET_BIT(ADMUX , 7);
    #endif	
   ADCSRA &=0b11111000;
   ADCSRA |= (0x07)&ADC_PRESCALLER; 

   #if ADC_AUTO_TRIGGER ==ADC_ENABLE 
   SET_BIT(ADCSRA , 5);
   
   SFIOR &=0b00011111;
   SFIOR |=ADC_AUTO_TRIGGER_SRC ;
   #else
   CLR_BIT(ADCSRA , 5);  
   #endif

   SET_BIT(ADCSRA , 7);
}

void ADC_voidStartConversion(uint8 u8ChannelNumCpy)
{
	ADMUX &=0b11100000;
	ADMUX |= (0x1F)&u8ChannelNumCpy;
	SET_BIT(ADCSRA , 6);
}

uint16 ADC_u16ReadAsync(void)
{

	return 	ADC_u16AdcValue  ; 
	
}

uint16 ADC_ReadSync(void)
{
	
	uint16 u16AdcValueLoc = 0 ;
	while (GET_BIT(ADCSRA,4) == 0);
	SET_BIT(ADCSRA,4);
	#if ADC_RES_BIT == ADC_10BIT
	u16AdcValueLoc =  ADCL ;
	u16AdcValueLoc |= ADCH<<8  ;
	#else
	u16AdcValueLoc = ADCH ;
	#endif
	return 	u16AdcValueLoc  ;
	
}

void ADC_voidInterruptEnable(void)
{
	SET_BIT(ADCSRA , 3);
}

void ADC_voidInterruptDisable(void)
{
	CLR_BIT(ADCSRA , 3);
}

void ADC_voidEnable(void)
{
	SET_BIT(ADCSRA , 7) ;
}
void ADC_voidDisable(void)
{
	CLR_BIT(ADCSRA , 7) ;
}

void __vector_16 (void) __attribute((signal,used)); 
void __vector_16 (void) 
{

	#if ADC_RES_BIT == ADC_10BIT
	ADC_u16AdcValue = ADCH<<8 | ADCL ;
	#else
	ADC_u16AdcValue = ADCH ;
	#endif
}






