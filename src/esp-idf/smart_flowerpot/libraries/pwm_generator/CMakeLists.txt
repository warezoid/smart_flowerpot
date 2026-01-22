set(
    srcs 
    "pwm_generator.c"
)

idf_component_register(
    SRCS ${srcs}
    INCLUDE_DIRS "include"
    REQUIRES esp_driver_ledc
)