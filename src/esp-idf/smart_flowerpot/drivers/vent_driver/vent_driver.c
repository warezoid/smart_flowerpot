/*
    - CREATE ERROR STRUCTURE FOR VENT AND OTHER ELEMENTS
    - SWITCH OFF MOSFET WITH ONE SHOT TIMER -> THEN DO ERROR LOGIC AFTER TICKS COUNT
        - STUDY TIMERS ON ESP
*/

#include <stdio.h>
#include "vent_driver.h"

void vent_driver_init(){
    //init pwm_generator
    pwm_init_t pwm_cfg = {
        .timer = LEDC_TIMER_0,
        .frequency_hz = 50,
        .channel = OUT_PWM_CHANNEL,
        .out_pwm_pin = GPIO_NUM_13
    };
    pwm_init(&pwm_cfg);

    //init out gpio
    gpio_set_direction(OUT_VSPM1_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(OUT_VSPM2_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(OUT_VSPM1_PIN, 0);
    gpio_set_level(OUT_VSPM2_PIN, 0);

    //init in gpio
    gpio_set_direction(IN_ESO1_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(IN_ESO2_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(IN_ESC1_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(IN_ESC2_PIN, GPIO_MODE_INPUT);
}



void vent_cls(vsrp_dataset *vent_sys){
    if(!vent_sys->vsrs_tick){
        pwm_set_duty(OUT_PWM_CHANNEL, SERVO_DUTY_CLOSE);

        if(vent_sys->vsv1_enabled){
            gpio_set_level(OUT_VSPM1_PIN, 1);
        }
        
        if(vent_sys->vsv2_enabled){
            gpio_set_level(OUT_VSPM2_PIN, 1);
        }

        vent_sys->vsrs_tick = xTaskGetTickCount();
        vent_sys->vsp_code = 1;
    }
}

void vent_opn(vsrp_dataset *vent_sys){
    if(!vent_sys->vsrs_tick){
        pwm_set_duty(OUT_PWM_CHANNEL, SERVO_DUTY_OPEN);

        if(vent_sys->vsv1_enabled){
            gpio_set_level(OUT_VSPM1_PIN, 1);
        }

        if(vent_sys->vsv2_enabled){
            gpio_set_level(OUT_VSPM2_PIN, 1);
        }

        vent_sys->vsrs_tick = xTaskGetTickCount();
        vent_sys->vsp_code = 2;
    }
}

void vent_ack(vsrp_dataset *vent_sys){
    if(vent_sys->vsrs_tick){
        if((xTaskGetTickCount() - vent_sys->vsrs_tick) >= pdMS_TO_TICKS(VENT_MOVE_DELAY_MS)){
            gpio_set_level(OUT_VSPM1_PIN, 0);
            gpio_set_level(OUT_VSPM2_PIN, 0);
            vent_sys->vsrs_tick = 0;

            switch(vent_sys->vsp_code){
                case 1:
                    if(vent_sys->vsv1_enabled){
                        if(!gpio_get_level(IN_ESC1_PIN)){
                            vent_sys->vsv1_enabled = 0;
                            vent_sys->errcode_1 = 10;
                        }
                    }

                    if(vent_sys->vsv2_enabled){
                        if(!gpio_get_level(IN_ESC2_PIN)){
                            vent_sys->vsv2_enabled = 0;
                            vent_sys->errcode_2 = 10;
                        }
                    }
                    break;
                case 2:
                    if(vent_sys->vsv1_enabled){
                        if(!gpio_get_level(IN_ESO1_PIN)){
                            vent_sys->vsv1_enabled = 0;
                            vent_sys->errcode_1 = 10;
                        }
                    }

                    if(vent_sys->vsv2_enabled){
                        if(!gpio_get_level(IN_ESO2_PIN)){
                            vent_sys->vsv2_enabled = 0;
                            vent_sys->errcode_2 = 10;
                        }
                    }
                    break;
            }

            vent_sys->vsp_code = 0;
        }
    }
}
