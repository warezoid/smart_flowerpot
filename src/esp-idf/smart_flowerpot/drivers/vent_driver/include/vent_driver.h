#ifndef VENT_DRIVER_H
#define VENT_DRIVER_H

#include "driver/ledc.h"

#define SERVO_DUTY_OPEN 0
#define SERVO_DUTY_CLOSE 0

void call_pwm_init(const ledc_channel_t ch);

#endif