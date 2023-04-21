#ifndef __ads8344__
#define __ads8344__

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

// Selects Internal Clock Mode
// Single-Ended Channel Selection
//  Define the ADC channels
#define CH0 0b10000111
#define CH1 0b11000111
#define CH2 0b10010111
#define CH3 0b11010111
#define CH4 0b10100111
#define CH5 0b11100111
#define CH6 0b10110111
#define CH7 0b11110111

// Define a function to read data from a channel
uint16_t ads_read(spi_inst_t *spi, uint8_t channel);
void ads_read_data_continues(spi_inst_t *spi, uint8_t *channels, uint16_t *data, uint32_t len);

#endif