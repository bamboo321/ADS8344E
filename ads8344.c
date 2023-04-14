#include "ads8344.h"

// Define a function to read data from a channel
uint16_t ads_read(spi_inst_t *spi, uint8_t channel)
{
    // Select the channel by sending a command byte
    spi_write_blocking(spi, &channel, 1);

    // Wait for the conversion to finish (about 8 us)
    sleep_us(8);

    // Read two bytes of data from the ADC
    uint8_t data[3];
    spi_read_blocking(spi, 0, data, 3);

    // Combine the two bytes into a 16-bit value
    uint16_t value = ((data[0] << 16) | (data[1] << 8) | data[2]) >> 7;

    // Return the value
    return value;
}