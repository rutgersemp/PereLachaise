#ifndef OMNI_H
#define OMNI_H

#include "motor_PWM.h"
#include <stdint.h>
#include <algorithm>

/*
*   Class extends a motor driver class to include 'chair specific' aspects like wheel diameter and mounting angle
*/

class Omni : public motor_PWM {
    public:
        // constructor without quadrature input
        Omni(uint _PWMPIN, uint _DIRPIN, float _ANGLE, float _DIAMETER);

        // constructor with quadrature input
        Omni(uint _PWMPIN, uint _DIRPIN, uint _PHASE_A, uint _PHASE_B, float _ANGLE, float _DIAMETER);

    private:
        float ANGLE, DIAMETER;
};

Omni::Omni(uint _PWMPIN, uint _DIRPIN, float _ANGLE, float _DIAMETER) : motor_PWM(_PWMPIN, _DIRPIN)
{
    ANGLE = _ANGLE;
    DIAMETER = _DIAMETER;
}

Omni::Omni(uint _PWMPIN, uint _DIRPIN, uint _PHASE_A, uint _PHASE_B, float _ANGLE, float _DIAMETER) : motor_PWM(_PWMPIN, _DIRPIN, _PHASE_A, _PHASE_B)
{
    ANGLE = _ANGLE;
    DIAMETER = _DIAMETER;
}

#endif