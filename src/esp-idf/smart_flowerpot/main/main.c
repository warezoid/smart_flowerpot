#include "vent_driver.h"

/****************TEST CODE*********************/
void test_open(){
    printf("open\n");
    pwm_set_duty(OUT_PWM_CHANNEL, SERVO_DUTY_OPEN);
}

void test_close(){
    printf("close\n");
    pwm_set_duty(OUT_PWM_CHANNEL, SERVO_DUTY_CLOSE);
}

int test_opened = 1;
/*************************************/


void app_main(void){
    printf("hello from esp\n");

    //init
    vsrp_dataset vs = {
        .vscp_timer = NULL,
        .vsrs_tick = 0,
        .vsp_code = 0,
        .vsv1_enabled = 1,
        .vsv2_enabled = 1
    };
    vent_driver_init(&vs);  //this should return if init is done or error occured!

    printf("init\n");
    gpio_set_level(OUT_VSPM1_PIN, 1);
    gpio_set_level(OUT_VSPM2_PIN, 1);


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
