#ifndef VENT_DRIVER_H
#define VENT_DRIVER_H

#include "driver/gpio.h"
#include "servo_motor_180.h"

typedef struct{
    uint8_t in_block_state;
    uint8_t error_code;
    uint32_t open_switch_state;
    uint32_t close_switch_state;
    gpio_num_t open_switch_pin;
    gpio_num_t close_switch_pin;
    gpio_num_t output_pin;
} Vent;

typedef struct{
    Vent *vents;
    Servo pwm_rail;
} VentSystem;

#endif