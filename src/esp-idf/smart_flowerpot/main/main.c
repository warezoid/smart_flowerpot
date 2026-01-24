#include "vent_driver.h"

void app_main(void){
    //init
    vent_driver_init();

    //vent
    vsrp_dataset vs = {
        .vsrs_tick = 0,
        .vsp_code = 0,
        .vsv1_enabled = 1,
        .vsv2_enabled = 1,
        .errcode_1 = 0,
        .errcode_2 = 0
    };

    vent_cls(&vs);

    //loop
    while(1){
        vent_ack(&vs);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}