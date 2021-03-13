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
#include "vectors.h"

// config files
#include "config.h"

/*
    UART code
*/
#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

#define UART_TX_PIN 0
#define UART_RX_PIN 1

volatile int8_t command[__NUMBER_OF_LEGS__]; // format is '!' int8_t int8_t int8_t ... '.', with first and last removed padding during receive
volatile bool commandAvailable = false;

void on_uart_rx() {
    static uint8_t count = 0;
    while (uart_is_readable(UART_ID)) {
        int8_t XYRbyte = uart_getc(UART_ID);

        // start of message received, set counter to start regardless of what else we were doing
        if ((char)XYRbyte == '!') count = 1;

        // end of message received at expected count, assuming valid command
        // reset counter and set message flag
        else if ((char)XYRbyte == '.' && count == 4)
        {
            count = 0;
            commandAvailable = true;
        }

        // count in middle of message, store bytes as received
        else if (count > 0 && count < 4) {
            command[count-1] = XYRbyte;
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
    uart_init(UART_ID, 2400);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    int actual = uart_set_baudrate(UART_ID, BAUD_RATE);
    uart_set_hw_flow(UART_ID, false, false);

    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

    // Turn off FIFO's - we want to do this character by character
    uart_set_fifo_enabled(UART_ID, false);

    // Set up a RX interrupt
    // We need to set up the handler first
    // Select correct interrupt for the UART we are using
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

    irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
    irq_set_enabled(UART_IRQ, true);

    uart_set_irq_enables(UART_ID, true, false);
}


int main() {
    motor_PWM led(25, PIN_UNUSED); // connection to on-boad LED for debugging use
    led.init(20000);

    Omni legA(__LEGA_PWM_PIN__, __LEGA_DIR_PIN__, __LEGA_ANGLE_RAD__, __OMNI_DIAMETER_MM__);
    legA.init(20000);

    Omni legB(__LEGB_PWM_PIN__, __LEGB_DIR_PIN__, __LEGB_ANGLE_RAD__, __OMNI_DIAMETER_MM__);
    legB.init(20000);

    Omni legC(__LEGC_PWM_PIN__, __LEGC_DIR_PIN__, __LEGC_ANGLE_RAD__, __OMNI_DIAMETER_MM__);
    legC.init(20000);

    std::array<Omni, __NUMBER_OF_LEGS__> wheels = {
        legA,
        legB,
        legC
    };
    Carriage chair(wheels);

    init_uart();

    while (1)
    {
        if (commandAvailable)
        {

            float command_norm[3] = {
                command[0]/127.0,
                command[1]/127.0,
                command[2]/127.0
                };

            // legA.drive_norm(command_norm[0]);
            // legB.drive_norm(command_norm[1]);
            // legC.drive_norm(command_norm[2]);

            std::complex<double> translate(command_norm[0], command_norm[1]);
            movementVector general;
            general.translation = translate;
            general.rotation = command_norm[2];
            chair.distribute(general);

            commandAvailable = false; // clear flag after use
        }

        tight_loop_contents();
    }
}