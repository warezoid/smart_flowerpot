cmake_minimum_required( VERSION 3.16 )

set(
    EXTRA_COMPONENT_DIRS
    "../../../libraries/pwm_generator"
    drainage_vent
)

include( $ENV{IDF_PATH}/tools/cmake/project.cmake )
project( motion )
