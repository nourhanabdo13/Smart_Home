/* 
 * File:   ecu_dc_motor.c
 * Author: Nourhan_Abdo
 *
 * Created on July 5, 2024, 10:14 AM
 */
#include "ecu_dc_motor.h"


/**
 * @brief Initialize the DC motor
 * @param _dc_motor pointer point to dc motor module configuration
 * @return Status of function
 *          (E_OK)     : function done successfully
 *          (E_NOT_OK) : function has issue
 */
Std_ReturnType dc_motor_initialization(const dc_motor_t *_dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
       
        gpio_pin_inialize(&(_dc_motor->dc_motor_pin[0]));
        gpio_pin_inialize(&(_dc_motor->dc_motor_pin[1]));
        
    }
    return ret;
}
/**
 * @brief  Move the DC motor right
 * @param _dc_motor pointer point to relay module configuration
 * @return Status of function
 *          (E_OK)     : function done successfully
 *          (E_NOT_OK) : function has issue
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]),GPIO_HIGH);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]),GPIO_LOW);
    }
    return ret;
}

/**
 * @brief  Move the DC motor left
 * @param _dc_motor pointer point to relay module configuration
 * @return Status of function
 *          (E_OK)     : function done successfully
 *          (E_NOT_OK) : function has issue
 */
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]),GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]),GPIO_HIGH);
    }
    return ret;
}

/**
 * @brief  Stop the DC motor 
 * @param _dc_motor pointer point to relay module configuration
 * @return Status of function
 *          (E_OK)     : function done successfully
 *          (E_NOT_OK) : function has issue
 */
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]),GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]),GPIO_LOW);
    }
    return ret;
}
