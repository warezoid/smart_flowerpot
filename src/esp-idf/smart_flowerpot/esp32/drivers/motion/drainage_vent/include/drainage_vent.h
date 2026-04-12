#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "driver/gpio.h"

#include "pwm_generator.h"

#define SERVO_DUTY_CLOSE 700
#define SERVO_DUTY_OPEN 220
#define VENT_MOVE_DELAY_MS 2500

#define SYS_DRAIN_VENT_PWM_CHNL LEDC_CHANNEL_0
#define SYS_DRAIN_VENT_PWM_TIME LEDC_TIMER_0
#define OUT_DRAIN_VENT_PWM GPIO_NUM_13

#define OUT_DRAIN_VENT_SPM1 GPIO_NUM_32
#define IN_DRAIN_VENT_ESC1 GPIO_NUM_34
#define IN_DRAIN_VENT_ESO1 GPIO_NUM_35

#define OUT_DRAIN_VENT_SPM2 GPIO_NUM_33
#define IN_DRAIN_VENT_ESC2 GPIO_NUM_39
#define IN_DRAIN_VENT_ESO2 GPIO_NUM_36

typedef struct{
    esp_timer_handle_t power_cut_off_timer;
    TickType_t event_start_tick;
    uint8_t control_flags;
    //todo: add some error system
} drainage_vent_dataset_t;

void drainage_vent_init(drainage_vent_dataset_t *vent_sys);
void drainage_vent_cls(drainage_vent_dataset_t *vent_sys);
void drainage_vent_opn(drainage_vent_dataset_t *vent_sys);
void drainage_vent_ack(drainage_vent_dataset_t *vent_sys);
