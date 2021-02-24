#include "PIDController.h"

PIDController::PIDController (const unsigned int kP, const unsigned int kI, const unsigned int kD, const unsigned int dt) {
    if (kP < 10000){ this._kP = kP; }
    if (kI < 10000){ this._kI = kI; }
    if (kD < 10000){ this._kD = kD; }
    if (dt < 10000){ this._dt = dt; }
}

PIDErrorStatus PIDController::setPGain(const unsigned int kP){
    if (kP < 10000){
        this._kP = kP;
        return PID_no_error;
    }
    else{
        return PID_error_val_out_of_range;
    }
}
