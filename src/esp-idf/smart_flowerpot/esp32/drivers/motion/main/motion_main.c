#include <stdio.h>
#include "drainage_vent.h"

/****************TEST CODE*********************/
void test_open(){
    printf("open\n");
    pwm_generator_set_duty(SYS_DRAIN_VENT_PWM_CHNL, SERVO_DUTY_OPEN);
}

void test_close(){
    printf("close\n");
    pwm_generator_set_duty(SYS_DRAIN_VENT_PWM_CHNL, SERVO_DUTY_CLOSE);
}

int test_opened = 1;
/*************************************/


void app_main(void){
    printf("hello from esp\n");

    //init
    drainage_vent_dataset_t drainage_vent_sys = {
        .power_cut_off_timer = NULL,
        .event_start_tick = 0,
        .control_flags = 0b11000000
    };
    drainage_vent_init(&drainage_vent_sys);  //this should return if init is done or error occured!

    printf("init\n");
    gpio_set_level(OUT_DRAIN_VENT_SPM1, 1);
    gpio_set_level(OUT_DRAIN_VENT_SPM2, 1);


    test_open();
    
    //loop
    while(1){
        if(test_opened){
            test_close();
        }
        else{
            test_open();
        }
        test_opened = !test_opened;

        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}
