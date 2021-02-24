#ifndef IPIDController_H
#define IPIDController_H

enum PIDErrorStatus{
    PID_no_error = 0U,
    PID_error_val_out_of_range = 1U,
};

class IPIDController{
    private:
        IPIDController(){}

    public:
        //Setters
        virtual PIDErrorStatus setPGain         (const unsigned int kP) = 0;
        virtual PIDErrorStatus setIGain         (const unsigned int kI) = 0;
        virtual PIDErrorStatus setDGain         (const unsigned int kD) = 0;
        virtual PIDErrorStatus setTimeInterval  (const unsigned int dt) = 0;

        virtual PIDErrorStatus getPIDOutput     (const int setPoint, const int error, int & output) = 0;

        virtual ~IPIDController() = 0;
};


#endif