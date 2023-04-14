add_library(ADS8344E INTERFACE)

target_include_directories(ADS8344E
  INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(ADS8344E
  INTERFACE
  pico_stdlib 
  hardware_spi
)

target_sources(ADS8344E
  INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/ads8344.c
  ${CMAKE_CURRENT_LIST_DIR}/ads8344.h
)