#include "main.h"

/* Movement Functions */

void moveToPoint(float x, float y, int timeout, bool fwd, bool async, float maxSpeed, float minSpeed, float earlyExit){
    chassis.moveToPoint(x, y, timeout,{.forwards=fwd,.maxSpeed=maxSpeed,.minSpeed=minSpeed,.earlyExitRange=earlyExit},async);
}

void turnToPoint(float x, float y, int timeout,bool fwd, bool async, int maxSpeed, int minSpeed, lemlib::AngularDirection dir, float earlyExit){
    chassis.turnToPoint(x, y, timeout,{.forwards=fwd,.maxSpeed=maxSpeed,.minSpeed=minSpeed,.direction=dir,.earlyExitRange=earlyExit},async);
}

void moveToPose(float x,float y, float theta, int timeout,bool fwd, bool async,float lead,float maxSpeed,float minSpeed,float earlyExit){
    chassis.moveToPose(x, y, theta, timeout,{.forwards=fwd,.lead=lead,.maxSpeed=maxSpeed,.minSpeed=minSpeed,.earlyExitRange=earlyExit},async);
}

/* Tuning Functions */

// tune kP and kD
void tuneAngularPID()
{
    chassis.setPose(0, 0, 0);
    chassis.turnToHeading(90, 10000);
}

void tuneLinearPID()
{
    chassis.setPose(0, 0, 0);
    chassis.moveToPoint(0, 48, 10000);
}
