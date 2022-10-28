/*
 * main.c
 *
 *  Created on: 2 Sep 2022
 *      Author: HP
 */

#include "STD_Types.h"
#include "BIT_Math.h"
#include <avr/delay.h>

#include "DIO_int.h"
#include "ADC_int.h"




void main (void)
{
	uint16 i = 0 , analog,DigitalValue,temp;
	DIO_voidInit();
    LCD_voidInit();
	ADC_voidInit();
	while (1)
	{
		ADC_voidStartConversion(ADC_CHANNEL_0);

		DigitalValue  = ADC_ReadSync();


		analog = (DigitalValue * 2560) /1024 ;

		temp = (analog /10 )-110;

		LCD_enuWriteData(0,((temp/100))+48);
		LCD_enuWriteData(0,((temp/10))+48);
		LCD_enuWriteData(0,(temp%10)+48);
		_delay_ms(2000);
		LCD_enuWriteCmd(0,0x01);
		_delay_ms(100);
	}


}
