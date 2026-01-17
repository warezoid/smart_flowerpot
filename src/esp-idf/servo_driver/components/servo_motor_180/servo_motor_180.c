#include "servo_motor_180.h"

void servo_setup(Servo servo){
    ledc_timer_config_t t = {
        .speed_mode = SPEED_MODE,
        .timer_num = servo.TIMER,
        .duty_resolution = DUTY_RESOLUTION,
        .freq_hz = FREQUENCY,
        .clk_cfg = CLK_CONFIG
    };
    ledc_timer_config(&t);

    ledc_channel_config_t c = {
        .speed_mode = SPEED_MODE,
        .channel = servo.CHANNEL,
        .timer_sel = servo.TIMER,
        .intr_type = INTR_TYPE,
        .gpio_num = servo.PIN,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&c);
}

void servo_write(const ledc_channel_t CHANNEL_NUM, unsigned int angle){
    if(angle > SERVO_MAX_DEG){
        angle = SERVO_MAX_DEG;
    }

    unsigned int pw = SERVO_MIN_PW_US + (SERVO_MAX_PW_US - SERVO_MIN_PW_US) * angle / SERVO_MAX_DEG;
    uint32_t duty = (pw * MAX_DUTY) / PERIOD_US;

    ledc_set_duty(SPEED_MODE, CHANNEL_NUM, duty);
    ledc_update_duty(SPEED_MODE, CHANNEL_NUM);
}