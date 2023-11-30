cmake_minimum_required(VERSION 3.22)
include(pico_sdk_import.cmake)
project(ADS8344E C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()


add_executable(ADS8344E_test
    main.c
    ads8344.c
)


target_link_libraries(ADS8344E_test
  pico_stdlib
  hardware_spi
)

pico_add_extra_outputs(ADS8344E_test)
# target_sources(ADS8344E_test
#   ${CMAKE_CURRENT_LIST_DIR}/ads8344.c
#   ${CMAKE_CURRENT_LIST_DIR}/ads8344.h
# )