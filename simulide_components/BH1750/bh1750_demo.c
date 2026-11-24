#include <avr/io.h>
#include <util/delay.h>
#include <i2c.h>
#include <uart.h>

#define BH1750_ADDRESS 0x23


int main(void) {
    uart_init(9600);
    i2cInit();

    i2cStart();
    i2cWrite(BH1750_ADDRESS << 1);
    i2cWrite(0x10);
    i2cStop();
    _delay_ms(180);

    uart_println("Demo");

    while (1) {
        i2cStart();
        i2cWrite((BH1750_ADDRESS << 1) | 1);
        uint8_t high = i2cRead(1);
        uint8_t low = i2cRead(0);
        i2cStop();

        uint16_t raw = ((uint16_t)high << 8) | low;
        uint16_t lux = (uint32_t)raw * 10 / 12;

        uart_print_uint(lux);
        uart_println("lux");

        _delay_ms(1000);
    }
}
