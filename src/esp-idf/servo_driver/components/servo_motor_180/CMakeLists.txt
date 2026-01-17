set(
    srcs 
    "servo_motor_180.c"
)

idf_component_register(
    SRCS ${srcs}
    INCLUDE_DIRS "include"
    REQUIRES driver
)