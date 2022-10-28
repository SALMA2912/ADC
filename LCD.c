
#include "STD_Types.h"
#include "BIT_MAth.h"
#include <avr/delay.h>

#include "DIO_int.h"
#include "LCD_int.h"
#include "LCD_cfg.h"
#include "LCD_priv.h"

void LCD_voidInit(void) //initializing the LCD (see datasheet)
{
	uint8 u8CntrLoc ; //counter on the indeces of the array LCD_astrConfig
	uint8 u8CmdLoc  ;
	for(u8CntrLoc = 0 ; u8CntrLoc < LCD_MAX_NUM ; u8CntrLoc++)
	{
		if (LCD_astrConfig[u8CntrLoc].strLcdPinOutCfg.u8LcdMode== LCD_8BIT_MODE) // 8 Bit-Mode 
		{
				_delay_ms(30); // as stated in data sheet (after VDD rises to 4.5 volt)
				
				u8CmdLoc = 0b00110000|
				LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8LineMode << 3|    //N
				LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8CharFont << 2;    //F
				LCD_enuWriteCmd (u8CntrLoc , u8CmdLoc);
				
				_delay_ms(1); // as stated in data sheet (more than 39 microseconds)
				
				u8CmdLoc = 0b00001000|
				LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8DisplayState << 2|  //D
				LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8CursorState << 1|   //C
				LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8BlinkState << 0;    //B
				LCD_enuWriteCmd (u8CntrLoc , u8CmdLoc);
				
				_delay_ms(1);  // as stated in data sheet (more than 39 microseconds)
				
				LCD_enuWriteCmd (u8CntrLoc , 0x01);
				
				_delay_ms(2);  // as stated in data sheet (more than 1.53 milliseconds)
				
				u8CmdLoc = 0b00000100|
				LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8IncreMode << 1|   //I/D
				LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8WindowMode << 0;  //SH
				LCD_enuWriteCmd (u8CntrLoc , u8CmdLoc);
				
				_delay_ms(1);
					
		}
		else // 4 Bit-Mode
		{
			/*
			
			_delay_ms(30);
			
			u8CmdLoc=0b00100000;
			LCD_enuWriteCmd (u8CntrLoc , u8CmdLoc);
			u8CmdLoc=0b00100000;
			LCD_enuWriteCmd (u8CntrLoc , u8CmdLoc);
			u8CmdLoc=0b00000000|
			LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8LineMode << 7|    //N
			LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8CharFont << 6;    //F
			LCD_enuWriteCmd (u8CntrLoc , u8CmdLoc);
			
			_delay_ms(1);
			
			u8CmdLoc=0b00000000;
			LCD_enuWriteCmd (u8CntrLoc , u8CmdLoc);
			u8CmdLoc=0b100000000|
			LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8DisplayState << 6|  //D
			LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8CursorState << 5|   //C
			LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8BlinkState << 4;    //B
			LCD_enuWriteCmd (u8CntrLoc , u8CmdLoc);
			
			_delay_ms(1);
			
			u8CmdLoc=0b00000000;
			LCD_enuWriteCmd (u8CntrLoc , u8CmdLoc);
			u8CmdLoc=0b00010000;
			LCD_enuWriteCmd (u8CntrLoc , u8CmdLoc);
			
			_delay_ms(2);
			
			u8CmdLoc=0b00000000;
			LCD_enuWriteCmd (u8CntrLoc , u8CmdLoc);
			u8CmdLoc=0b01000000|
			LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8WindowMode<< 5|   //I/D
			LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8WindowMode<< 4;   //SH
			
			*/
		
			
			
			
		}
		
	}
}



tenuErrorStatus LCD_enuWriteCmd(uint8 u8LcdIndxCpy , uint8 u8LcdCmdCpy)   //function that takes the index of the LCD you want to write on (which LCD) and the comand you want to write
{
 tenuErrorStatus enuReturStateLoc = E_OK ;
 
 if(u8LcdIndxCpy < LCD_MAX_NUM)
 {
	DIO_enuSetPinValue(LCD_astrConfig[u8LcdIndxCpy].strLcdPinOutCfg.au8ControlPins[0] , 0) ;  // RS = 0 (we're writing(inputing) a comand)  //write DIO rs
    // help cmd	
    LCD_voidHelp(u8LcdIndxCpy, u8LcdCmdCpy);
   
   
 }
 else
 {
	 enuReturStateLoc = E_NOK_PARAM_OUT_OF_RANGE ;
 }
	return enuReturStateLoc ;
}



tenuErrorStatus LCD_enuWriteData(uint8 u8LcdIndxCpy , uint8 u8LcdDataCpy)  //function that takes the index of the LCD you want to write on (which LCD) and the data (character) you want to write 
{
tenuErrorStatus enuReturStateLoc = E_OK ;
 if(u8LcdIndxCpy < LCD_MAX_NUM)
 {
	//write DIO rs
	DIO_enuSetPinValue(LCD_astrConfig[u8LcdIndxCpy].strLcdPinOutCfg.au8ControlPins[0] , 1) ;  // RS = 1 (we're writing data)
    // help cmd	
    LCD_voidHelp(u8LcdIndxCpy, u8LcdDataCpy);
   
   
 }
 else
 {
	 enuReturStateLoc = E_NOK_PARAM_OUT_OF_RANGE ;
 }
	return enuReturStateLoc ;
	
}



static void LCD_voidHelp(uint8 u8LcdIndxCpy, uint8 u8LcdCmdDataCpy)
{
	uint8 u8CntrLoc ; // counter on data pins (D0....D7)
	
	DIO_enuSetPinValue(LCD_astrConfig[u8LcdIndxCpy].strLcdPinOutCfg.au8ControlPins[1] , 0) ;   //R/W = 0 (we're writing)  // R/W low
	DIO_enuSetPinValue(LCD_astrConfig[u8LcdIndxCpy].strLcdPinOutCfg.au8ControlPins[2] , 1) ;   //E = 1  (to put 0s and 1s of data or comand on the pin)  //EN latch high
	
    if (LCD_astrConfig[u8LcdIndxCpy].strLcdPinOutCfg.u8LcdMode== LCD_8BIT_MODE) // 8-Bit-Mode
	{
		for(u8CntrLoc = 0 ; u8CntrLoc < 8 ; u8CntrLoc++)  // 
		{
			DIO_enuSetPinValue(LCD_astrConfig[u8LcdIndxCpy].strLcdPinOutCfg.au8DataPins[u8CntrLoc],GET_BIT(u8LcdCmdDataCpy,u8CntrLoc));
		}
	
	}
	else   //4-Bit-Mode
	{
		for(u8CntrLoc = 4 ; u8CntrLoc < 8; u8CntrLoc++)
		{
			DIO_enuSetPinValue(LCD_astrConfig[u8LcdIndxCpy].strLcdPinOutCfg.au8DataPins[u8CntrLoc],GET_BIT(u8LcdCmdDataCpy,u8CntrLoc));
			u8LcdCmdDataCpy = u8LcdCmdDataCpy<<4 ;
			DIO_enuSetPinValue(LCD_astrConfig[u8LcdIndxCpy].strLcdPinOutCfg.au8DataPins[u8CntrLoc],GET_BIT(u8LcdCmdDataCpy,u8CntrLoc));
			
		}
		
	}
	
	DIO_enuSetPinValue(LCD_astrConfig[u8LcdIndxCpy].strLcdPinOutCfg.au8ControlPins[2] , 0) ;  //E = 0 (after we made sure all 0s and 1s of data or comand are on the pins) //EN latch low
    
}
  
   
   
   
   
   
   
   
   
   
   
   