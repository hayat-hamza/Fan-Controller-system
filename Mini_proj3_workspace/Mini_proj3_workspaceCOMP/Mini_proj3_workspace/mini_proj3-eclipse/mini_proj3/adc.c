 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega16 ADC driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
#include "adc.h"
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void ADC_init(const ADC_ConfigType * Config_Ptr)
{

	////////////////////
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage or internal or else..
	 * ADLAR   = 0 right adjusted
	 * MUX4:0 to choose channel
	 */
	/*
	 * (ADMUX & 0XFC) TO MAKE SURE THESE BITS DONT CHANGE
	 */
	ADMUX&=~0X03;	/*TO CLEAR first 2 bits before putting value in them*/
	ADMUX =(ADMUX & 0XFC)|(ADMUX|Config_Ptr->ref_volt);/* (ADMUX & 0XFC) TO MAKE SURE THESE BITS DONT CHANGE */
	ADMUX =(1<<REFS1)|(1<<REFS0);


	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 to choose ADC_Clock --> ADC must operate in range 50-200Khz
	 */
	ADCSRA&=~0x07;		/*clear first 3 bits*/
	ADCSRA = (1<<ADEN) | (1<<ADPS1);
	ADCSRA = (ADCSRA& 0xf8)|(ADCSRA|Config_Ptr->prescaler);		/**/

}

uint16 ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}
