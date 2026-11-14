idf_component_register(
    SRCS "bottom_vent.c"
    INCLUDE_DIRS "include"
    REQUIRES esp_driver_gpio esp_timer
)
