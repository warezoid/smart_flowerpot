#include "pwm_generator.h"

void pwm_init(pwm_init_t *pwm_cfg){
    ledc_timer_config_t t = {
        .speed_mode = SPEED_MODE,
        .timer_num = pwm_cfg->timer,
        .duty_resolution = DUTY_RESOLUTION,
        .freq_hz = pwm_cfg->frequency_hz,
        .clk_cfg = CLK_CONFIG
    };
    ledc_timer_config(&t);

    ledc_channel_config_t c = {
        .speed_mode = SPEED_MODE,
        .channel = pwm_cfg->channel,
        .timer_sel = pwm_cfg->timer,
        .intr_type = INTR_TYPE,
        .gpio_num = pwm_cfg->out_pwm_pin,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&c);
}

void pwm_set_duty(const ledc_channel_t CHANNEL_NUM, uint16_t duty){
    ledc_set_duty(SPEED_MODE, CHANNEL_NUM, duty);
    ledc_update_duty(SPEED_MODE, CHANNEL_NUM);
}