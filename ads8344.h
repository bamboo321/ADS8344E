// Include the pico libraries
#include "pico/stdlib.h"
#include "hardware/spi.h"

// Define the SPI pins
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19

// Define the ADC channels
#define CH0 0b10000000
#define CH1 0b10010000
#define CH2 0b10100000
#define CH3 0b10110000
#define CH4 0b11000000
#define CH5 0b11010000
#define CH6 0b11100000
#define CH7 0b11110000

// Define a function to read data from a channel
uint16_t read_adc(uint8_t channel) {
    // Select the channel by sending a command byte
    spi_write_blocking(SPI_PORT, &channel, 1);

    // Wait for the conversion to finish (about 8 us)
    sleep_us(8);

    // Read two bytes of data from the ADC
    uint8_t data[2];
    spi_read_blocking(SPI_PORT, 0, data, 2);

    // Combine the two bytes into a 12-bit value
    uint16_t value = (data[0] << 8) | data[1];
    value >>= 4;

    // Return the value
    return value;
}

int main() {
    // Initialize the SPI module with a clock speed of 1 MHz
    spi_init(SPI_PORT, 1000000);

    // Set up the SPI pins
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);

    // Set the chip select pin as output and high
    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);

    while (true) {
        // Read data from channel 0 and print it to the serial monitor
        uint16_t value = read_adc(CH0);
        printf("Channel 0: %d\n", value);

        // Wait for a second
        sleep_ms(1000);
    }
}
