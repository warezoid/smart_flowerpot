#ifndef SERVO_MOTOR_180_H
#define SERVO_MOTOR_180_H

#include "driver/ledc.h"

#define SPEED_MODE LEDC_LOW_SPEED_MODE
#define CLK_CONFIG LEDC_AUTO_CLK
#define INTR_TYPE LEDC_INTR_DISABLE
#define DUTY_RESOLUTION LEDC_TIMER_13_BIT

#define FREQUENCY 50
#define PERIOD_US 20000     //1 / FREQUENCY * 1000000
#define MAX_DUTY 8192       //2**DUTY_RESOLUTION

#define SERVO_MIN_PW_US 1000
#define SERVO_MAX_PW_US 2000
#define SERVO_MAX_DEG 180

typedef struct{
    const uint8_t PIN;
    const ledc_timer_t TIMER;
    const ledc_channel_t CHANNEL;
} Servo;

void servo_setup(Servo servo);
void servo_write(const ledc_channel_t CHANNEL_NUM, unsigned int angle);

#endif