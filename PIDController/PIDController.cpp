#include "PIDController.h"

PIDController::PIDController (const unsigned int kP, const unsigned int kI, const unsigned int kD, const unsigned int dt) {
    if (kP < 10000){ this->_kP = kP; }
    if (kI < 10000){ this->_kI = kI; }
    if (kD < 10000){ this->_kD = kD; }
    if (dt < 10000){ this->_dt = dt; }
}

PIDErrorStatus PIDController::setPGain(const unsigned int kP){
    if (kP < 10000){
        this->_kP = kP;
        return PID_no_error;
    }
    else{
        return PID_error_val_out_of_range;
    }
}

PIDErrorStatus PIDController::setIGain(const unsigned int kI){
    if (kI < 10000){
        this->_kI = kI;
        return PID_no_error;
    }
    else{
        return PID_error_val_out_of_range;
    }
}

PIDErrorStatus PIDController::setDGain(const unsigned int kD){
    if (kD < 10000){
        this->_kD = kD;
        return PID_no_error;
    }
    else{
        return PID_error_val_out_of_range;
    }
}

PIDErrorStatus PIDController::setTimeInterval(const unsigned int dt){
    if (dt < 10000){
        this->_dt = dt;
        return PID_no_error;
    }
    else{
        return PID_error_val_out_of_range;
    }
}

PIDErrorStatus PIDController::getPIDOutput(const int setPoint, const int input, int & output){
    this->_output = 0;
    PIDErrorStatus status = PID_no_error;
    status = this->_calculateProportional(setPoint, input);
    status = this->_calculateIntegral(setPoint, input);
    status = this->_calculateDerivative(setPoint, input);
    if(status == PID_no_error){
        output = this->_output / 100;
    }
    return status;
}

PIDErrorStatus PIDController::_calculateProportional(const int setPoint, const int input)
{
    this->_output += this->_kP * ((setPoint - input) * 100);
    return PID_no_error;
}

PIDErrorStatus PIDController::_calculateIntegral(const int setPoint, const int input)
{
    this->_errorSum += this->_dt * ((setPoint - input) * 100);
    this->_output += this->_kI * this->_errorSum;
    return PID_no_error;
}

PIDErrorStatus PIDController::_calculateDerivative(const int setPoint, const int input)
{
    int error = ((setPoint - input) * 100);
    this->_output += kD * ((error - this->_lastError) / dt);
    this->_lastError = error;
    return PID_no_error;
}




