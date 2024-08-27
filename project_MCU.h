/* 
 * File:   Application.h
 * Author: East-Sound
 *
 * Created on July 2, 2024, 5:48 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H


/* Section: Includes */
#include "ECU_Layer/ecu_layer_int.h"
#include "ECU_Layer/DC_Motor/ecu_dc_motor.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "MCAL_Layer/EEPROM/hal_eeprom.h"
#include "MCAL_Layer/ADC/hal_adc.h"
#include "MCAL_Layer/Timer/hal_timer0.h"
#include "MCAL_Layer/Timer/hal_timer1.h"
#include "MCAL_Layer/Timer/hal_timer2.h"
#include "MCAL_Layer/Timer/hal_timer3.h"
#include "MCAL_Layer/CCP1/hal_ccp1.h"
#include "MCAL_Layer/CCP1/hal_ccp1.h"
#include "MCAL_Layer/usart/hal_usart.h"
#include "MCAL_Layer/I2C/hal_i2c.h"
#include "ECU_Layer/Ultrasonic/Ultrasonic.h"
#include "ECU_Layer/7_segment/ecu_7_segment.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

/* Section: Data Type Declarations */
extern keypad_t keypad1;
extern chr_lcd_4bit_t lcd_2;
extern chr_lcd_4bit_t lcd_1;


/* Section: Function Declarations */
void application_initialize(void);
void Int0_APP_ISR(void);

#endif	/* APPLICATION_H */

