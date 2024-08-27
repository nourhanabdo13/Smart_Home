/* 
 * File:   ecu_keypad.h
 * Author: Nourhan_Abdo
 *
 * Created on July 8, 2024, 10:06 AM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* Section: Includes */
#include "ecu_keypad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

/* Section: Data Type Declarations */
typedef struct{
    pin_config_t key_pin_raws[4];
    pin_config_t key_pin_column[4];
}keypad_t;

/* Section: Function Declarations */
Std_ReturnType keypad_initialize(const keypad_t *_keypad);
Std_ReturnType keypad_get_value(const keypad_t *_keypad,uint8 *value);


#endif	/* ECU_KEYPAD_H */

