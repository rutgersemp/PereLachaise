#ifndef CONFIG_H
#define CONFIG_H
#include <stdint.h>

const uint8_t __NUMBER_OF_LEGS__ = 3;
const float __OMNI_DIAMETER_MM__ = 100.0;

const uint8_t __LEGA_PWM_PIN__ = 17;
const uint8_t __LEGA_DIR_PIN__ = 16;
const float   __LEGA_ANGLE_RAD__ = 0.0;

const uint8_t PIN_UNUSED = 2; // generic unconnected pin to pass as placeholder for future use

#endif