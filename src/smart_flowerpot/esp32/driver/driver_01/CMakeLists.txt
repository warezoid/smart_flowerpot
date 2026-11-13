cmake_minimum_required( VERSION 3.16 )

set(
    EXTRA_COMPONENT_DIRS
    flower_fan
    "./flower_vent/top_vent"
    "./flower_vent/bottom_vent"
)

include( $ENV{IDF_PATH}/tools/cmake/project.cmake )
project( driver_01 )
