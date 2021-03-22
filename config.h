#ifndef CONFIG_H
#define CONFIG_H
#include <stdint.h>

# define DEG2RAD 0.0174532923716

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

const uint8_t __NUMBER_OF_LEGS__ = 3;
const float __OMNI_DIAMETER_MM__ = 100.0;

const uint8_t __LEGA_PWM_PIN__ = 27;
const uint8_t __LEGA_DIR_PIN__ = 26;
const float   __LEGA_ANGLE_RAD__ = 90.0 * DEG2RAD;

const uint8_t __LEGB_PWM_PIN__ = 21;
const uint8_t __LEGB_DIR_PIN__ = 20;
const uint8_t __LEGB_CHA_PIN__ = 15;
const uint8_t __LEGB_CHB_PIN__ = 14;
const float   __LEGB_ANGLE_RAD__ = -30.0 * DEG2RAD;

const uint8_t __LEGC_PWM_PIN__ = 16;
const uint8_t __LEGC_DIR_PIN__ = 17;
const float   __LEGC_ANGLE_RAD__ = 210.0 * DEG2RAD;

const uint8_t PIN_UNUSED = 2; // generic unconnected pin to pass as placeholder for future use

#endif