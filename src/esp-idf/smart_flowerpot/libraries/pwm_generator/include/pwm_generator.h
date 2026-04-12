#pragma once

#include <stdint.h>
#include "driver/ledc.h"

#define SPEED_MODE LEDC_LOW_SPEED_MODE
#define DUTY_RESOLUTION LEDC_TIMER_13_BIT
#define MAX_DUTY 8192
#define CLK_CONFIG LEDC_AUTO_CLK
#define INTR_TYPE LEDC_INTR_DISABLE

typedef struct{
    const ledc_timer_t timer;
    const ledc_channel_t channel;
    const uint32_t freq_hz;
    const int out_pin;
} pwm_generator_config_t;

void pwm_generator_init(pwm_generator_config_t *pwm_cfg);
void pwm_generator_set_duty(const ledc_channel_t CHANNEL_NUM, uint32_t duty);
