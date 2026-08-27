#include "drainage_vent.h"

void drainage_vent_init(){
//init out gpio
    gpio_set_direction(OUT_DRAIN_VENT_SPM1, GPIO_MODE_OUTPUT);
    gpio_set_direction(OUT_DRAIN_VENT_SPM2, GPIO_MODE_OUTPUT);
    gpio_set_level(OUT_DRAIN_VENT_SPM1, 0);
    gpio_set_level(OUT_DRAIN_VENT_SPM2, 0);
    
//init in gpio
    gpio_set_direction(IN_DRAIN_VENT_ESO1, GPIO_MODE_INPUT);
    gpio_set_direction(IN_DRAIN_VENT_ESO2, GPIO_MODE_INPUT);
    gpio_set_direction(IN_DRAIN_VENT_ESC1, GPIO_MODE_INPUT);
    gpio_set_direction(IN_DRAIN_VENT_ESC2, GPIO_MODE_INPUT);

//init pwm_generator
    pwm_generator_config_t pwm_cfg = {
        .timer = SYS_DRAIN_VENT_PWM_TIME,
        .channel = SYS_DRAIN_VENT_PWM_CHNL,
        .freq_hz = 50,
        .out_pin = OUT_DRAIN_VENT_PWM
    };
    pwm_generator_init(&pwm_cfg);
    pwm_generator_set_duty(SYS_DRAIN_VENT_PWM_CHNL, 0);
}

drainage_vent_dataset_t drainage_vent_init_dataset(){
    drainage_vent_dataset_t res = {
        .action_start_tick = 0,

        .v1_opn_ms = 50,
        .v1_cls_ms = 50,
        .v2_opn_ms = 50,
        .v2_cls_ms = 50,

        .v1_opn_duty = 200,
        .v1_cls_duty = 700,
        .v2_opn_duty = 200,
        .v2_cls_duty = 600,

        .err_word = 0x0000,
        .io_byte = 0x30,
        .ctrl_byte = 0x00
    };

    return res;
}

void drainage_vent_print_dataset(const drainage_vent_dataset_t *vent_sys){
    if(vent_sys == NULL) return;

    printf("\n");
    printf("========================================\n");
    printf("Drainage vent dataset:\n");
    printf("========================================\n");

    printf("\taction_start_tick : %lu\n", (unsigned long)vent_sys->action_start_tick);

    printf("\tv1_opn_ms       : %lu\n", (unsigned long)vent_sys->v1_opn_ms);
    printf("\tv1_cls_ms       : %lu\n", (unsigned long)vent_sys->v1_cls_ms);
    printf("\tv2_opn_ms       : %lu\n", (unsigned long)vent_sys->v2_opn_ms);
    printf("\tv2_cls_ms       : %lu\n", (unsigned long)vent_sys->v2_cls_ms);

    printf("\tv1_opn_duty       : %lu\n", (unsigned long)vent_sys->v1_opn_duty);
    printf("\tv1_cls_duty       : %lu\n", (unsigned long)vent_sys->v1_cls_duty);
    printf("\tv2_opn_duty       : %lu\n", (unsigned long)vent_sys->v2_opn_duty);
    printf("\tv2_cls_duty       : %lu\n", (unsigned long)vent_sys->v2_cls_duty);

    printf("\terr_word          : 0x%04X\n", vent_sys->err_word);
    printf("\tio_byte           : 0x%02X\n", vent_sys->io_byte);
    printf("\tctrl_byte         : 0x%02X\n", vent_sys->ctrl_byte);

    printf("========================================\n");
}

static inline void v1_switch_off(uint32_t *ticks){
    pwm_generator_set_duty(SYS_DRAIN_VENT_PWM_CHNL, 0);
    gpio_set_level(OUT_DRAIN_VENT_SPM1, 0);
    *ticks = 0;
}

static inline void v2_switch_off(uint32_t *ticks){
    pwm_generator_set_duty(SYS_DRAIN_VENT_PWM_CHNL, 0);
    gpio_set_level(OUT_DRAIN_VENT_SPM2, 0);
    *ticks = 0;
}

