#include "vent_driver.h"

void app_main(void){
    //init
    vsrp_dataset vs = {
        .vscp_timer = NULL,
        .vsrs_tick = 0,
        .vsp_code = 0,
        .vsv1_enabled = 1,
        .vsv2_enabled = 1
    };
    vent_driver_init(&vs);


    
    vent_opn(&vs);
    
    //loop
    while(1){
        vent_ack(&vs);

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}