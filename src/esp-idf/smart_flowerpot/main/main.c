#include "vent_driver.h"

#define PIN_16 GPIO_NUM_16
#define PIN_17 GPIO_NUM_17

void app_main(void){
    gpio_set_direction(PIN_16, GPIO_MODE_INPUT);
    gpio_set_direction(PIN_17, GPIO_MODE_INPUT);

    //init
    vsrp_dataset vs = {
        .vscp_timer = NULL,
        .vsrs_tick = 0,
        .vsp_code = 0,
        .vsv1_enabled = 1,
        .vsv2_enabled = 1
    };
    vent_driver_init(&vs);
    
    //loop
    while(1){

        if(gpio_get_level(PIN_16)){
            printf("-\n");
            vent_opn(&vs);
        }

        if(gpio_get_level(PIN_17)){
            printf("--\n");
            vent_cls(&vs);
        }

        vent_ack(&vs);

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}