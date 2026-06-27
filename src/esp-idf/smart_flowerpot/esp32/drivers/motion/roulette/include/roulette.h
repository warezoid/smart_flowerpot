#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "driver/gpio.h"

/*
    MEASURMENT:     1       2       3
    CLOSING TIME:   55s     55s     55s     -> 58s = 58000 ms
    OPENING TIME    67s     67s     67s     -> 70s = 70000 ms
*/
#define ROULETTE_MOVE_CLOSE_DELAY_MS 5000//58000
#define ROULETTE_MOVE_OPEN_DELAY_MS 8000//70000

#define OUT_ROULETTE_DIR1 GPIO_NUM_18
#define OUT_ROULETTE_DIR2 GPIO_NUM_19
#define OUT_ROULETTE_EN1 GPIO_NUM_16

#define IN_ROULETTE_ESO1 GPIO_NUM_22
#define IN_ROULETTE_ESC1 GPIO_NUM_23

typedef struct{
    esp_timer_handle_t power_cut_off_timer;
    TickType_t event_start_tick;
    uint8_t control_flags;
    //todo: add some error system
} roulette_dataset_t;

void roulette_init(roulette_dataset_t *roulette_sys);
void roulette_cls(roulette_dataset_t *roulette_sys);
void roulette_opn(roulette_dataset_t *roulette_sys);
void roulette_ack(roulette_dataset_t *roulette_sys);
