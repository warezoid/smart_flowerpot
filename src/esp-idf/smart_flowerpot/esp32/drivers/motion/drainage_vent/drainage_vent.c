/*
    - CREATE ERROR STRUCTURE FOR VENT AND OTHER ELEMENTS
        - IF ERROR SEND ERROR MESSAGE TO MASTER CONTROLER, WHICH GENERATE ERROR LOG
*/

#include <stdio.h>
#include "drainage_vent.h"



static void vscp_callback(void *arg){
    gpio_set_level(OUT_DRAIN_VENT_SPM1, 0);
    gpio_set_level(OUT_DRAIN_VENT_SPM2, 0);
}

void vent_driver_init(vsrp_dataset *vent_sys){
    //init out gpio
    gpio_set_direction(OUT_DRAIN_VENT_SPM1, GPIO_MODE_OUTPUT);
    gpio_set_direction(OUT_DRAIN_VENT_SPM2, GPIO_MODE_OUTPUT);
    gpio_set_level(OUT_DRAIN_VENT_SPM1, 0);
    gpio_set_level(OUT_DRAIN_VENT_SPM2, 0);
    
    //init in gpio
    gpio_set_direction(IN_DRAIN_VENT_ESO1, GPIO_MODE_INPUT);
    gpio_set_direction(IN_DRAIN_VENT_ESO2, GPIO_MODE_INPUT);
    gpio_set_direction(IN_DRAIN_VENT_ESC1, GPIO_MODE_INPUT);
    gpio_set_direction(IN_DRAIN_VENT_ESC2, GPIO_MODE_INPUT);

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
        .timer = SYS_DRAIN_VENT_PWM_TIME,
        .frequency_hz = 50,
        .channel = SYS_DRAIN_VENT_PWM_CHNL,
        .out_pwm_pin = OUT_DRAIN_VENT_PWM
    };
    pwm_init(&pwm_cfg);
}



void vent_cls(vsrp_dataset *vent_sys){
    if(!vent_sys->vsrs_tick){
        if(vent_sys->vsv1_enabled || vent_sys->vsv2_enabled){
            printf("Zaviracka\n");
            pwm_set_duty(SYS_DRAIN_VENT_PWM_CHNL, SERVO_DUTY_CLOSE);

            if(vent_sys->vsv1_enabled) gpio_set_level(OUT_DRAIN_VENT_SPM1, 1);
        
            if(vent_sys->vsv2_enabled) gpio_set_level(OUT_DRAIN_VENT_SPM2, 1);

            if(!esp_timer_is_active(vent_sys->vscp_timer)) esp_timer_start_once(vent_sys->vscp_timer, VENT_MOVE_DELAY_MS * 1000);
            vent_sys->vsrs_tick = xTaskGetTickCount();
            vent_sys->vsp_code = 1;
        }
    }
}

void vent_opn(vsrp_dataset *vent_sys){
    if(!vent_sys->vsrs_tick){
        if(vent_sys->vsv1_enabled || vent_sys->vsv2_enabled){
            printf("Oteviracka\n");
            pwm_set_duty(SYS_DRAIN_VENT_PWM_CHNL, SERVO_DUTY_OPEN);

            if(vent_sys->vsv1_enabled) gpio_set_level(OUT_DRAIN_VENT_SPM1, 1);

            if(vent_sys->vsv2_enabled) gpio_set_level(OUT_DRAIN_VENT_SPM2, 1);

            if(!esp_timer_is_active(vent_sys->vscp_timer)) esp_timer_start_once(vent_sys->vscp_timer, VENT_MOVE_DELAY_MS * 1000);
            vent_sys->vsrs_tick = xTaskGetTickCount();
            vent_sys->vsp_code = 2;
        }
    }
}

void vent_ack(vsrp_dataset *vent_sys){
    if(vent_sys->vsrs_tick){
        printf("check!\n");
        if((xTaskGetTickCount() - vent_sys->vsrs_tick) >= pdMS_TO_TICKS(VENT_MOVE_DELAY_MS + 500)){
            printf("check ticks!\n");
            gpio_set_level(OUT_DRAIN_VENT_SPM1, 0);
            gpio_set_level(OUT_DRAIN_VENT_SPM2, 0);
            vent_sys->vsrs_tick = 0;

            switch(vent_sys->vsp_code){
                case 1:
                    printf("check 1!\n");
                    if(vent_sys->vsv1_enabled){
                        if(!gpio_get_level(IN_DRAIN_VENT_ESC1)){
                            vent_sys->vsv1_enabled = 0;
                            //SEND ERROR MESSAGE TO MASTER CONTROLER
                            printf("vs1 error!\n");
                        }
                    }

                    if(vent_sys->vsv2_enabled){
                        if(!gpio_get_level(IN_DRAIN_VENT_ESC2)){
                            vent_sys->vsv2_enabled = 0;
                            //SEND ERROR MESSAGE TO MASTER CONTROLER
                            printf("vs2 error!\n");
                        }
                    }
                    break;
                case 2:
                    printf("check 2!\n");
                    if(vent_sys->vsv1_enabled){
                        if(!gpio_get_level(IN_DRAIN_VENT_ESO1)){
                            vent_sys->vsv1_enabled = 0;
                            //SEND ERROR MESSAGE TO MASTER CONTROLER
                            printf("vs1 error!\n");
                        }
                    }

                    if(vent_sys->vsv2_enabled){
                        if(!gpio_get_level(IN_DRAIN_VENT_ESO2)){
                            vent_sys->vsv2_enabled = 0;
                            //SEND ERROR MESSAGE TO MASTER CONTROLER
                            printf("vs2 error!\n");
                        }
                    }
                    break;
            }

            vent_sys->vsp_code = 0;
        }
    }
}
