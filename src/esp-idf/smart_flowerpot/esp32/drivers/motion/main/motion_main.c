#include "drainage_vent.h"
#include "roulette.h"



/*************** START of temp code - ROULETTE and VENT testing */
#define TMP_VENT_OPEN GPIO_NUM_17
#define TMP_VENT_CLOSE GPIO_NUM_21
#define TMP_ROULETTE_OPEN GPIO_NUM_25 
#define TMP_ROULETTE_CLOSE GPIO_NUM_26
/*************** END of temp code - ROULETTE and VENT testing */



void app_main(void){
//init
/*
    drainage_vent_dataset_t drainage_vent_sys = {
        .power_cut_off_timer = NULL,
        .event_start_tick = 0,
        .control_flags = 0b00001100
    };
    drainage_vent_init(&drainage_vent_sys);
    //drainage_vent_opn(&drainage_vent_sys);

    roulette_dataset_t roulette_sys = {
        .power_cut_off_timer = NULL,
        .event_start_tick = 0,
        .control_flags = 0b00000100
    };
    roulette_init(&roulette_sys);
*/


/*************** START of temp code - ROULETTE and VENT testing */
    gpio_set_direction(TMP_VENT_OPEN, GPIO_MODE_INPUT);
    gpio_set_direction(TMP_VENT_CLOSE, GPIO_MODE_INPUT);
    gpio_set_direction(TMP_ROULETTE_OPEN, GPIO_MODE_INPUT);
    gpio_set_direction(TMP_ROULETTE_CLOSE, GPIO_MODE_INPUT);
/*************** END of temp code - ROULETTE and VENT testing */



//loop
    while(1){



        /*************** START of temp code - ROULETTE and VENT testing */
            //printf("\033[H\033[J");

            if(gpio_get_level(TMP_VENT_OPEN)){
                printf("V-LOG:\topen request!\n");
            }

            if(gpio_get_level(TMP_VENT_CLOSE)){
                printf("V-LOG:\tclose request!\n");
            }

            if(gpio_get_level(TMP_ROULETTE_OPEN)){
                printf("R-LOG:\topen request!\n");
            }

            if(gpio_get_level(TMP_ROULETTE_CLOSE)){
                printf("R-LOG:\tclose request!\n");
            }

            vTaskDelay(pdMS_TO_TICKS(100));
        /*************** END of temp code - ROULETTE and VENT testing */


        
        //drainage_vent_ack(&drainage_vent_sys);
        //roulette_ack(&roulette_sys);
    }
}
