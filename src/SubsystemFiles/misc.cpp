#include "main.h"
// This file exists just so that we can have a global variables that dont belong to a subsystem.

//Auton Selector
rd::Selector selector({
    
});

rd::Console console;

pros::Controller master(pros::E_CONTROLLER_MASTER);


pros::Optical ring_optic_sensor(0);

// Helper function to set brakes on all subsystems
void setBrakes()
{
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    setIntakeBrakes();
    setStakeBrake();
}


