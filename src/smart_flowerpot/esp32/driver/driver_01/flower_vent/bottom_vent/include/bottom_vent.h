#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define OUT_BOTTOM_VENT_EN1 GPIO_NUM_25
#define OUT_BOTTOM_VENT_DIR1 GPIO_NUM_26
#define OUT_BOTTOM_VENT_DIR2 GPIO_NUM_27

#define OUT_BOTTOM_VENT_MPR1 GPIO_NUM_32
#define IN_BOTTOM_VENT_ESO1 GPIO_NUM_35
#define IN_BOTTOM_VENT_ESC1 GPIO_NUM_34

#define OUT_BOTTOM_VENT_MPR2 GPIO_NUM_33
#define IN_BOTTOM_VENT_ESO2 GPIO_NUM_39
#define IN_BOTTOM_VENT_ESC2 GPIO_NUM_36

typedef struct{
    TickType_t action_start_tick;
    
    uint32_t v1_opn_ms;
    uint32_t v1_cls_ms;
    uint32_t v2_opn_ms;
    uint32_t v2_cls_ms;

    uint16_t err_word;
    uint8_t io_byte;
    uint8_t ctrl_byte;
} bottom_vent_dataset_t;

void bottom_vent_init();
bottom_vent_dataset_t bottom_vent_init_dataset();
void bottom_vent_print(const bottom_vent_dataset_t *vent_sys);
void bottom_vent_fsm(bottom_vent_dataset_t *vent_sys);
