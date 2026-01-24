/*
    WRITE CLOSE / OPEN FUNCTIONS
    INCLUDE ERROR LOGIC IN VENT_DRIVER_INIT
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
        printf("DUTY CHANGED TO CLOSE!\n");

        if(vent_sys->vsv1_enabled){
            printf("MOSFET 1 SWITCH ON!\n");
            gpio_set_level(OUT_VSPM1_PIN, 1);
        }
        
        if(vent_sys->vsv2_enabled){
            printf("MOSFET 2 SWITCH ON!\n");
            gpio_set_level(OUT_VSPM2_PIN, 1);
        }

        vent_sys->vsrs_tick = xTaskGetTickCount();
        vent_sys->vsp_code = 1;
        printf("TICK UPDATED: %ld!\n", vent_sys->vsrs_tick);
    }
}

void vent_opn(vsrp_dataset *vent_sys){
    if(!vent_sys->vsrs_tick){
        pwm_set_duty(OUT_PWM_CHANNEL, SERVO_DUTY_OPEN);
        printf("DUTY CHANGED TO OPEN!\n");

        if(vent_sys->vsv1_enabled){
            printf("MOSFET 1 SWITCH ON!\n");
            gpio_set_level(OUT_VSPM1_PIN, 1);
        }
        
        if(vent_sys->vsv2_enabled){
            printf("MOSFET 2 SWITCH ON!\n");
            gpio_set_level(OUT_VSPM2_PIN, 1);
        }

        vent_sys->vsrs_tick = xTaskGetTickCount();
        vent_sys->vsp_code = 2;
        printf("TICK UPDATED: %ld!\n", vent_sys->vsrs_tick);
    }
}



void vent_ack(vsrp_dataset *vent_sys){
    if(vent_sys->vsrs_tick){
        printf("VENT ACK INSIDE CONDITION!\n");
        
        if((xTaskGetTickCount() - vent_sys->vsrs_tick) >= pdMS_TO_TICKS(5000)){
            switch(vent_sys->vsp_code){
                case 1:
                //vsp_code = 1 -> close -> waiting for revision
                //end switch conditions
                break;
                case 2:
                //vsp_code = 2 -> open -> waiting for revision
                //end switch conditions
                break;
                default:
                vent_sys->vsp_code = 0;
                vent_sys->vsrs_tick = 0;
                break;
            }

            printf("TIMER RUNOUT!\n");
        }
    }
}















/*
    BELLOW IS ONLY TESTING CODE
    VALUES OF DUTY OPEN AND DUTY CLOSED WILL BE HARDCODED IN HEADER FILE AS MACRO
    WHILE REMOVING ALSO REMOVE #include <stdio.h>!!!
*/
void calc_duty(uint32_t deg){
    const uint32_t SERVO_MIN_PW_US = 500;
    const uint32_t SERVO_MAX_PW_US = 2500;
    const uint32_t SERVO_MAX_DEG = 180;
    const uint32_t PERIOD_US = 20000;

    unsigned int pw = SERVO_MIN_PW_US + (SERVO_MAX_PW_US - SERVO_MIN_PW_US) * deg / SERVO_MAX_DEG;
    uint32_t duty = (pw * MAX_DUTY) / PERIOD_US;

    printf("ESP LOG: Duty value for angle %ld = %ld.\n", deg, duty);
}