/* 
 * File:   Application.c
 * Author: Nourhan_Abdo
 *
 * Created on July 2, 2024, 4:25 AM
 */

#include "Application.h"
keypad_t keypad2 = {.key_pin_raws[0].port = PORTD_INDEX,.key_pin_raws[0].pin = GPIO_PIN0,
                    .key_pin_raws[0].direction = GPIO_OUTPUT,.key_pin_raws[0].logic = GPIO_LOW,
                    .key_pin_raws[1].port = PORTD_INDEX,.key_pin_raws[1].pin = GPIO_PIN1,
                    .key_pin_raws[1].direction = GPIO_OUTPUT,.key_pin_raws[1].logic = GPIO_LOW,
                    .key_pin_raws[2].port = PORTD_INDEX,.key_pin_raws[2].pin = GPIO_PIN2,
                    .key_pin_raws[2].direction = GPIO_OUTPUT,.key_pin_raws[2].logic = GPIO_LOW,
                    .key_pin_raws[3].port = PORTD_INDEX,.key_pin_raws[3].pin = GPIO_PIN3,
                    .key_pin_raws[3].direction = GPIO_OUTPUT,.key_pin_raws[3].logic = GPIO_LOW,
                    .key_pin_column[0].port = PORTD_INDEX,.key_pin_column[0].pin = GPIO_PIN4,
                    .key_pin_column[0].direction = GPIO_INPUT,.key_pin_column[0].logic = GPIO_LOW,
                    .key_pin_column[1].port = PORTD_INDEX,.key_pin_column[1].pin = GPIO_PIN5,
                    .key_pin_column[1].direction = GPIO_INPUT,.key_pin_column[1].logic = GPIO_LOW,
                    .key_pin_column[2].port = PORTD_INDEX,.key_pin_column[2].pin = GPIO_PIN6,
                    .key_pin_column[2].direction = GPIO_INPUT,.key_pin_column[2].logic = GPIO_LOW,
                    .key_pin_column[3].port = PORTD_INDEX,.key_pin_column[3].pin = GPIO_PIN7,
                    .key_pin_column[3].direction = GPIO_INPUT,.key_pin_column[3].logic = GPIO_LOW  
};
dc_motor_t dc_motor_1 = {.dc_motor_pin[0].port = PORTB_INDEX,.dc_motor_pin[0].pin = GPIO_PIN0,
                         .dc_motor_pin[0].direction = GPIO_OUTPUT, .dc_motor_pin[0].logic = DC_MOTOR_OFF_STATUS,
                         .dc_motor_pin[1].port = PORTB_INDEX,.dc_motor_pin[1].pin = GPIO_PIN1,
                         .dc_motor_pin[1].direction = GPIO_OUTPUT, .dc_motor_pin[1].logic = DC_MOTOR_OFF_STATUS};
dc_motor_t dc_motor_2 = {.dc_motor_pin[0].port = PORTB_INDEX,.dc_motor_pin[0].pin = GPIO_PIN2,
                         .dc_motor_pin[0].direction = GPIO_OUTPUT, .dc_motor_pin[0].logic = DC_MOTOR_OFF_STATUS,
                         .dc_motor_pin[1].port = PORTB_INDEX,.dc_motor_pin[1].pin = GPIO_PIN3,
                         .dc_motor_pin[1].direction = GPIO_OUTPUT, .dc_motor_pin[1].logic = DC_MOTOR_OFF_STATUS};
segment_t seg1 = {.segment_pin[0].port = PORTC_INDEX,.segment_pin[0].pin = GPIO_PIN3,
                  .segment_pin[0].direction = GPIO_OUTPUT,.segment_pin[0].logic = GPIO_LOW,
                  .segment_pin[1].port = PORTC_INDEX,.segment_pin[1].pin = GPIO_PIN4,
                  .segment_pin[1].direction = GPIO_OUTPUT,.segment_pin[1].logic = GPIO_LOW,
                  .segment_pin[2].port = PORTC_INDEX,.segment_pin[2].pin = GPIO_PIN5,
                  .segment_pin[2].direction = GPIO_OUTPUT,.segment_pin[2].logic = GPIO_LOW,
                  .segment_pin[3].port = PORTC_INDEX,.segment_pin[3].pin = GPIO_PIN6,
                  .segment_pin[3].direction = GPIO_OUTPUT,.segment_pin[3].logic = GPIO_LOW,
                  .segment_type = SEGMENT_COMMON_ANODE
};
led_t led1 = {.port = PORTC_INDEX, .pin = GPIO_PIN2, .led_status = GPIO_LOW};
led_t led2 = {.port = PORTC_INDEX, .pin = GPIO_PIN7, .led_status = GPIO_LOW};
led_t led3 = {.port = PORTA_INDEX, .pin = GPIO_PIN2, .led_status = GPIO_LOW};
led_t led4 = {.port = PORTC_INDEX, .pin = GPIO_PIN1, .led_status = GPIO_LOW};
led_t buzzer2 = {.port = PORTA_INDEX, .pin = GPIO_PIN3, .led_status = GPIO_LOW};
led_t led5 = {.port = PORTA_INDEX, .pin = GPIO_PIN5, .led_status = GPIO_LOW};
led_t buzzer3 = {.port = PORTB_INDEX, .pin = GPIO_PIN5, .led_status = GPIO_LOW};
void ADC_Init1(void) {
    ADCON1 = 0x0D; 
    ADCON2 = 0xA9; 
}

