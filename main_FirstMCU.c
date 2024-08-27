/* 
 * File:   Application.c
 * Author: Nourhan_Abdo
 *
 * Created on July 2, 2024, 4:25 AM
 */

#include "Application.h"
dc_motor_t dc_motor_1 = {.dc_motor_pin[0].port = PORTD_INDEX,.dc_motor_pin[0].pin = GPIO_PIN0,
                         .dc_motor_pin[0].direction = GPIO_OUTPUT, .dc_motor_pin[0].logic = DC_MOTOR_OFF_STATUS,
                         .dc_motor_pin[1].port = PORTD_INDEX,.dc_motor_pin[1].pin = GPIO_PIN1,
                         .dc_motor_pin[1].direction = GPIO_OUTPUT, .dc_motor_pin[1].logic = DC_MOTOR_OFF_STATUS};
dc_motor_t dc_motor_2 = {.dc_motor_pin[0].port = PORTD_INDEX,.dc_motor_pin[0].pin = GPIO_PIN2,
                         .dc_motor_pin[0].direction = GPIO_OUTPUT, .dc_motor_pin[0].logic = DC_MOTOR_OFF_STATUS,
                         .dc_motor_pin[1].port = PORTD_INDEX,.dc_motor_pin[1].pin = GPIO_PIN3,
                         .dc_motor_pin[1].direction = GPIO_OUTPUT, .dc_motor_pin[1].logic = DC_MOTOR_OFF_STATUS};
led_t led1 = {.port = PORTA_INDEX, .pin = GPIO_PIN1, .led_status = GPIO_LOW};
led_t led2 = {.port = PORTA_INDEX, .pin = GPIO_PIN2, .led_status = GPIO_LOW};
led_t led3 = {.port = PORTA_INDEX, .pin = GPIO_PIN3, .led_status = GPIO_LOW};
led_t led4 = {.port = PORTD_INDEX, .pin = GPIO_PIN4, .led_status = GPIO_LOW};
led_t led5 = {.port = PORTD_INDEX, .pin = GPIO_PIN7, .led_status = GPIO_LOW};
keypad_t keypad1 = {.key_pin_raws[0].port = PORTC_INDEX,.key_pin_raws[0].pin = GPIO_PIN0,
                    .key_pin_raws[0].direction = GPIO_OUTPUT,.key_pin_raws[0].logic = GPIO_LOW,
                    .key_pin_raws[1].port = PORTC_INDEX,.key_pin_raws[1].pin = GPIO_PIN1,
                    .key_pin_raws[1].direction = GPIO_OUTPUT,.key_pin_raws[1].logic = GPIO_LOW,
                    .key_pin_raws[2].port = PORTC_INDEX,.key_pin_raws[2].pin = GPIO_PIN2,
                    .key_pin_raws[2].direction = GPIO_OUTPUT,.key_pin_raws[2].logic = GPIO_LOW,
                    .key_pin_raws[3].port = PORTC_INDEX,.key_pin_raws[3].pin = GPIO_PIN3,
                    .key_pin_raws[3].direction = GPIO_OUTPUT,.key_pin_raws[3].logic = GPIO_LOW,
                    .key_pin_column[0].port = PORTC_INDEX,.key_pin_column[0].pin = GPIO_PIN4,
                    .key_pin_column[0].direction = GPIO_INPUT,.key_pin_column[0].logic = GPIO_LOW,
                    .key_pin_column[1].port = PORTC_INDEX,.key_pin_column[1].pin = GPIO_PIN5,
                    .key_pin_column[1].direction = GPIO_INPUT,.key_pin_column[1].logic = GPIO_LOW,
                    .key_pin_column[2].port = PORTC_INDEX,.key_pin_column[2].pin = GPIO_PIN6,
                    .key_pin_column[2].direction = GPIO_INPUT,.key_pin_column[2].logic = GPIO_LOW,
                    .key_pin_column[3].port = PORTC_INDEX,.key_pin_column[3].pin = GPIO_PIN7,
                    .key_pin_column[3].direction = GPIO_INPUT,.key_pin_column[3].logic = GPIO_LOW  
};

