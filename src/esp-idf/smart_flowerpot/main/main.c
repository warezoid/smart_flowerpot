#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "vent_driver.h"

void app_main(void){
    vent_driver_init();

    while(1){
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}