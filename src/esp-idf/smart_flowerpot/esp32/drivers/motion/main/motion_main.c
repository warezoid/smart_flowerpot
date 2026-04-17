#include "drainage_vent.h"
#include "roulette.h"

void app_main(void){
//init
    drainage_vent_dataset_t drainage_vent_sys = {
        .power_cut_off_timer = NULL,
        .event_start_tick = 0,
        .control_flags = 0b11000000
    };
    drainage_vent_init(&drainage_vent_sys);
    drainage_vent_cls(&drainage_vent_sys);

    roulette_dataset_t roulette_sys = {
        .power_cut_off_timer = NULL,
        .event_start_tick = 0,
        .control_flags = 0b11000000
    };
    roulette_init(&roulette_sys);
    roulette_cls(&roulette_sys);

//loop
    while(1){
        //printf("\033[H\033[J");

        drainage_vent_ack(&drainage_vent_sys);
        

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
