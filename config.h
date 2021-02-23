#ifndef CONFIG_H
#define CONFIG_H
#include <stdint.h>

/*
*   Most of this could/should probably be JSON
*/

// the number of legs/wheels on the chair
const uint8_t __NUMBER_OF_LEGS__ = 3;
// diameter of each omniwheel in mms
const float __OMNI_DIAMETER_MM__ = 100.0;

// pin declarations for a leg
const uint8_t __LEGA_PWM_PIN__ = 17;
const uint8_t __LEGA_DIR_PIN__ = 16;
const float   __LEGA_ANGLE_RAD__ = 0.0;

// generic unconnected pin to pass as placeholder for future use
const uint8_t PIN_UNUSED = 2; 

/*
    UART configuration
*/
#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

#define UART_TX_PIN 0
#define UART_RX_PIN 1

#endif