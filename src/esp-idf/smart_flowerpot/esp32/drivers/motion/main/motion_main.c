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
    //drainage_vent_opn(&drainage_vent_sys);

    roulette_dataset_t roulette_sys = {
        .power_cut_off_timer = NULL,
        .event_start_tick = 0,
        .control_flags = 0b00000100
    };
    roulette_init(&roulette_sys);
/*
    // drainage vent configuration - closed position
    int vent1_position = SERVO_DUTY_OPEN;
    int vent2_position = SERVO_DUTY_OPEN;
*/
/*
    gpio_set_level(OUT_DRAIN_VENT_SPM1, 1);
    gpio_set_level(OUT_DRAIN_VENT_SPM2, 1);
    pwm_generator_set_duty(SYS_DRAIN_VENT_PWM_CHNL, SERVO_DUTY_CLOSE);
*/
    int vent_timer = 0;
    int closed = 1;

//loop
    while(1){
        printf("\033[H\033[J");
        printf("ESO1:\t\t%d\n", gpio_get_level(IN_DRAIN_VENT_ESO1));
        printf("ESC1:\t\t%d\n", gpio_get_level(IN_DRAIN_VENT_ESC1));
        printf("ESO2:\t\t%d\n", gpio_get_level(IN_DRAIN_VENT_ESO2));
        printf("ESC2:\t\t%d\n", gpio_get_level(IN_DRAIN_VENT_ESC2));


        if(vent_timer >= 50){
            if(closed){
                pwm_generator_set_duty(SYS_DRAIN_VENT_PWM_CHNL, SERVO_DUTY_OPEN);
            }
            else{
                pwm_generator_set_duty(SYS_DRAIN_VENT_PWM_CHNL, SERVO_DUTY_CLOSE);
            }

            closed = !closed;
            vent_timer = 0;
        }

        vent_timer++;
        vTaskDelay(pdMS_TO_TICKS(100));

    /*

        if(!gpio_get_level(IN_DRAIN_VENT_ESC1))printf("VENT 1 POSITION: %d\n", vent1_position);
        if(!gpio_get_level(IN_DRAIN_VENT_ESC2))printf("VENT 2 POSITION: %d\n", vent2_position);
    
        if( gpio_get_level(IN_DRAIN_VENT_ESC1) ){
            gpio_set_level(OUT_DRAIN_VENT_SPM1, 0);           
            printf("VENT 1 CLOSED POSITION: %d\n", vent1_position);
        }
        else{
            vent1_position += 5;
        }

        if( gpio_get_level(IN_DRAIN_VENT_ESC2) ){
            gpio_set_level(OUT_DRAIN_VENT_SPM2, 0);
            printf("VENT 2 CLOSED POSITION: %d\n", vent2_position);
        }
        else{
            vent2_position += 5;
        }

        int tmp_pos = vent1_position >= vent2_position ? vent1_position : vent2_position;
        printf("TMP_POS:\t\t%d\n", tmp_pos);
        pwm_generator_set_duty(SYS_DRAIN_VENT_PWM_CHNL, tmp_pos);
   
        vTaskDelay(pdMS_TO_TICKS(500));
*/

        //drainage_vent_ack(&drainage_vent_sys);
        //roulette_ack(&roulette_sys);
    }
}
