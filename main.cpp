// standard libraries
// #include <stdio.h>
#include <stdint.h>

// pico libraries
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

// local libraries
#include "motor_PWM.h"
#include "omni.h"
// #include "vectors.h"

// config files
#include "config.h"

volatile int8_t command[__NUMBER_OF_LEGS__]; // format is '!' int8_t int8_t int8_t ... '.', with first and last removed padding during receive
volatile bool commandAvailable = false;

void on_uart_rx() {
    static uint8_t count = 0;
    while (uart_is_readable(UART_ID)) {
        uint8_t ch = uart_getc(UART_ID);

        if (ch == '!') count = 1;
        else if (ch == '.' && count == 4)
        {
            count = 0;
            commandAvailable = true;
        }
        else if (count > 0 && count < 4) {
            command[count-1] = ch;
            count++;
        }
        else
        {
            // count = 0; continue keeping track of count for debugging
            commandAvailable = false;
            // TODO: raise an exception of sorts
        }

    }
}

void init_uart()
{
    // setup UART, low baud initially for convenience
    uart_init(UART_ID, 2400);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // configure remaining settings
    int actual = uart_set_baudrate(UART_ID, BAUD_RATE);
    uart_set_hw_flow(UART_ID, false, false);
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

    // Disable FIFO
    uart_set_fifo_enabled(UART_ID, false);

    // Set up a RX interrupt handler
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;
    irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
    irq_set_enabled(UART_IRQ, true);
    uart_set_irq_enables(UART_ID, true, false);
}


int main() {
    // // connection to on-boad LED for debugging purposes
    // motor_PWM led(25, PIN_UNUSED); 
    // led.init(20000);

    Omni legA(__LEGA_PWM_PIN__, __LEGA_DIR_PIN__, __LEGA_ANGLE_RAD__, __OMNI_DIAMETER_MM__);
    legA.init(20000);

    init_uart();

    while (1)
    {
        if (commandAvailable)
        {
            legA.drive_127(command[1]);

            commandAvailable = false; // clear flag after use
        }

        tight_loop_contents();
    }
}