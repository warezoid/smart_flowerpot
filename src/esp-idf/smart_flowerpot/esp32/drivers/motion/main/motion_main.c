#include "drainage_vent.h"
#include "roulette.h"

void app_main(void){
//init
    drainage_vent_dataset_t drainage_vent_sys = {
        .power_cut_off_timer = NULL,
        .event_start_tick = 0,
        .control_flags = 0b00001100
    };
    drainage_vent_init(&drainage_vent_sys);
    drainage_vent_cls(&drainage_vent_sys);

    roulette_dataset_t roulette_sys = {
        .power_cut_off_timer = NULL,
        .event_start_tick = 0,
        .control_flags = 0b00000100
    };
    roulette_init(&roulette_sys);

    roulette_opn(&roulette_sys);

    //code for getting a approximate value of roulette movement sequency time (closing: 55s | opening: not measured)
    TickType_t ticks_measurements = xTaskGetTickCount();
    printf("TICKS started!\n");

//loop
    while(1){
        //printf("\033[H\033[J");
/*
        printf("ESO1:\t%d\n", gpio_get_level(IN_ROULETTE_ESO1));
        printf("ESC1:\t%d\n", gpio_get_level(IN_ROULETTE_ESC1));
        printf("---\n");
*/
/*
        if( gpio_get_level(IN_ROULETTE_ESC1) ){
            printf("TICKS: %ld\n", pdTICKS_TO_MS( xTaskGetTickCount() - ticks_measurements ));
        }
*/
/*
        drainage_vent_ack(&drainage_vent_sys);
        roulette_ack(&roulette_sys);
*/

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
