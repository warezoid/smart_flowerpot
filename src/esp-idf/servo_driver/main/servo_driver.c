/*
    - https://navody.dratek.cz/arduino-projekty/servo-motor.html
    - https://www.amazon.com/AYWHP-Helicopter-Drones-Robotics-Control/dp/B0DRHXGY4X
    - https://medium.com/@melek_cherif/pwm-motor-control-using-esp32-esp-idf-6c0e9bec4604
    - https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/ledc.html
    - https://github.com/Melek-Cherif/motor_control_esp32

    servo frequency: 50 Hz -> 1 / 0.02
    servo positions: 0 (0.5ms) -> min | 90 (1.5ms) -> stred | 180 (2.5ms) -> max
        - send angle between 0 - 180 deg -> calculate pulse widht -> calculate duty cycle
    duty resolution: basicly it is offset value | more samples -> finer signal
    duty: on time in percentage (0.75 -> 75 %) coded in offset binary -> duty value between 2.5 % and 12.5 %

    esp32 and servo must be in the same VOLTAGE RAILS!
*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "servo_motor_180.h"

void app_main(void)
{
    Servo vent_servo = {
        .PIN = GPIO_NUM_25,
        .TIMER = LEDC_TIMER_0,
        .CHANNEL = LEDC_CHANNEL_0
    };
    servo_setup(vent_servo);

    while(1){       
        servo_write(vent_servo.CHANNEL, 0);
        vTaskDelay(pdMS_TO_TICKS(500));

        servo_write(vent_servo.CHANNEL, 180);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}