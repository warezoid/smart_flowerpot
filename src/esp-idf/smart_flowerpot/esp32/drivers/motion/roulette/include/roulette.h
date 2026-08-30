#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define OUT_ROULETTE_DIR1 GPIO_NUM_18
#define OUT_ROULETTE_DIR2 GPIO_NUM_19
#define OUT_ROULETTE_EN1 GPIO_NUM_16

#define IN_ROULETTE_TOP1 GPIO_NUM_22
#define IN_ROULETTE_TOP2 GPIO_NUM_23
#define IN_ROULETTE_BOT1 GPIO_NUM_17
#define IN_ROULETTE_BOT2 GPIO_NUM_21

typedef struct{
    TickType_t action_start_tick;

    uint32_t r1_opn_ms;
    uint32_t r1_cls_ms;

    uint16_t err_word;
    uint8_t io_byte;
    uint8_t ctrl_byte;
} roulette_dataset_t;

void roulette_init();
roulette_dataset_t roulette_init_dataset();
void roulette_print(const roulette_dataset_t *roulette_sys);
void roulette_fsm(roulette_dataset_t *roulette_sys);
