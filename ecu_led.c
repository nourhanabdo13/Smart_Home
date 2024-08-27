/* 
 * File:   ecu_led.c
 * Author: Nourhan_Abdo
 *
 * Created on July 2, 2024, 5:41 AM
 */
#include "ecu_led.h"

/**
 * @brief Initialize the pin to OUTPUT and turn on and off the led
 * @param led pointer to led module configurations
 * @return Status of function
 *          (E_OK)     : function done successfully
 *          (E_NOT_OK) : function has issue
 */
Std_ReturnType led_initialize(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led->port ,.pin = led->pin ,.direction = GPIO_OUTPUT,.logic = led->led_status};
        gpio_pin_inialize(&pin_obj);
    }
    
    return ret;
}
/**
 * @brief Turn ON the led
 * @param led pointer to led module configurations
 * @return Status of function
 *          (E_OK)     : function done successfully
 *          (E_NOT_OK) : function has issue
 */
Std_ReturnType led_turn_on(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led->port ,.pin = led->pin ,.direction = GPIO_OUTPUT,.logic = led->led_status};
        gpio_pin_write_logic(&pin_obj,GPIO_HIGH);
    }
    
    return ret;
}
/**
 * @brief Turn OFF the led
 * @param led pointer to led module configurations
 * @return Status of function
 *          (E_OK)     : function done successfully
 *          (E_NOT_OK) : function has issue
 */
Std_ReturnType led_turn_off(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led->port ,.pin = led->pin ,.direction = GPIO_OUTPUT,.logic = led->led_status};
        gpio_pin_write_logic(&pin_obj,GPIO_LOW);
    }
    
    return ret;
}
/**
 * @brief Toggle the led
 * @param led pointer to led module configurations
 * @return Status of function
 *          (E_OK)     : function done successfully
 *          (E_NOT_OK) : function has issue
 */
Std_ReturnType led_turn_toggle(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
       pin_config_t pin_obj = {.port = led->port ,.pin = led->pin ,.direction = GPIO_OUTPUT,.logic = led->led_status};
        gpio_pin_toggle_logic(&pin_obj);
    }
    
    return ret;
}

