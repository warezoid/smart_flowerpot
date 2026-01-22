#include "vent_driver.h"
#include "pwm_generator.h"

void call_pwm_init(const ledc_channel_t ch){
    pwm_init_t pwm_config = {
        .timer = LEDC_TIMER_0,
        .frequency_hz = 50,
        .channel = ch,
        .out_pwm_pin = GPIO_NUM_13
    };
    pwm_init(&pwm_config);
}



/*
    BELLOW IS ONLY TESTING CODE
    VALUES OF DUTY OPEN AND DUTY CLOSED WILL BE HARDCODED IN HEADER FILE AS MACRO
*/
#include <stdio.h>
#include <stdint.h>
static void calc_duty(uint32_t deg){
    const uint32_t SERVO_MIN_PW_US = 500;
    const uint32_t SERVO_MAX_PW_US = 2500;
    const uint32_t SERVO_MAX_DEG = 180;
    const uint32_t PERIOD_US = 20000;

    unsigned int pw = SERVO_MIN_PW_US + (SERVO_MAX_PW_US - SERVO_MIN_PW_US) * deg / SERVO_MAX_DEG;
    uint32_t duty = (pw * MAX_DUTY) / PERIOD_US;

    printf("ESP LOG: Duty value for angle %ld = %ld.", deg, duty);
}