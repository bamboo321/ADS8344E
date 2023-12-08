#include "ads8344.h"

// Define a function to read data from a channel
uint16_t ads_read(spi_inst_t *spi, uint8_t channel, uint gpio_cs)
{
    // Set the CS pin to low to start the SPI communication
    gpio_put(gpio_cs, 0);

    // Select the channel by sending a command byte
    spi_write_blocking(spi, &channel, 1);

    // Wait for the conversion to finish (about 8 us)
    sleep_us(8);

    // Read two bytes of data from the ADC
    uint8_t data[3];
    spi_read_blocking(spi, 0, data, 3);

    // Combine the two bytes into a 16-bit value
    uint16_t value = ((data[0] << 16) | (data[1] << 8) | data[2]) >> 7;

    // Set the CS pin to high to end the SPI communication
    gpio_put(gpio_cs, 1);

    // Return the value
    return value;
}

void ads_read_data_continues(spi_inst_t *spi, uint8_t *channels, uint16_t *data, uint32_t len)
{
    uint32_t data_index = 0;
    uint8_t ch_index = 0;
    // uint8_t ch = channels[ch_index++];
    spi_write_blocking(spi, &channels[ch_index++], 1);
    while (len > data_index)
    {
        uint8_t d[3];
        spi_write_read_blocking(spi, &channels[ch_index], d, 3);
        data[data_index++] = ((d[0] << 16) | (d[1] << 8) | d[2]) >> 7;
        ch_index += 3;
        if (ch_index >= 24)
            ch_index = 1;
    }
}

void ads_doual_read_data_continues(spi_inst_t *spi_first, spi_inst_t *spi_second, uint8_t *channels, uint16_t *data, uint32_t len)
{
    uint32_t data_index = 0;
    uint8_t ch_index = 0;
    // uint8_t ch = channels[ch_index++];
    spi_write_blocking(spi_first, &channels[ch_index++], 1);
    spi_write_blocking(spi_second, &channels[ch_index++], 1);
    while (len > data_index)
    {
        uint8_t d1[3];
        uint8_t d2[3];
        spi_write_read_blocking(spi_first, &channels[ch_index], d1, 3);
        spi_write_read_blocking(spi_second, &channels[ch_index], d2, 3);
        data[data_index++] = ((d1[0] << 16) | (d1[1] << 8) | d1[2]) >> 7;
        data[data_index++] = ((d2[0] << 16) | (d2[1] << 8) | d2[2]) >> 7;
        ch_index += 3;
        if (ch_index >= 24)
            ch_index = 1;
    }
}
