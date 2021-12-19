 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ATmega16 ADC driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions and Enums                               *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
/*
 * refrence voltage values
 */
#define ADC_REF_VOLT_VALUE   2.56
enum ref_volt {AREF,AVCC,RESERVED,INTEERNAL};
/*
 * ADC prescaler values
 */
enum prescaler {ADC_PRESCALER_2=1,ADC_PRESCALER_4,ADC_PRESCALER_8,ADC_PRESCALER_16,ADC_PRESCALER_32,ADC_PRESCALER_64,ADC_PRESCALER_128};


/*******************************************************************************
 *                    			  new data types                                 *
 *******************************************************************************/
typedef uint8   ADC_ReferenceVolatge;
typedef uint8   ADC_Prescaler;

/*******************************************************************************
 *                    			  strucures                                   *
 *******************************************************************************/

 typedef struct{
 ADC_ReferenceVolatge ref_volt;
 ADC_Prescaler prescaler;
}ADC_ConfigType;

/*******************************************************************************
 *                     		 Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num);

#endif /* ADC_H_ */


