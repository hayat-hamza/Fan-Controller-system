/*
 * mini_proj3.c
 *
 *  Created on: Oct 15, 2021
 *      Author: Hayat Hussein
 */

#include "lcd.h"
#include "adc.h"
#include "lm35_sensor.h"
#include "motor.h"


int main(void){
	uint8 temp=0;
	uint8 speed;
	/*
	 * using the internal ADC ref 2.56v  with 8 prescaler
	 * and initializing lcd ,adc and motor
	 */
	ADC_ConfigType Internal_8;
	Internal_8.prescaler=8;
	Internal_8.ref_volt=2.56;
	LCD_init();
	ADC_init(&Internal_8);
	DcMotor_Init();
	LCD_clearScreen();
	/* Display these sentences at same position at all times */
	LCD_displayStringRowColumn(0,3,"Fan is ");
	LCD_displayStringRowColumn(1,3,"Temp = ");
	while(1)
	{
		/*
		 * we take the temp from the temp sensor then converting it into a percintage 0->100
		 * to express the speed
		 */
		temp = LM35_getTemperature();
		speed=(float)temp*100/120;
		/*
		 * DcMotor_Rotate func is responsible for choosing the motor state{cw,a-cw or stop}
		 * and the speed of the motor depending on the temp
		 */
		DcMotor_Rotate(CW,speed);
		/* Display the temperature value every time at same position */
		LCD_moveCursor(1,10);
		/*
		 * the folloing if-else statment to make sure the the number is displayed correctly
		 */
		if(temp >= 100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}
	}
	return 0;
}
