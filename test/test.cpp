#include "stdio.h"
#include "pico/stdlib.h"
#include "MCP23017.hpp"

#define LED_PIN 25

int main()
{
    stdio_init_all();
    i2c_init(i2c0, 100000);
    i2c_init(i2c1, 100000);

    sleep_ms(4000);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_put(LED_PIN, 0);
    gpio_put(LED_PIN, 1);
    
    gpio_set_function(0, GPIO_FUNC_I2C); // Data
    gpio_set_function(1, GPIO_FUNC_I2C); // Clk

    gpio_pull_up(0);
    gpio_pull_up(1);

    MCP23017 port(i2c0, 0x20);

    port.set_port_mode(PORT_16_BIT);
    port.set_ioconfig(0b00111000);

    port.set_iodir_a(0x00);
    port.set_iodir_b(0x00);

    port.write_configuration();

    port.test_output();

    return 0;
}