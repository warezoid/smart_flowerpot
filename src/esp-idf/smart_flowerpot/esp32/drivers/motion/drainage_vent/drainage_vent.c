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

drainage_vent_dataset_t init_dataset(){
    drainage_vent_dataset_t res = {
        .action_start_tick = 0,
        .v1_opn_tick = 500,
        .v1_cls_tick = 500,
        .v2_opn_tick = 500,
        .v2_cls_tick = 500,
        .v1_opn_duty = 200,
        .v1_cls_duty = 600,
        .v2_opn_duty = 200,
        .v2_cls_duty = 600,
        .err_word = 0x0000,
        .io_byte = 0x30,
        .tmp_byte = 0x00
    };

    return res;
}
