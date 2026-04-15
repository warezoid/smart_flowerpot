idf_component_register(
    SRCS "roulette.c"
    INCLUDE_DIRS "include"
    REQUIRES esp_driver_gpio esp_timer
)
