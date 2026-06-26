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



    //code for getting a approximate value of roulette movement sequency time
    TickType_t ticks_measurements = xTaskGetTickCount();
    printf("TICKS started!\n");
    bool just_print = false;



//loop
    while(1){       
        if( gpio_get_level(IN_ROULETTE_ESO1) && !just_print ){
            ticks_measurements = xTaskGetTickCount() - ticks_measurements;
            just_print = true;
        }
        
        printf("ESO1:\t\t%d\n", gpio_get_level(IN_ROULETTE_ESO1));
        printf("ESC1:\t\t%d\n", gpio_get_level(IN_ROULETTE_ESC1));
        if(just_print) printf("MOVEMENT TIME:\t%ld\n", pdTICKS_TO_MS(ticks_measurements));

        if( gpio_get_level(IN_DRAIN_VENT_ESC1) ) roulette_opn(&roulette_sys);
        if( gpio_get_level(IN_DRAIN_VENT_ESO1) ) roulette_cls(&roulette_sys);

        printf("---\n");

        //drainage_vent_ack(&drainage_vent_sys);
        roulette_ack(&roulette_sys);

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
