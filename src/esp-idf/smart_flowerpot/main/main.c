#include <stdio.h>
#include "vent_driver.h"

#define VENT_CHANNEL LEDC_CHANNEL_0

void app_main(void){
    call_pwm_init(VENT_CHANNEL);
}