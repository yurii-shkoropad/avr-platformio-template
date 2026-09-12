#include <avr/io.h>
#include <uart.h>
 
int main(void)
{
    uart_init(9600);
    uart_println("Program started");

    uart_print_bin(1 << 0);
}
