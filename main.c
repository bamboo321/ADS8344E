#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "ads8344.h"

#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS 17
#define PIN_SCK 18
#define PIN_MOSI 19

int main()
{
    stdio_init_all();
    spi_init(SPI_PORT, 1000 * 1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);

    // Initialize the CS pin
    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);

    while (1)
    {
        uint16_t value = ads_read(SPI_PORT, 0, PIN_CS);
        printf("Read value: %d\n", value);
        sleep_ms(1000);
    }
}