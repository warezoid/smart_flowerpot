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
    //drainage_vent_cls(&drainage_vent_sys);

    roulette_dataset_t roulette_sys = {
        .power_cut_off_timer = NULL,
        .event_start_tick = 0,
        .control_flags = 0b00000100
    };
    roulette_init(&roulette_sys);

    //roulette_opn(&roulette_sys);
    gpio_set_level(OUT_DRAIN_VENT_SPM1, 1);
    gpio_set_level(OUT_DRAIN_VENT_SPM2, 1);
    
    //pwm_generator_set_duty(SYS_DRAIN_VENT_PWM_CHNL, SERVO_DUTY_OPEN);

    int i = 0;
//loop
    while(1){
        printf("\033[H\033[J");        
        printf("ESO1:\t\t%d\n", gpio_get_level(IN_DRAIN_VENT_ESO1));
        printf("ESC1:\t\t%d\n", gpio_get_level(IN_DRAIN_VENT_ESC1));
        printf("ESO2:\t\t%d\n", gpio_get_level(IN_DRAIN_VENT_ESO2));
        printf("ESC2:\t\t%d\n", gpio_get_level(IN_DRAIN_VENT_ESC2));      
/*
        if(i){
            pwm_generator_set_duty(SYS_DRAIN_VENT_PWM_CHNL, SERVO_DUTY_OPEN);
            printf("open!\n");
        }
        else{
            pwm_generator_set_duty(SYS_DRAIN_VENT_PWM_CHNL, SERVO_DUTY_CLOSE);
            printf("close!\n");
        }
        
        i = !i;
*/
        vTaskDelay(pdMS_TO_TICKS(5000));

        //drainage_vent_ack(&drainage_vent_sys);
        //roulette_ack(&roulette_sys);
    }
}
