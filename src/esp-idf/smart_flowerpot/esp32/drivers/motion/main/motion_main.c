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

    int i = 0;
    int closing = 1;
    roulette_cls(&roulette_sys);
    printf("closing\n");

//loop
    while(1){
        //printf("\033[H\033[J");        
/*
        printf("ESO1:\t%d\n", gpio_get_level(IN_ROULETTE_ESO1));
        printf("ESC1:\t%d\n", gpio_get_level(IN_ROULETTE_ESC1));
        printf("ESO2:\t%d\n", gpio_get_level(IN_ROULETTE_ESO2));
        printf("ESC2:\t%d\n", gpio_get_level(IN_ROULETTE_ESC2));
*/
        drainage_vent_ack(&drainage_vent_sys);
        roulette_ack(&roulette_sys);

        if(i >= 120){
            i = 0;

            if(closing){
                roulette_opn(&roulette_sys);
                printf("opening\n");
            }
            else{
                roulette_cls(&roulette_sys);
                printf("closing\n");
            }

            closing = !closing;
        }
        i++;

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
