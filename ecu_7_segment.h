/* 
 * File:   ecu_7_segment.h
 * Author: Nourhan_Abdo
 *
 * Created on July 7, 2024, 9:24 AM
 */

#ifndef ECU_7_SEGMENT_H
#define	ECU_7_SEGMENT_H

/* Section: Includes */
#include "ecu_7_segment_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

/* Section: Data Type Declarations */
typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE      
}segment_type_t;

typedef struct{
    pin_config_t segment_pin[4];
    segment_type_t segment_type;
}segment_t;

/* Section: Function Declarations */
Std_ReturnType segment_initialize(const segment_t *seg);
Std_ReturnType segment_write_number(const segment_t *seg,uint8 number);

#endif	/* ECU_7_SEGMENT_H */

