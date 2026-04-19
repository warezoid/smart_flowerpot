#include "roulette.h"
#include <stdio.h>

static void power_cut_off_callback(void *arg){
    gpio_set_level(OUT_ROULETTE_EN1, 0);
    gpio_set_level(OUT_ROULETTE_EN2, 0);
    gpio_set_level(OUT_ROULETTE_DIR1, 0);
    gpio_set_level(OUT_ROULETTE_DIR2, 0);
}

void roulette_init(roulette_dataset_t *roulette_sys){
//init out gpio
    gpio_set_direction(OUT_ROULETTE_EN1, GPIO_MODE_OUTPUT);
    gpio_set_direction(OUT_ROULETTE_EN2, GPIO_MODE_OUTPUT);
    gpio_set_direction(OUT_ROULETTE_DIR1, GPIO_MODE_OUTPUT);
    gpio_set_direction(OUT_ROULETTE_DIR2, GPIO_MODE_OUTPUT);
    gpio_set_level(OUT_ROULETTE_EN1, 0);
    gpio_set_level(OUT_ROULETTE_EN2, 0);
    gpio_set_level(OUT_ROULETTE_DIR1, 0);
    gpio_set_level(OUT_ROULETTE_DIR2, 0);
    
//init in gpio
    gpio_set_direction(IN_ROULETTE_ESO1, GPIO_MODE_INPUT);
    gpio_set_direction(IN_ROULETTE_ESO2, GPIO_MODE_INPUT);
    gpio_set_direction(IN_ROULETTE_ESC1, GPIO_MODE_INPUT);
    gpio_set_direction(IN_ROULETTE_ESC2, GPIO_MODE_INPUT);

//init power_cut_off_timer
    esp_timer_create_args_t pwr_cut_off_cfg = {
        .callback = power_cut_off_callback,
        .arg = NULL,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "power_cut_off_timer"
    };
    esp_timer_create(&pwr_cut_off_cfg, &(roulette_sys->power_cut_off_timer));
}

void roulette_cls(roulette_dataset_t *roulette_sys){
    if(!roulette_sys->event_start_tick){
        if(roulette_sys->control_flags & 0xC0){
            printf("STATE:\tCLOSING\n");

            gpio_set_level(OUT_ROULETTE_DIR1, 0);
            gpio_set_level(OUT_ROULETTE_DIR2, 1);

            if(roulette_sys->control_flags & 0x40) gpio_set_level(OUT_ROULETTE_EN1, 1);
            if(roulette_sys->control_flags & 0x80) gpio_set_level(OUT_ROULETTE_EN2, 1);

            if(!esp_timer_is_active(roulette_sys->power_cut_off_timer)) esp_timer_start_once(roulette_sys->power_cut_off_timer, ROULETTE_MOVE_DELAY_MS * 1000);
            roulette_sys->event_start_tick = xTaskGetTickCount();

            roulette_sys->control_flags &= 0xC0;
            roulette_sys->control_flags |= 0x01;
        }
    }
}

void roulette_opn(roulette_dataset_t *roulette_sys){
    if(!roulette_sys->event_start_tick){
        if(roulette_sys->control_flags & 0xC0){
            printf("STATE:\tOPENING\n");

            gpio_set_level(OUT_ROULETTE_DIR1, 1);
            gpio_set_level(OUT_ROULETTE_DIR2, 0);

            if(roulette_sys->control_flags & 0x40) gpio_set_level(OUT_ROULETTE_EN1, 1);
            if(roulette_sys->control_flags & 0x80) gpio_set_level(OUT_ROULETTE_EN2, 1);

            if(!esp_timer_is_active(roulette_sys->power_cut_off_timer)) esp_timer_start_once(roulette_sys->power_cut_off_timer, ROULETTE_MOVE_DELAY_MS * 1000);
            roulette_sys->event_start_tick = xTaskGetTickCount();

            roulette_sys->control_flags &= 0xC0;
            roulette_sys->control_flags |= 0x02;
        }
    }
}

void roulette_ack(roulette_dataset_t *roulette_sys){
    if(roulette_sys->event_start_tick){
        if((xTaskGetTickCount() - roulette_sys->event_start_tick) >= pdMS_TO_TICKS(ROULETTE_MOVE_DELAY_MS + 500)){
            gpio_set_level(OUT_ROULETTE_EN1, 0);
            gpio_set_level(OUT_ROULETTE_EN2, 0);
            gpio_set_level(OUT_ROULETTE_DIR1, 0);
            gpio_set_level(OUT_ROULETTE_DIR2, 0);
            roulette_sys->event_start_tick = 0;

            switch(roulette_sys->control_flags & 0x3F){
                case 1:
                    if(roulette_sys->control_flags & 0x40){
                        if(!gpio_get_level(IN_ROULETTE_ESC1)){
                            roulette_sys->control_flags &= 0xBF;
                            //v1 error
                        }
                    }

                    if(roulette_sys->control_flags & 0x80){
                        if(!gpio_get_level(IN_ROULETTE_ESC2)){
                            roulette_sys->control_flags &= 0x7F;
                            //v2 error
                        }
                    }
                    break;
                case 2:
                    if(roulette_sys->control_flags & 0x40){
                        if(!gpio_get_level(IN_ROULETTE_ESO1)){
                            roulette_sys->control_flags &= 0xBF;
                            //v1 error
                        }
                    }

                    if(roulette_sys->control_flags & 0x80){
                        if(!gpio_get_level(IN_ROULETTE_ESO2)){
                            roulette_sys->control_flags &= 0x7F;
                            //v2 error
                        }
                    }
                    break;
            }

            roulette_sys->control_flags &= 0xC0;
        }
    }
}
