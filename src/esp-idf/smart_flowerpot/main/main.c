#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "vent_driver.h"

void app_main(void){
    call_pwm_init(LEDC_CHANNEL_0);
    
    while(1){
        calc_duty(0);   //204
        vTaskDelay(pdMS_TO_TICKS(5000));

        calc_duty(180); //1024
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}