#ifndef VECTORS_H
#define VECTORS_H

#include <algorithm>
#include <complex>
#include <array>
#include "config.h"
#include "omni.h"

class Carriage
{
    public:
        Carriage(const std::array<Omni, __NUMBER_OF_LEGS__> & _leg_array);

    private:
        std::array<Omni, __NUMBER_OF_LEGS__> leg_array;

};

Carriage::Carriage(const std::array<Omni, __NUMBER_OF_LEGS__> & _leg_array)
{
    leg_array = _leg_array;
}

#endif