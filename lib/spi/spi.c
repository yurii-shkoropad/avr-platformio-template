#include <avr/io.h>
#include "spi.h"

#define SPI_SS   PB2
#define SPI_MOSI PB3
#define SPI_MISO PB4
#define SPI_SCK  PB5

void SPI_init(void) {
    DDRB |= (1 << SPI_SS) |
            (1 << SPI_MOSI) |
            (1 << SPI_SCK);

    DDRB &= ~(1 << SPI_MISO);

    SPI_deselect();

    SPCR = (1 << SPE) |
           (1 << MSTR) |
           (1 << SPR0);

    SPSR &= ~(1 << SPI2X);
}

void SPI_select(void) {
    PORTB &= ~(1 << SPI_SS);
}

void SPI_deselect(void) {
    PORTB |= (1 << SPI_SS);
}

uint8_t SPI_transfer(uint8_t data) {
    SPDR = data;

    while (!(SPSR & (1 << SPIF)));

    return SPDR;
}

void SPI_write(uint8_t data) {
    (void)SPI_transfer(data);
}

uint8_t SPI_read(void) {
    return SPI_transfer(0xFF);
}