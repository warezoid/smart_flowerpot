#ifndef VENT_DRIVER_H
#define VENT_DRIVER_H

#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "pwm_generator.h"

#define SERVO_DUTY_CLOSE 204
#define SERVO_DUTY_OPEN 1024

#define VENT_MOVE_DELAY_MS 5000

#define OUT_PWM_CHANNEL LEDC_CHANNEL_0

#define OUT_VSPM1_PIN GPIO_NUM_26
#define OUT_VSPM2_PIN GPIO_NUM_27

#define IN_ESO1_PIN GPIO_NUM_34
#define IN_ESO2_PIN GPIO_NUM_35
#define IN_ESC1_PIN GPIO_NUM_36
#define IN_ESC2_PIN GPIO_NUM_37

typedef struct{
    TickType_t vsrs_tick;
    uint8_t vsp_code;
    uint8_t vsv1_enabled;
    uint8_t vsv2_enabled;
    uint8_t errcode_1;
    uint8_t errcode_2;
} vsrp_dataset;

void vent_driver_init();

void vent_cls(vsrp_dataset *vent_sys);
void vent_opn(vsrp_dataset *vent_sys);
void vent_ack(vsrp_dataset *vent_sys);

void calc_duty(uint32_t deg);

#endif