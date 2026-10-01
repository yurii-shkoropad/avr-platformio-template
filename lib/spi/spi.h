#ifndef SPI_H
#define SPI_H

#include <stdint.h>

void SPI_init(void);
uint8_t SPI_transfer(uint8_t data);

void SPI_select(void);
void SPI_deselect(void);

void SPI_write(uint8_t data);
uint8_t SPI_read(void);

#endif