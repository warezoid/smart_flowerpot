#include "drainage_vent.h"
#include "roulette.h"



/*************** START of temp code - ROULETTE and VENT testing */
#define TMP_VENT_OPEN GPIO_NUM_17
#define TMP_VENT_CLOSE GPIO_NUM_21
#define TMP_ROULETTE_OPEN GPIO_NUM_25 
#define TMP_ROULETTE_CLOSE GPIO_NUM_26
/*************** END of temp code - ROULETTE and VENT testing */



void app_main(void){
/*************** START of temp code - ROULETTE and VENT testing */
    gpio_set_direction(TMP_VENT_OPEN, GPIO_MODE_INPUT);
    gpio_set_direction(TMP_VENT_CLOSE, GPIO_MODE_INPUT);
    gpio_set_direction(TMP_ROULETTE_OPEN, GPIO_MODE_INPUT);
    gpio_set_direction(TMP_ROULETTE_CLOSE, GPIO_MODE_INPUT);
/*************** END of temp code - ROULETTE and VENT testing */

//init
drainage_vent_init();
drainage_vent_dataset_t drainage_vent_sys = drainage_vent_init_dataset();


    roulette_dataset_t roulette_sys = {
        .power_cut_off_timer = NULL,
        .event_start_tick = 0,
        .control_flags = 0b00000100
    };
    roulette_init(&roulette_sys);


//loop
    while(1){
        /*************** START of temp code - ROULETTE and VENT testing */
        printf("\033[H\033[J");

        if(gpio_get_level(TMP_VENT_OPEN)){
            printf("V-LOG:\topen request!\n");
            drainage_vent_sys.io_byte = (drainage_vent_sys.io_byte & 0xFC) | 0x01;
        }

        if(gpio_get_level(TMP_VENT_CLOSE)){
            printf("V-LOG:\tclose request!\n");
            drainage_vent_sys.io_byte = (drainage_vent_sys.io_byte & 0xFC) | 0x02;          
        }

        if(gpio_get_level(TMP_ROULETTE_OPEN)){
            printf("R-LOG:\topen request!\n");
            roulette_opn(&roulette_sys);
        }

        if(gpio_get_level(TMP_ROULETTE_CLOSE)){
            printf("R-LOG:\tclose request!\n");
            roulette_cls(&roulette_sys);
        }
        /*************** END of temp code - ROULETTE and VENT testing */
/*
        printf("ESO1: %d\n", gpio_get_level(IN_DRAIN_VENT_ESO1));
        printf("ESC1: %d\n", gpio_get_level(IN_DRAIN_VENT_ESC1));
        printf("ESO2: %d\n", gpio_get_level(IN_DRAIN_VENT_ESO2));
        printf("ESC2: %d\n", gpio_get_level(IN_DRAIN_VENT_ESC2));
*/
        drainage_vent_print_dataset(&drainage_vent_sys);
        drainage_vent_fsm(&drainage_vent_sys);



        roulette_ack(&roulette_sys);



        //vTaskDelay(pdMS_TO_TICKS(1));
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
