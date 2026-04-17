#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "driver/gpio.h"

#define ROULETTE_MOVE_DELAY_MS 9500     //measure time needed for roulette full movement

#define OUT_ROULETTE_DIR1 GPIO_NUM_18
#define OUT_ROULETTE_DIR2 GPIO_NUM_19

#define OUT_ROULETTE_EN1 GPIO_NUM_16
#define IN_ROULETTE_ESO1 GPIO_NUM_22
#define IN_ROULETTE_ESC1 GPIO_NUM_23

#define OUT_ROULETTE_EN2 GPIO_NUM_17
#define IN_ROULETTE_ESO2 GPIO_NUM_25
#define IN_ROULETTE_ESC2 GPIO_NUM_26

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
