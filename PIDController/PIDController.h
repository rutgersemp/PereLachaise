#ifndef PIDController_H
#define PIDController_H

#include "IPIDController.h"

class PIDController : public IPIDController{
    private:
        unsigned int _kP{0};
        unsigned int _kI{0};
        unsigned int _kD{0};
        unsigned int _dt{0};
        int _output{0};
        int _lastError{0};
        long _errorSum{0};
        



        PIDErrorStatus _calculateProportional   (const int setPoint, const int input);
        PIDErrorStatus _calculateIntegral       (const int setPoint, const int input);
        PIDErrorStatus _calculateDerivative     (const int setPoint, const int input);

    public:
        PIDController(){}
        PIDController(const unsigned int kP, const unsigned int kI, const unsigned int kD, const unsigned int dt);
        ~PIDController(){}

        PIDErrorStatus setPGain         (const unsigned int kP) override;
        PIDErrorStatus setIGain         (const unsigned int kI) override;
        PIDErrorStatus setDGain         (const unsigned int kD) override;
        PIDErrorStatus setTimeInterval  (const unsigned int dt) override;

        PIDErrorStatus getPIDOutput     (const int setPoint, const int input, int & output) override;
};


#endif