void ADC_Init1(void) {
    ADCON1 = 0x00;  
    ADCON2 = 0xA9;  
    ADCON0 = 0x01;  
}
unsigned int ADC_Read(unsigned char channel) {
    if (channel > 7) return 0;
    
    ADCON0 = (channel << 3) | 0x01;  
     __delay_ms(2); 
    GO_nDONE = 1;  
    while (GO_nDONE);  
    return (ADRESH << 8) + ADRESL;  
}

uint8 temperature = 0;
uint8 lm35_res_1_txt[7];
uint8 key_value;
unsigned int distance;
unsigned int adcValue;
char correct_password[] = "2369";
char entered_password[5];
int pos = 0;

int main() { 
    Std_ReturnType ret = E_NOT_OK;
    application_initialize();
    TRISEbits.RE0 = 1;
    lcd_4bit_send_command(&lcd_1,_LCD_CLEAR);
    ret = lcd_4bit_send_string_pos(&lcd_1,2,7,"Hello");
    __delay_ms(250);
    lcd_4bit_send_command(&lcd_1,_LCD_CLEAR);
    ret = lcd_4bit_send_string_pos(&lcd_1,1,1,"Enter Password:");
    
    ADC_Init1(); 
    while(1){
            ret = keypad_get_value(&keypad1,&key_value);
            if(key_value != '\0') {
            entered_password[pos] = key_value;
            pos++;}
        
        if(pos == 4) {
            entered_password[4] = '\0';
            __delay_ms(500);
            if((strcmp(entered_password, correct_password) == 0) && (PORTBbits.RB7 == 1)) {
                lcd_4bit_send_command(&lcd_1,_LCD_CLEAR);
                ret = lcd_4bit_send_string_pos(&lcd_1,2,1,"Correct Password");
                ret = lcd_4bit_send_string_pos(&lcd_1,3,1,"Door Opened");
                ret = dc_motor_move_right(&dc_motor_2);
                ret = led_turn_on(&led1);
                __delay_ms(1000);
                ret = dc_motor_stop(&dc_motor_2);
                LATBbits.LB6 = 0;
                lcd_4bit_send_command(&lcd_1,_LCD_CLEAR);
                ret = lcd_4bit_send_string_pos(&lcd_1,3,1,"Welcome to Home ");
            } else {
                TRISBbits.RB6 = 0;
                LATBbits.LB6 = 1;
                lcd_4bit_send_command(&lcd_1,_LCD_CLEAR);
                ret = lcd_4bit_send_string_pos(&lcd_1,2,1,"Wrong Password");
                ret = lcd_4bit_send_string_pos(&lcd_1, 3, 1,"Buzzer ON");
                ret = led_turn_on(&led2);
                __delay_ms(500);
                LATBbits.LB6 = 0;
                lcd_4bit_send_command(&lcd_1,_LCD_CLEAR);
                ret = led_turn_off(&led2);
                ret = lcd_4bit_send_string_pos(&lcd_1,1,1,"Enter Password:");
            }
        }
            
        adcValue = ADC_Read(0);
        temperature = (adcValue * 500.0) / 1024.0;
        if(temperature > 25)
        {
            ret = dc_motor_move_right(&dc_motor_1);
            ret = led_turn_on(&led3);
            ret = led_turn_off(&led4);
        }
        else
        {
            ret = dc_motor_stop(&dc_motor_1);
            ret = led_turn_on(&led4);
            ret = led_turn_off(&led3);
        }
        ret = convert_uint16_to_string(temperature, lm35_res_1_txt);
        
        if(PORTDbits.RD6 == 1)
        {
            ret = led_turn_on(&led5);
        }
        else if(PORTDbits.RD6 == 0)
        {
            ret = led_turn_off(&led5);
        }
        
    }
        
    return (EXIT_SUCCESS);
}
void application_initialize(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = dc_motor_initialization(&dc_motor_1);
    ret = dc_motor_initialization(&dc_motor_2);
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
    ret = led_initialize(&led3);
    ret = led_initialize(&led4);
    ret = led_initialize(&led5);
    ret = keypad_initialize(&keypad1);
    ecu_layer_initialize();
}
