cmake_minimum_required( VERSION 3.16 )

set(
    EXTRA_COMPONENT_DIRS
    "../../../library/pwm_generator"
    drainage_vent
    roulette
)

include( $ENV{IDF_PATH}/tools/cmake/project.cmake )
project( driver_00 )
