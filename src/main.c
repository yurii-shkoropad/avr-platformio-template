#include <avr/io.h>
#include <util/delay.h>
#include <spi.h>

#define LATCH_PIN_DISPLAY  PB2
#define LATCH_PIN_BUTTONS  PB1

const uint8_t digit_map[10] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

void display_digit(uint8_t digit);
uint8_t read_shift_register();

int main() {
  DDRB |= (1 << LATCH_PIN_DISPLAY) | (1 << LATCH_PIN_BUTTONS);
  spi_init();
  while (1) {
    uint8_t input = read_shift_register();

    if (bit_is_clear(input, 0)) {
      display_digit(1);
    } else if (bit_is_clear(input, 1)) {
      display_digit(2);
    } else if (bit_is_clear(input, 2)) {
      display_digit(3);
    } else {
      display_digit(0);
    }

    _delay_ms(50);
  }
}

void display_digit(uint8_t digit) {
  PORTB &= ~(1 << LATCH_PIN_DISPLAY);
  spi_transfer(digit_map[digit]);
  PORTB |= (1 << LATCH_PIN_DISPLAY);
}

uint8_t read_shift_register() {
  uint8_t data;

  PORTB &= ~(1 << LATCH_PIN_BUTTONS);
  _delay_us(1); 
  PORTB |= (1 << LATCH_PIN_BUTTONS);

  data = spi_read();

  return data;
}