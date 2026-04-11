#ifndef VENT_DRIVER_H
#define VENT_DRIVER_H

#include <stdint.h>

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
    esp_timer_handle_t vscp_timer;
    TickType_t vsrs_tick;
    uint8_t vsp_code;
    uint8_t vsv1_enabled;
    uint8_t vsv2_enabled;
    uint8_t errcode_1;
    uint8_t errcode_2;
} vsrp_dataset;

void vent_driver_init(vsrp_dataset *vent_sys);

void vent_cls(vsrp_dataset *vent_sys);
void vent_opn(vsrp_dataset *vent_sys);
void vent_ack(vsrp_dataset *vent_sys);

#endif