void drainage_vent_fsm(drainage_vent_dataset_t *vent_sys){
    switch(vent_sys->ctrl_byte & 0x0F){
        case 0:
            if(vent_sys->io_byte & 0x03){
                vent_sys->ctrl_byte = ((vent_sys->io_byte & 0x03) << 4) | 0x01;
            }
        break;
        
        case 1:
            if(vent_sys->io_byte & 0x10){
                vent_sys->action_start_tick = xTaskGetTickCount();
                gpio_set_level(OUT_DRAIN_VENT_SPM1, 1);
                
                uint8_t dir_byte = (vent_sys->ctrl_byte & 0x30) >> 4;
                if(dir_byte == 1){
                    pwm_generator_set_duty(SYS_DRAIN_VENT_PWM_CHNL, vent_sys->v1_opn_duty);
                }
                else if(dir_byte == 2){
                    pwm_generator_set_duty(SYS_DRAIN_VENT_PWM_CHNL, vent_sys->v1_cls_duty);
                }

                vent_sys->ctrl_byte = (vent_sys->ctrl_byte & 0xF0) | 0x02;
            }
            else{
                vent_sys->ctrl_byte = (vent_sys->ctrl_byte & 0xF0) | 0x03;
            }
        break;
        
        case 2:
        {
            uint8_t dir_byte = (vent_sys->ctrl_byte & 0x30) >> 4;
            if(dir_byte == 1){
                if(gpio_get_level(IN_DRAIN_VENT_ESO1)){
                    //here I can add some acknowledge for user that vent1 is opened
                    v1_switch_off(&vent_sys->action_start_tick);
                    vent_sys->ctrl_byte = (vent_sys->ctrl_byte & 0xF0) | 0x03;
                }
                else{
                    if(pdMS_TO_TICKS(xTaskGetTickCount() - vent_sys->action_start_tick) > vent_sys->v1_opn_ms){
                        //here I can add some alarm (NOT OPEN) that emergency switch off timer was activated
                        v1_switch_off(&vent_sys->action_start_tick);
                        vent_sys->io_byte &= 0xEF;
                        vent_sys->ctrl_byte = (vent_sys->ctrl_byte & 0xF0) | 0x03;
                    }
                }
            }
            else if(dir_byte == 2){
                if(gpio_get_level(IN_DRAIN_VENT_ESC1)){
                    //here I can add some acknowledge for user that vent1 is closed
                    v1_switch_off(&vent_sys->action_start_tick);
                    vent_sys->ctrl_byte = (vent_sys->ctrl_byte & 0xF0) | 0x03;
                }
                else{
                    if(pdMS_TO_TICKS(xTaskGetTickCount() - vent_sys->action_start_tick) > vent_sys->v1_cls_ms){
                        //here I can add some alarm (NOT CLOSE) that emergency switch off timer was activated
                        v1_switch_off(&vent_sys->action_start_tick);
                        vent_sys->io_byte &= 0xEF;
                        vent_sys->ctrl_byte = (vent_sys->ctrl_byte & 0xF0) | 0x03;
                    }
                }
            }
        }
        break;

        case 3:
            if(vent_sys->io_byte & 0x20){
                vent_sys->action_start_tick = xTaskGetTickCount();
                gpio_set_level(OUT_DRAIN_VENT_SPM2, 1);
                
                uint8_t dir_byte = (vent_sys->ctrl_byte & 0x30) >> 4;
                if(dir_byte == 1){
                    pwm_generator_set_duty(SYS_DRAIN_VENT_PWM_CHNL, vent_sys->v2_opn_duty);
                }
                else if(dir_byte == 2){
                    pwm_generator_set_duty(SYS_DRAIN_VENT_PWM_CHNL, vent_sys->v2_cls_duty);
                }

                vent_sys->ctrl_byte = (vent_sys->ctrl_byte & 0xF0) | 0x04;
            }
            else{
                vent_sys->ctrl_byte = (vent_sys->ctrl_byte & 0xF0) | 0x05;
            }
        break;

        case 4:
        {
            uint8_t dir_byte = (vent_sys->ctrl_byte & 0x30) >> 4;
            if(dir_byte == 1){
                if(gpio_get_level(IN_DRAIN_VENT_ESO2)){
                    //here I can add some acknowledge for user that vent2 is opened
                    v2_switch_off(&vent_sys->action_start_tick);
                    vent_sys->ctrl_byte = (vent_sys->ctrl_byte & 0xF0) | 0x05;
                }
                else{
                    if(pdMS_TO_TICKS(xTaskGetTickCount() - vent_sys->action_start_tick) > vent_sys->v2_opn_ms){
                        //here I can add some alarm (NOT OPEN) that emergency switch off timer was activated
                        v2_switch_off(&vent_sys->action_start_tick);
                        vent_sys->io_byte &= 0xDF;
                        vent_sys->ctrl_byte = (vent_sys->ctrl_byte & 0xF0) | 0x05;
                    }
                }
            }
            else if(dir_byte == 2){
                if(gpio_get_level(IN_DRAIN_VENT_ESC2)){
                    //here I can add some acknowledge for user that vent2 is closed
                    v2_switch_off(&vent_sys->action_start_tick);
                    vent_sys->ctrl_byte = (vent_sys->ctrl_byte & 0xF0) | 0x05;
                }
                else{
                    if(pdMS_TO_TICKS(xTaskGetTickCount() - vent_sys->action_start_tick) > vent_sys->v2_cls_ms){
                        //here I can add some alarm (NOT CLOSE) that emergency switch off timer was activated
                        v2_switch_off(&vent_sys->action_start_tick);
                        vent_sys->io_byte &= 0xDF;
                        vent_sys->ctrl_byte = (vent_sys->ctrl_byte & 0xF0) | 0x05;
                    }
                }
            }
        }
        break;

        case 5:
            vent_sys->io_byte &= 0xFC;
            vent_sys->ctrl_byte &= 0xC0;
        break;
    }
}
