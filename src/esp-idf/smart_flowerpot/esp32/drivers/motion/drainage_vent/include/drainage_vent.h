#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#include "pwm_generator.h"

#define SYS_DRAIN_VENT_PWM_CHNL LEDC_CHANNEL_0
#define SYS_DRAIN_VENT_PWM_TIME LEDC_TIMER_0
#define OUT_DRAIN_VENT_PWM GPIO_NUM_13

#define OUT_DRAIN_VENT_SPM1 GPIO_NUM_32
#define IN_DRAIN_VENT_ESC1 GPIO_NUM_34
#define IN_DRAIN_VENT_ESO1 GPIO_NUM_35

#define OUT_DRAIN_VENT_SPM2 GPIO_NUM_33
#define IN_DRAIN_VENT_ESC2 GPIO_NUM_36
#define IN_DRAIN_VENT_ESO2 GPIO_NUM_39

typedef struct{
    TickType_t action_start_tick;

    TickType_t v1_opn_tick;
    TickType_t v1_cls_tick;
    TickType_t v2_opn_tick;
    TickType_t v2_cls_tick;

    uint32_t v1_opn_duty;
    uint32_t v1_cls_duty;
    uint32_t v2_opn_duty;
    uint32_t v2_cls_duty;

    uint16_t err_word;
    uint8_t io_byte;
    uint8_t tmp_byte;
} drainage_vent_dataset_t;

void drainage_vent_init();
drainage_vent_dataset_t init_dataset();