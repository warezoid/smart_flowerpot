#ifndef PWM_GENERATOR_H
#define PWM_GENERATOR_H

#include <stdint.h>
#include "driver/ledc.h"

#define SPEED_MODE LEDC_LOW_SPEED_MODE
#define DUTY_RESOLUTION LEDC_TIMER_13_BIT
#define MAX_DUTY 8192
#define CLK_CONFIG LEDC_AUTO_CLK
#define INTR_TYPE LEDC_INTR_DISABLE

typedef struct{
    const ledc_timer_t timer;
    const uint32_t frequency_hz;
    const ledc_channel_t channel;
    const uint8_t out_pwm_pin;
} pwm_init_t;

void pwm_init(pwm_init_t *pwm_cfg);
void pwm_set_duty(const ledc_channel_t CHANNEL_NUM, uint16_t duty);

#endif