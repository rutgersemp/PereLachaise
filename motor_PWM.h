/*
*   TODO: 
    - Change constructors to use initialization fields so PWMPIN etc. can be const
    - Implement PID
*/

#ifndef MOTOR_PWM_H
#define MOTOR_PWM_H

#include <stdlib.h> // for abs()
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"


class motor_PWM {
    public:
        // init PWM modules with frequency of 20kHz
        void init();

        // set PWM frequency of output
        void set_PWM_freq(unsigned long F);

        // overload combining init() and set_PWM_freq() into single call
        void init(unsigned long FPWM);

        // set duty cycle as signed permillage ([0, 1000])
        void set_duty_1000(uint permille);

        // set duty cycle magnitude of signed byte ([0, 127])
        void set_duty_127(int8_t byte);

        // set duty cycle magnitude of normalized float ([0.0, 1.0])
        void set_duty_norm(float norm);

        // set output direction of driver
        void set_direction(bool clockwise);

        // drive PWM and DIR pins based on signed byte ([-127, 127])
        void drive_127(int8_t drive);

        // drive PWM and DIR pins based on signed byte ([-1000, 1000])
        void drive_1000(uint permille);

        // drive PWM and DIR pins based on normalized float ([0.0, 1.0])
        void drive_norm(float norm);

        // generate audible tone without inducing (additional) movement
        void tone(unsigned long F);

        // Create a motor_PWM object with pins for PWM and direction, and two phase pins for quadrature feedback (not currently implemented)
        motor_PWM (uint _PWMPIN, uint _DIRPIN, uint _PHASE_A, uint _PHASE_B);

        // overload of constructor when quadrature feedback isn't used or available
        motor_PWM (uint _PWMPIN, uint _DIRPIN);

    private:
        // pwm peripheral values
        uint slice_num, wrap, level;

        // internal copy of hardware pins
        uint PWMPIN, DIRPIN, PHASE_A, PHASE_B;

        // wether or not closed loop operation is enabled
        bool closed_loop;
    
};

void motor_PWM::init()
{
    gpio_set_function(PWMPIN, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(PWMPIN);
    pwm_config config = pwm_get_default_config();
    // assuming 125meg clock, 6250 = 20kHz
    pwm_config_set_wrap(&config, 6250);
    pwm_init(slice_num, &config, true);

    gpio_init(DIRPIN);
    gpio_set_dir(DIRPIN, GPIO_OUT);
}

void motor_PWM::init(unsigned long FPWM)
{
    init();
    set_PWM_freq(FPWM);
}

void motor_PWM::set_PWM_freq(unsigned long F) 
{
    unsigned long fclk = clock_get_hz(clk_sys);
    wrap = fclk / F;
    pwm_set_wrap(slice_num, wrap);
}

void motor_PWM::set_duty_1000(uint permille)
{
    level = (permille/1000.0) * float(wrap);
    pwm_set_gpio_level(PWMPIN, level);
}

void motor_PWM::set_duty_127(int8_t byte)
{
    level = (byte/127.0) * float(wrap);
    pwm_set_gpio_level(PWMPIN, level);
}

void motor_PWM::set_duty_norm(float norm)
{
    level = norm * float(wrap);
    pwm_set_gpio_level(PWMPIN, level);
}

void motor_PWM::set_direction(bool clockwise)
{
    gpio_put(DIRPIN, clockwise);
}

void motor_PWM::drive_127(int8_t drive)
{
    // simple boolean check for sign
    set_direction( (drive > 0) );
    set_duty_127( abs(drive));
}

// void motor_PWM::drive_1000(uint permille)
// {
//     // not implemented
// }

void motor_PWM::drive_norm(float drive)
{
    // simple boolean check for sign
    set_direction( (drive > 0) );
    set_duty_norm( abs(drive));
}

// // modulate a jitter of a particular frequency onto the drive signal, creating a tone
// void motor_PWM::tone(unsigned long F)
// {
//     // not implemented
// }

// Construct a Leg object which has pins for PWM&DIR, two quadrature phases, and a physical offset angle from the x-axis
motor_PWM::motor_PWM(uint _PWMPIN, uint _DIRPIN, uint _PHASE_A, uint _PHASE_B)
{
    PWMPIN = _PWMPIN;
    DIRPIN = _DIRPIN;
    PHASE_A = _PHASE_A;
    PHASE_B = _PHASE_B;
    closed_loop = true;
}

// Construct a Leg object which has pins for PWM&DIR, and a physical offset angle from the x-axis
motor_PWM::motor_PWM(uint _PWMPIN, uint _DIRPIN)
{
    PWMPIN = _PWMPIN;
    DIRPIN = _DIRPIN;
    closed_loop = false;
}

#endif