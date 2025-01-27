#include "api.h" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pose.hpp"

// inline bool isRunningAuton = false;

void tuneAngularPID();
void tuneAngularWindUp();
void tuneLinearPID();
void tuneLinearWindUp();


void clampUp();
void clampDown();

void intakePivot();
void intake();
void outtake();
void stopIntake();

void doinkerDown();
void doinkerUp();

void rushDown();
void rushUp();


void moveToPoint(float x, float y,int timeout, bool fwd = true,bool async = true,float maxSpeed = 127,float minSpeed = 0,float earlyExit = 0);
void turnToPoint(float x, float y, int timeout,bool fwd = true, bool async = true, int maxSpeed = 127, int minSpeed = 0, lemlib::AngularDirection dir = lemlib::AngularDirection::AUTO, float earlyExit = 0);
void moveToPose(float x,float y, float theta, int timeout,bool fwd = true, bool async = true,float lead = .6,float maxSpeed = 127,float minSpeed = 0,float earlyExit = 0);