unsigned int ADC_Read(unsigned char channel) {
    ADCON0 = (channel << 2) | 0x01; 
    __delay_ms(2); 
    ADCON0bits.GO_DONE = 1;
    while (ADCON0bits.GO_DONE);
    return ((ADRESH << 8) + ADRESL);
}
void PWM_Init(void) {
    PR2 = 0xFF; 
    CCP1M3 = 1; CCP1M2 = 1; 
    T2CKPS0 = 1; T2CKPS1 = 0; 
    TMR2ON = 1; 
    CCP1CONbits.DC1B = 0;
    CCPR1L = 0; 
}

void PWM_Set_Duty(unsigned int duty) {
    if(duty < 1024) {
        CCP1CONbits.DC1B = duty & 0x03;
        CCPR1L = duty >> 2; 
    }
}


uint8 key_value = 0;
unsigned char current_floor = 0; 
unsigned char target_floor = 0;
unsigned int ldr_value = 0;
unsigned int pot_value = 0; 
int main() { 
    Std_ReturnType ret = E_NOT_OK;
    application_initialize(); 
     ADC_Init1();
     PWM_Init();
     TRISCbits.RC0 = 1;
     TRISAbits.RA4 = 1;
    while(1){
        if(PORTCbits.RC0 == 1)
        {
            ret = led_turn_on(&led4);
            ret = led_turn_on(&buzzer2);
            
        }
        else
        {
            ret = led_turn_off(&led4);
            ret = led_turn_off(&buzzer2);
        }
        if(PORTAbits.RA4 == 1)
        {
            ret = led_turn_on(&led5);
            ret = led_turn_on(&buzzer3);
            
        }
        else
        {
            ret = led_turn_off(&led5);
            ret = led_turn_off(&buzzer3);
        }
        pot_value = ADC_Read(1);
        PWM_Set_Duty(pot_value);
        ldr_value = ADC_Read(0);
        if(ldr_value < 512)
        {
            ret = led_turn_on(&led3);
            ret = dc_motor_stop(&dc_motor_2);
            
        }
        else
        {
            ret = dc_motor_move_right(&dc_motor_2);
            ret = led_turn_off(&led3);
            __delay_ms(1000);
            ret = dc_motor_stop(&dc_motor_2);
        }
        ret = dc_motor_stop(&dc_motor_2);
        ret = keypad_get_value(&keypad2,&key_value);
        if (key_value == '1') {
            target_floor = 1;
        } else if (key_value == '2') {
            target_floor = 2;
        } else if (key_value == '3') {
            target_floor = 3;
        } else if (key_value == '4') {
            target_floor = 4;
        } else if (key_value == '5') {
            target_floor = 5;
        } else if (key_value == '6') {
            target_floor = 6;
        } else if (key_value == '7') {
            target_floor = 7;
        } else if (key_value == '8') {
            target_floor = 8;
        } else if (key_value == '9') {
            target_floor = 9;
        }
        ret = dc_motor_move_right(&dc_motor_1);
        ret = led_turn_on(&led2);
        if (target_floor > current_floor) {
            while (current_floor < target_floor) {
                current_floor++;
                switch(current_floor) {
                    case 0: ret = segment_write_number(&seg1,0); break; 
                    case 1: ret = segment_write_number(&seg1,1); break; 
                    case 2: ret = segment_write_number(&seg1,2); break; 
                    case 3: ret = segment_write_number(&seg1,3); break; 
                    case 4: ret = segment_write_number(&seg1,4); break; 
                    case 5: ret = segment_write_number(&seg1,5); break; 
                    case 6: ret = segment_write_number(&seg1,6); break; 
                    case 7: ret = segment_write_number(&seg1,7); break; 
                    case 8: ret = segment_write_number(&seg1,8); break;
                    case 9: ret = segment_write_number(&seg1,9); break; 
                }
                __delay_ms(1000); 
            }
        } else if (target_floor < current_floor) {
            while (current_floor > target_floor) {
                current_floor--;
                switch(current_floor) {
                    case 0: ret = segment_write_number(&seg1,0); break; 
                    case 1: ret = segment_write_number(&seg1,1); break; 
                    case 2: ret = segment_write_number(&seg1,2); break; 
                    case 3: ret = segment_write_number(&seg1,3); break; 
                    case 4: ret = segment_write_number(&seg1,4); break; 
                    case 5: ret = segment_write_number(&seg1,5); break; 
                    case 6: ret = segment_write_number(&seg1,6); break; 
                    case 7: ret = segment_write_number(&seg1,7); break; 
                    case 8: ret = segment_write_number(&seg1,8); break;
                    case 9: ret = segment_write_number(&seg1,9); break; 
                }
                __delay_ms(1000); 
            }
        }
        ret = dc_motor_stop(&dc_motor_1);
        ret = led_turn_off(&led2);
    }
        
    return (EXIT_SUCCESS);
}
void application_initialize(void)
{
    Std_ReturnType ret = E_NOT_OK;
    ret = keypad_initialize(&keypad2);
    ret = segment_initialize(&seg1);
    ret = dc_motor_initialization(&dc_motor_1);
    ret = dc_motor_initialization(&dc_motor_2);
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
    ret = led_initialize(&led3);
    ret = led_initialize(&led4);
    ret = led_initialize(&buzzer2);
    ret = led_initialize(&led5);
    ret = led_initialize(&buzzer3);
    ecu_layer_initialize();
}
