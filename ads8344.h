#ifndef __ads8344__
#define __ads8344__

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

//Selects Internal Clock Mode
//Single-Ended Channel Selection
// Define the ADC channels
#define CH0 0b10000110
#define CH1 0b11000110
#define CH2 0b10010110
#define CH3 0b11010110
#define CH4 0b10100110
#define CH5 0b11100110
#define CH6 0b10110110
#define CH7 0b11110110

// Define a function to read data from a channel
uint16_t ads_read(spi_inst_t *spi,uint8_t channel);

#endif