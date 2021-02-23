#ifndef VECTORS_H
#define VECTORS_H

#include <algorithm>
// #include <complex>
#include <ctgmath>
#include <array>
#include "config.h"
#include "omni.h"

struct movementVector 
{
    std::complex<double> translation; // a 2-dimensional vector
    double rotation; // a 1-dimensional scalar
};

class Carriage
{
    public:
        Carriage(std::array<Omni, __NUMBER_OF_LEGS__> & _wheels);
        void distribute(movementVector general_vector);

    private:
        std::array<Omni, __NUMBER_OF_LEGS__> wheels;

};

Carriage::Carriage(std::array<Omni, __NUMBER_OF_LEGS__> & _wheels) : wheels{_wheels}
{
    //
}

void Carriage::distribute(movementVector general_vector)
{
    std::array<float, __NUMBER_OF_LEGS__> translationals;
    for (uint idx = 0; idx < __NUMBER_OF_LEGS__; idx++) // implemented without auto& : since array size is known and index is required anyway
    {
        translationals[idx] = abs(general_vector.translation) * sin( wheels[idx].angle() - arg(general_vector.translation));
    }
}

#endif