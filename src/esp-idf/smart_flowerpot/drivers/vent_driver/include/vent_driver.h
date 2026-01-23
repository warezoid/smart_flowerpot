#ifndef VENT_DRIVER_H
#define VENT_DRIVER_H

#include <stdint.h>
#include "driver/gpio.h"
#include "pwm_generator.h"

#define SERVO_DUTY_CLOSE 204
#define SERVO_DUTY_OPEN 1024

#define OUT_PWM_CHANNEL LEDC_CHANNEL_0

#define OUT_VSPM1_PIN GPIO_NUM_26
#define OUT_VSPM2_PIN GPIO_NUM_27

#define IN_ESO1_PIN GPIO_NUM_34
#define IN_ESO2_PIN GPIO_NUM_35
#define IN_ESC1_PIN GPIO_NUM_36
#define IN_ESC2_PIN GPIO_NUM_37

void vent_driver_init();
void calc_duty(uint32_t deg);

#endif