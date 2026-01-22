set(
    srcs 
    "vent_driver.c"
)

idf_component_register(
    SRCS ${srcs}
    INCLUDE_DIRS "include"
    REQUIRES pwm_generator
)