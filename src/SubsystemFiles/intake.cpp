#include "main.h"
#include "pros/abstract_motor.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"


void setIntakeBrakes(){

    intakeMotor.set_brake_mode(pros::MotorBrake::coast);

}

void intakeControl(){

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
        intakeMotor.move(intakeSpeed);
    }else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
        intakeMotor.move(-intakeSpeed);
    }else{
        intakeMotor.brake();
    }

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)){
        intakePivotStatus=!intakePivotStatus;
        intakePivotPistons.set_value(intakePivotStatus);
    }

}

pros::Task colorSorting{[]{

    intakeColorSensor.set_led_pwm(100);
    
    while(true){


        /* when the specified color */
        if(sortColor==1 && !isLoaded){

            isLoaded = (intakeColorSensor.get_hue()>5 && intakeColorSensor.get_hue()<25) ? true:false; /* if the ring is red, prepare to get rid of it */

        }else if(sortColor==-1 && !isLoaded){

            isLoaded = (intakeColorSensor.get_hue()>185 && intakeColorSensor.get_hue()<215) ? true:false; /*  if the ring is blue, prepare to get rid of it */

        }


        /* if the motors current draw is massive, it's probably stuck */
        if(intakeMotor.get_current_draw()>2300){
            isStuck = true;
        }



        if(((isLoaded && intakeDistanceSensor.get_distance() < 40 && intakeMotor.get_actual_velocity() > 50)  || isStuck)){

            /* reverse intakeMotor for specified time. if intakeMotor is stuck then reverse for longer */
            pros::delay(200);

            intakeMotor.move(-intakeSpeed);
            pros::delay(250 + 250*(isStuck));
            intakeMotor.move(intakeSpeed);

            /* reset */
            isStuck  = false;
            isLoaded = false;
        }

        pros::delay(20);

    }


    
}};