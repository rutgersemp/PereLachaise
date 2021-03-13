#ifndef VECTORS_H
#define VECTORS_H

#include <algorithm>
// #include <complex>
#include <ctgmath> // includes math and complex behind the scenes
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

        // takes a movementVector struct as input, consisting of 1 plane of translation and 1 axis of rotation
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
    std::array<float, __NUMBER_OF_LEGS__> omnivectors;
    float max_mag = 0;

    for (uint idx = 0; idx < __NUMBER_OF_LEGS__; idx++) // implemented without auto& : since array size is known and index is required anyway
    {
        omnivectors[idx] = abs(general_vector.translation) * sin( wheels[idx].angle() - arg(general_vector.translation));
        omnivectors[idx] = omnivectors[idx] - general_vector.rotation;
        if (abs(omnivectors[idx]) > max_mag) max_mag = abs(omnivectors[idx]); // keep track of largest value
    }

    // if one of the wheels needs to spin faster than possible, slow everything else down to compensate
    // this step cannot be done until all speeds are known, thus needs to be in a separate loop
    if (max_mag > 1.0) 
    {
        for (uint idx = 0; idx < __NUMBER_OF_LEGS__; idx++)
        {
            omnivectors[idx] = omnivectors[idx] / max_mag;
        }
    }

    // finally, set duty cycles
    for (uint idx = 0; idx < __NUMBER_OF_LEGS__; idx++)
    {
        wheels[idx].set_duty_1000( 1000.0* omnivectors[idx]);
    }
}

#endif