#include "drainage_vent.h"
#include "roulette.h"



/*************** START of temp code - ROULETTE and VENT testing */
#define TMP_VENT_OPEN GPIO_NUM_4
#define TMP_VENT_CLOSE GPIO_NUM_27
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

roulette_init();
roulette_dataset_t roulette_sys = roulette_init_dataset();




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
            roulette_sys.io_byte = (roulette_sys.io_byte & 0xFC) | 0x01;
        }

        if(gpio_get_level(TMP_ROULETTE_CLOSE)){
            printf("R-LOG:\tclose request!\n");
            roulette_sys.io_byte = (roulette_sys.io_byte & 0xFC) | 0x02;
        }
        /*************** END of temp code - ROULETTE and VENT testing */



        //drainage_vent_print(&drainage_vent_sys);
        drainage_vent_fsm(&drainage_vent_sys);


        roulette_print(&roulette_sys);
        roulette_fsm(&roulette_sys);

        //vTaskDelay(pdMS_TO_TICKS(1));
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
