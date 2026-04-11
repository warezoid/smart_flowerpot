# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/esp/esp-idf/components/bootloader/subproject"
  "/media/warezoid/Storage drive1/warezoid/work/projects/smart_flowerpot/code/src/esp-idf/smart_flowerpot/esp32/drivers/motion/build/bootloader"
  "/media/warezoid/Storage drive1/warezoid/work/projects/smart_flowerpot/code/src/esp-idf/smart_flowerpot/esp32/drivers/motion/build/bootloader-prefix"
  "/media/warezoid/Storage drive1/warezoid/work/projects/smart_flowerpot/code/src/esp-idf/smart_flowerpot/esp32/drivers/motion/build/bootloader-prefix/tmp"
  "/media/warezoid/Storage drive1/warezoid/work/projects/smart_flowerpot/code/src/esp-idf/smart_flowerpot/esp32/drivers/motion/build/bootloader-prefix/src/bootloader-stamp"
  "/media/warezoid/Storage drive1/warezoid/work/projects/smart_flowerpot/code/src/esp-idf/smart_flowerpot/esp32/drivers/motion/build/bootloader-prefix/src"
  "/media/warezoid/Storage drive1/warezoid/work/projects/smart_flowerpot/code/src/esp-idf/smart_flowerpot/esp32/drivers/motion/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/media/warezoid/Storage drive1/warezoid/work/projects/smart_flowerpot/code/src/esp-idf/smart_flowerpot/esp32/drivers/motion/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/media/warezoid/Storage drive1/warezoid/work/projects/smart_flowerpot/code/src/esp-idf/smart_flowerpot/esp32/drivers/motion/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
