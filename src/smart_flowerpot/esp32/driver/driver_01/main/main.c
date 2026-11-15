#include "bottom_vent.h"

void app_main(void){
//init
    bottom_vent_init();
    bottom_vent_dataset_t bottom_vent_sys = bottom_vent_init_dataset();

    //bottom_vent_sys.io_byte = (bottom_vent_sys.io_byte & 0xFC) | 0x01;    //open - bottom vent
    bottom_vent_sys.io_byte = (bottom_vent_sys.io_byte & 0xFC) | 0x02;    //close - bottom vent

//loop
    while(1){
        printf("\033[H\033[J");

        bottom_vent_print(&bottom_vent_sys);
        bottom_vent_fsm(&bottom_vent_sys);

        //vTaskDelay(pdMS_TO_TICKS(1));
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
