#include "drainage_vent.h"

static void power_cut_off_callback(void *arg){
    gpio_set_level(OUT_DRAIN_VENT_SPM1, 0);
    gpio_set_level(OUT_DRAIN_VENT_SPM2, 0);
}

void drainage_vent_init(drainage_vent_dataset_t *vent_sys){
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

//init power_cut_off_timer
    esp_timer_create_args_t pwr_cut_off_cfg = {
        .callback = power_cut_off_callback,
        .arg = NULL,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "power_cut_off_timer"
    };
    esp_timer_create(&pwr_cut_off_cfg, &(vent_sys->power_cut_off_timer));

//init pwm_generator
    pwm_generator_config_t pwm_cfg = {
        .timer = SYS_DRAIN_VENT_PWM_TIME,
        .channel = SYS_DRAIN_VENT_PWM_CHNL,
        .freq_hz = 50,
        .out_pin = OUT_DRAIN_VENT_PWM
    };
    pwm_generator_init(&pwm_cfg);
}

void drainage_vent_cls(drainage_vent_dataset_t *vent_sys){
    if(!vent_sys->event_start_tick){
        if(vent_sys->control_flags & 0xC0){
            pwm_generator_set_duty(SYS_DRAIN_VENT_PWM_CHNL, SERVO_DUTY_CLOSE);

            if(vent_sys->control_flags & 0x40) gpio_set_level(OUT_DRAIN_VENT_SPM1, 1);
            if(vent_sys->control_flags & 0x80) gpio_set_level(OUT_DRAIN_VENT_SPM2, 1);

            if(!esp_timer_is_active(vent_sys->power_cut_off_timer)) esp_timer_start_once(vent_sys->power_cut_off_timer, VENT_MOVE_DELAY_MS * 1000);
            vent_sys->event_start_tick = xTaskGetTickCount();

            vent_sys->control_flags &= 0xC0;
            vent_sys->control_flags |= 0x01;
        }
    }
}

void drainage_vent_opn(drainage_vent_dataset_t *vent_sys){
    if(!vent_sys->event_start_tick){
        if(vent_sys->control_flags & 0xC0){
            pwm_generator_set_duty(SYS_DRAIN_VENT_PWM_CHNL, SERVO_DUTY_OPEN);

            if(vent_sys->control_flags & 0x40) gpio_set_level(OUT_DRAIN_VENT_SPM1, 1);
            if(vent_sys->control_flags & 0x80) gpio_set_level(OUT_DRAIN_VENT_SPM2, 1);

            if(!esp_timer_is_active(vent_sys->power_cut_off_timer)) esp_timer_start_once(vent_sys->power_cut_off_timer, VENT_MOVE_DELAY_MS * 1000);
            vent_sys->event_start_tick = xTaskGetTickCount();

            vent_sys->control_flags &= 0xC0;
            vent_sys->control_flags |= 0x02;
        }
    }
}

void drainage_vent_ack(drainage_vent_dataset_t *vent_sys){
    if(vent_sys->event_start_tick){
        if((xTaskGetTickCount() - vent_sys->event_start_tick) >= pdMS_TO_TICKS(VENT_MOVE_DELAY_MS + 500)){
            gpio_set_level(OUT_DRAIN_VENT_SPM1, 0);
            gpio_set_level(OUT_DRAIN_VENT_SPM2, 0);
            vent_sys->event_start_tick = 0;

            switch(vent_sys->control_flags & 0x3F){
                case 1:
                    if(vent_sys->control_flags & 0x40){
                        if(!gpio_get_level(IN_DRAIN_VENT_ESC1)){
                            vent_sys->control_flags &= 0xBF;
                            //v1 error
                        }
                    }

                    if(vent_sys->control_flags & 0x80){
                        if(!gpio_get_level(IN_DRAIN_VENT_ESC2)){
                            vent_sys->control_flags &= 0x7F;
                            //v2 error
                        }
                    }
                    break;
                case 2:
                    if(vent_sys->control_flags & 0x40){
                        if(!gpio_get_level(IN_DRAIN_VENT_ESO1)){
                            vent_sys->control_flags &= 0xBF;
                            //v1 error
                        }
                    }

                    if(vent_sys->control_flags & 0x80){
                        if(!gpio_get_level(IN_DRAIN_VENT_ESO2)){
                            vent_sys->control_flags &= 0x7F;
                            //v2 error
                        }
                    }
                    break;
            }

            vent_sys->control_flags &= 0xC0;
        }
    }
}
