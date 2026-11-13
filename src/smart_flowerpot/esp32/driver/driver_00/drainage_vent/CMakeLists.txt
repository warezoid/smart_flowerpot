idf_component_register(
    SRCS "drainage_vent.c"
    INCLUDE_DIRS "include"
    REQUIRES esp_driver_gpio esp_timer pwm_generator
)
