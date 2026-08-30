/*

#define ROULETTE_MOVE_CLOSE_DELAY_MS    60000
#define ROULETTE_MOVE_OPEN_DELAY_MS     72000

*/

#include "roulette.h"

void roulette_init(){
//init out gpio
    gpio_set_direction(OUT_ROULETTE_EN1, GPIO_MODE_OUTPUT);
    gpio_set_direction(OUT_ROULETTE_DIR1, GPIO_MODE_OUTPUT);
    gpio_set_direction(OUT_ROULETTE_DIR2, GPIO_MODE_OUTPUT);
    gpio_set_level(OUT_ROULETTE_EN1, 0);
    gpio_set_level(OUT_ROULETTE_DIR1, 0);
    gpio_set_level(OUT_ROULETTE_DIR2, 0);
    
//init in gpio
    gpio_set_direction(IN_ROULETTE_TOP1, GPIO_MODE_INPUT);
    gpio_set_direction(IN_ROULETTE_TOP2, GPIO_MODE_INPUT);
    gpio_set_direction(IN_ROULETTE_BOT1, GPIO_MODE_INPUT);
    gpio_set_direction(IN_ROULETTE_BOT2, GPIO_MODE_INPUT);
}

roulette_dataset_t roulette_init_dataset(){
    roulette_dataset_t res = {
        .action_start_tick = 0,

        .r1_opn_ms = 720,
        .r1_cls_ms = 600,

        .err_word = 0x0000,
        .io_byte = 0x10,
        .ctrl_byte = 0x00
    };

    return res;
}

void roulette_print(const roulette_dataset_t *roulette_sys){
    if(roulette_sys == NULL) return;

    printf("\n");
    printf("========================================\n");
    printf("Roulette dataset:\n");
    printf("========================================\n");

    printf("\taction_start_tick : %lu\n", (unsigned long)roulette_sys->action_start_tick);

    printf("\tr1_opn_ms         : %lu\n", (unsigned long)roulette_sys->r1_opn_ms);
    printf("\tr1_cls_ms         : %lu\n", (unsigned long)roulette_sys->r1_cls_ms);

    printf("\terr_word          : 0x%04X\n", roulette_sys->err_word);
    printf("\tio_byte           : 0x%02X\n", roulette_sys->io_byte);
    printf("\tctrl_byte         : 0x%02X\n", roulette_sys->ctrl_byte);

    printf("========================================\n");
    printf("Roulette end switches:\n");
    printf("========================================\n");

    printf("\ttop1:             : %d\n", gpio_get_level(IN_ROULETTE_TOP1));
    printf("\ttop2:             : %d\n", gpio_get_level(IN_ROULETTE_TOP2));
    printf("\tbot1:             : %d\n", gpio_get_level(IN_ROULETTE_BOT1));
    printf("\tbot2:             : %d\n", gpio_get_level(IN_ROULETTE_BOT2));

    printf("========================================\n");
}

static inline void r1_switch_off(uint32_t *ticks){
    gpio_set_level(OUT_ROULETTE_DIR1, 0);
    gpio_set_level(OUT_ROULETTE_DIR2, 0);
    gpio_set_level(OUT_ROULETTE_EN1, 0);
    *ticks = 0;
}

void roulette_fsm(roulette_dataset_t *roulette_sys){
    switch(roulette_sys->ctrl_byte & 0x0F){
        case 0:
            if(roulette_sys->io_byte & 0x03){
                roulette_sys->ctrl_byte = ((roulette_sys->io_byte & 0x03) << 4) | 0x01;
            }
        break;
        
        case 1:
            if(roulette_sys->io_byte & 0x10){
                roulette_sys->action_start_tick = xTaskGetTickCount();
                
                uint8_t dir_byte = (roulette_sys->ctrl_byte & 0x30) >> 4;
                if(dir_byte == 1){
                    gpio_set_level(OUT_ROULETTE_DIR1, 0);
                    gpio_set_level(OUT_ROULETTE_DIR2, 1);
                }
                else if(dir_byte == 2){
                    gpio_set_level(OUT_ROULETTE_DIR1, 1);
                    gpio_set_level(OUT_ROULETTE_DIR2, 0);
                }
                
                gpio_set_level(OUT_ROULETTE_EN1, 1);

                roulette_sys->ctrl_byte = (roulette_sys->ctrl_byte & 0xF0) | 0x02;
            }
            else{
                roulette_sys->ctrl_byte = (roulette_sys->ctrl_byte & 0xF0) | 0x04;
            }
        break;
        
        case 2:
        {
            uint8_t dir_byte = (roulette_sys->ctrl_byte & 0x30) >> 4;
            if(dir_byte == 1){
                if(gpio_get_level(IN_ROULETTE_TOP1) || gpio_get_level(IN_ROULETTE_TOP2)){
                    //here I can add some acknowledge for user that roulette1 is opened
                    r1_switch_off(&roulette_sys->action_start_tick);
                    roulette_sys->ctrl_byte = (roulette_sys->ctrl_byte & 0xF0) | 0x03;
                }
                else{
                    if(pdMS_TO_TICKS(xTaskGetTickCount() - roulette_sys->action_start_tick) > roulette_sys->r1_opn_ms){
                        //here I can add some alarm (NOT OPEN) that emergency switch off timer was activated
                        r1_switch_off(&roulette_sys->action_start_tick);
                        roulette_sys->io_byte &= 0xEF;
                        roulette_sys->ctrl_byte = (roulette_sys->ctrl_byte & 0xF0) | 0x04;
                    }
                }
            }
            else if(dir_byte == 2){
                if(gpio_get_level(IN_ROULETTE_BOT1) || gpio_get_level(IN_ROULETTE_BOT2)){
                    //here I can add some acknowledge for user that roulette1 is closed
                    r1_switch_off(&roulette_sys->action_start_tick);
                    roulette_sys->ctrl_byte = (roulette_sys->ctrl_byte & 0xF0) | 0x03;
                }
                else{
                    if(pdMS_TO_TICKS(xTaskGetTickCount() - roulette_sys->action_start_tick) > roulette_sys->r1_cls_ms){
                        //here I can add some alarm (NOT CLOSE) that emergency switch off timer was activated
                        r1_switch_off(&roulette_sys->action_start_tick);
                        roulette_sys->io_byte &= 0xEF;
                        roulette_sys->ctrl_byte = (roulette_sys->ctrl_byte & 0xF0) | 0x04;
                    }
                }
            }
        }
        break;

        case 3:
        {
            uint8_t dir_byte = (roulette_sys->ctrl_byte & 0x30) >> 4;
            if(dir_byte == 1){
                if(!(gpio_get_level(IN_ROULETTE_TOP1) && gpio_get_level(IN_ROULETTE_TOP2))){
                    //here I can add some alarm for user that one of limit switch is not active while second is
                }
            }
            else if(dir_byte == 2){
                if(gpio_get_level(IN_ROULETTE_BOT1) || gpio_get_level(IN_ROULETTE_BOT2)){
                    //here I can add some alarm for user that one of limit switch is not active while second is
                }
            }

            roulette_sys->ctrl_byte = (roulette_sys->ctrl_byte & 0xF0) | 0x04;
        }
        break;

        case 4:
            roulette_sys->io_byte &= 0xFC;
            roulette_sys->ctrl_byte &= 0xC0;
        break;
    }
}
