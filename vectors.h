#ifndef VECTORS_H
#define VECTORS_H

#include <algorithm>
#include <complex>
#include <array>
#include "motor_PWM.h"

class Carriage
{
    public:
        Carriage(const std::array<motor_PWM, __NUMBER_OF_LEGS__> &_leg_array);

    private:
        std::array<motor_PWM, __NUMBER_OF_LEGS__> leg_array;

};

Carriage::Carriage(const std::array<motor_PWM, __NUMBER_OF_LEGS__> &_leg_array)
{
    leg_array = _leg_array;
}

#endif