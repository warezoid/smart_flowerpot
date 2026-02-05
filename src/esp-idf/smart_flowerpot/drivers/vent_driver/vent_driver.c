/*
    - CREATE ERROR STRUCTURE FOR VENT AND OTHER ELEMENTS
        - IF ERROR SEND ERROR MESSAGE TO MASTER CONTROLER, WHICH GENERATE ERROR LOG
    - SET TIMERS ONLY IF VSVs are ENABLED
*/

#include <stdio.h>
#include "vent_driver.h"



static void vscp_callback(void *arg){
    gpio_set_level(OUT_VSPM1_PIN, 0);
    gpio_set_level(OUT_VSPM2_PIN, 0);
}

void vent_driver_init(vsrp_dataset *vent_sys){
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

    //init vscp_timer
    esp_timer_create_args_t tmr_cfg = {
        .callback = vscp_callback,
        .arg = NULL,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "vscp"
    };
    esp_timer_create(&tmr_cfg, &(vent_sys->vscp_timer));

    //init pwm_generator
    pwm_init_t pwm_cfg = {
        .timer = LEDC_TIMER_0,
        .frequency_hz = 50,
        .channel = OUT_PWM_CHANNEL,
        .out_pwm_pin = GPIO_NUM_13
    };
    pwm_init(&pwm_cfg);
}



void vent_cls(vsrp_dataset *vent_sys){
    if(!vent_sys->vsrs_tick){
        pwm_set_duty(OUT_PWM_CHANNEL, SERVO_DUTY_CLOSE);

        if(vent_sys->vsv1_enabled) gpio_set_level(OUT_VSPM1_PIN, 1);
        
        if(vent_sys->vsv2_enabled) gpio_set_level(OUT_VSPM2_PIN, 1);

        if(!esp_timer_is_active(vent_sys->vscp_timer)) esp_timer_start_once(vent_sys->vscp_timer, VENT_MOVE_DELAY_MS * 1000);
        vent_sys->vsrs_tick = xTaskGetTickCount();
        vent_sys->vsp_code = 1;
    }
}

void vent_opn(vsrp_dataset *vent_sys){
    if(!vent_sys->vsrs_tick){
        pwm_set_duty(OUT_PWM_CHANNEL, SERVO_DUTY_OPEN);

        if(vent_sys->vsv1_enabled) gpio_set_level(OUT_VSPM1_PIN, 1);

        if(vent_sys->vsv2_enabled) gpio_set_level(OUT_VSPM2_PIN, 1);

        if(!esp_timer_is_active(vent_sys->vscp_timer)) esp_timer_start_once(vent_sys->vscp_timer, VENT_MOVE_DELAY_MS * 1000);
        vent_sys->vsrs_tick = xTaskGetTickCount();
        vent_sys->vsp_code = 2;
    }
}

void vent_ack(vsrp_dataset *vent_sys){
    if(vent_sys->vsrs_tick){
        if((xTaskGetTickCount() - vent_sys->vsrs_tick) >= pdMS_TO_TICKS(VENT_MOVE_DELAY_MS + 500)){
            gpio_set_level(OUT_VSPM1_PIN, 0);
            gpio_set_level(OUT_VSPM2_PIN, 0);
            vent_sys->vsrs_tick = 0;

            switch(vent_sys->vsp_code){
                case 1:
                    if(vent_sys->vsv1_enabled){
                        if(!gpio_get_level(IN_ESC1_PIN)){
                            vent_sys->vsv1_enabled = 0;
                            //SEND ERROR MESSAGE TO MASTER CONTROLER
                        }
                    }

                    if(vent_sys->vsv2_enabled){
                        if(!gpio_get_level(IN_ESC2_PIN)){
                            vent_sys->vsv2_enabled = 0;
                            //SEND ERROR MESSAGE TO MASTER CONTROLER
                        }
                    }
                    break;
                case 2:
                    if(vent_sys->vsv1_enabled){
                        if(!gpio_get_level(IN_ESO1_PIN)){
                            vent_sys->vsv1_enabled = 0;
                            //SEND ERROR MESSAGE TO MASTER CONTROLER
                        }
                    }

                    if(vent_sys->vsv2_enabled){
                        if(!gpio_get_level(IN_ESO2_PIN)){
                            vent_sys->vsv2_enabled = 0;
                            //SEND ERROR MESSAGE TO MASTER CONTROLER
                        }
                    }
                    break;
            }

            vent_sys->vsp_code = 0;
        }
    }
}
