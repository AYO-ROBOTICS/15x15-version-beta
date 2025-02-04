#include "main.h"

/* Motor Groups declaration and initialization */

/**
 *
 ** leftMotors represents the grouping of motors that are on the LEFT side of the DRIVETRAIN

 * ARGUMENTS:
 *
 ** The first argument in leftMotors represents the ports that each motor is connected to.
 * ! in this case our motor ports will be negative, negativity in motor ports indicates that the motor should be spinning in a reversed direction.
 * ! with a positive port, motors spin clockwise at a positive input. With a negative port, motors spin counterclockwise at a positive input.
 *
 ** The second argument represents the gearset of the motor
 * ! There are different types of gearsets: Red, Green, and Blue.
 * ! Blue being the fastest at 600PM, Red being the slowest at 100RPM, and Green being the middle range at 200RPM.
 *
 */
/* Arguments:

 * The first argument in leftMotors represents the ports that each motor is connected to
 * 	- in this case our motor ports will be negative, negativity in motor ports indicates that the motor should be spinning in a reversed direction
 *	- with a positive port, motors spin clockwise at a positive input. with a negative port, motors spin counterclockwise at a positive input.

 * The second argument represents the gearset of the motor.
 *	- There are different types of gearsets: Red, Green, Blue, with
 *	- blue being the fastest at 600RPM, Red being the slowest at 100RPM, and Green being the middle range at 200RPM

 */

pros::MotorGroup leftMotors({0, 0, 0}, pros::MotorGearset::blue); // Motor ports {4,3,2} at 600RPM

/**
 ** Same logic from leftMotors applies to rightMotors, including arguments and motor gearsets.
 ** rightMotors represents the grouping of motors that are on the RIGHT side of the DRIVETRAIN
 ** Positive motor ports because the motors should be spinning clockwise for the robot to move forward.
 */
pros::MotorGroup rightMotors({0, 0, 0}, pros::MotorGearset::blue); // Motor ports {8,9,10} at 600RPM (Blue gearset)

/* End of Motor Group declaration and initialization */

/* Start of DRIVETRAIN code */

/**
 * ! This block of code creates a DRIVETRAIN object,
 *
 *? What does a drive train object do?
 ** This stores our left side motors, right side motors, our TRACKWIDTH, WHEELDIAMETER,
 ** DRIVERPM, and our HORIZONTALDRIFT value
 *
 * TRACKWIDTH:
 * ! The distance between the left side and right side of the DRIVETRAIN.
 * ! Specifically from the middle of the wheels.
 *
 * WHEELDIAMETER:
 * ! The diameter of our DRIVETRAIN wheels. We measured using calipers.
 *
 * DRIVERPM:
 * ! The speed our wheels will spin at, this value is different from the motor RPM because we are using a gear ratio,
 * ! Our DRIVETRAIN gearing consists of a 36T gear input and a 48T gear output,  this comes out to be a 3/4 ratio or 0.75,
 * ! We take this 0.75 value and multiply it by our motor RPM to find our DRIVETRAIN wheel RPM,
 * ! Our robot uses a 600RPM motor with a 0.75 gear ratio, making our DRIVETRAIN RPM become 450RPM.
 *
 * HORIZONTALDRIFT:
 * ! A feature that ensures compatibility with multiple types of DRIVETRAINS,
 * ! with both all omni wheels (drift drive), or DRIVETRAINS with center traction wheels.
 * ! It controls how fast the chassis can move while turning, a higher value means,
 * ! The robot has less physical drift when driving and turning in auton and lower value means the opposite.
 * ! We use our default value of 8 because we have center traction wheels which allow us to grip the field more proper.
 *
 *
 */

lemlib::Drivetrain DRIVETRAIN(&leftMotors,  // left motor group
                              &rightMotors, // right motor group
                              11.5,         // Track width: 11.5 INCHES
                              2.75,         // Wheel diameter of our 3D Printed custom Omni Wheels & VEX Traction wheels
                              450,          // drivetrain rpm: 450 RPM
                              8             // horizontal drift: 8
);

/*  End of Drive Train Code */

/* Start of Odometry Code */

/**
 *
 *?s What is odometry?
 ** Odometry is the use of data from motion sensors to estimate change in position over time,
 ** It is used in robotics by some legged or wheeled robots to estimate their position relative to a starting location.
 ** In our case, we will be using tracking wheels in order to track our robots position accurately and precisely.
 *
 *? Why use odometry?
 ** We use odometry for consistency of autonomous routines including both skills autonomous and match autonomous.
 *
 */

/**
 *
 *? For our odometry, we use readings from 2 unique sensors and 3 total sensors:
 **  1. An IMU (Inertial Measurement Unit) using a Vex V5 Inertial Sensor
 **  2. Vertical Tracking wheel using a Vex V5 Rotation Sensor
 **  3. Horizontal Tracking wheel using a Vex V5 Rotation Sensor.
 *
 * IMU:
 * 	! this is used in order to find our current heading value which is the current direction the robot is facing.
 * 	! we can use this value in our odometry to make sure that our robot faces the proper direction when commanded to.
 *
 *
 */
pros::Imu IMU(0);

/**
 *
 * HORIZONTALTRACKINGSENSOR:
 * ! sensor tracks any movement in the horizontal direction of our robot, this is used a lot in the case where our auton paths stray
 * ! due to horizontal contact from our or opposing alliance robots.
 * 
 * ! Horizontal tracking wheels are recommended, however we we're unable to fit one on to our build
 * ! After doing testing, we came to the conclusion that using traction wheels would help us mitigate autonomous inconsistancys in curved movements
 *
 * VERTICALTRACKINGSENSOR:
 * ! sensor tracks vertical movement/straight movements of the robot.
 * ! This allows us to accurately move our robot a specific amount of units forward, as well as account for any contact.
 *
 *
 */
pros::Rotation horizontalTrackingWheelSensor(0); // we do not use a horizontal tracker, this is here do demonstrate how creating one would look like.
pros::Rotation verticalTrackingWheelSensor(0);

/**
 *
 *! These lines of code bind the previously made vertical TrackingWheelSensors into a new object that represents
 *! the tracking wheel.
 *
 *! We will use this tracking wheel in order to physically track our robots movements, same explanation from sensors applies.
 *! Our tracking wheel is custom designed by us at AYO and has a measured diameter of ~1.96
 *
 */
lemlib::TrackingWheel verticalTrackingWheel(&verticalTrackingWheelSensor, 1.96, 0);

/**
 *
 * SENSORS:
 * ! an amalgamation of all our sensors, makes our sensors easily accessible by going through the "sensors" object.
 * ! contains our verticalTrackingWheel, horizontalTrackingWheel, and our IMU.
 *
 * ! additional arguments are verticalTrackingWheel2 and horizontalTrackingWheel2, we decided against using multiple tracking wheels
 * ! for redundancy and ease of code.
 *
 */
lemlib::OdomSensors sensors(nullptr,   // vertical tracking wheel 1, set to null
                            nullptr,                  // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr,                  // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            nullptr                      // inertial sensor
);

/* End of Odometry Code*/

/* Start of PID Code */

/**
 *
 *! This is our lateral PID controller.
 *
 * PID:
 *? What is a PID?
 ** A PID is a controller. It controls a mechanism. It takes a numerical input, and returns a numerical output.
 ** The numerical input is a measurement from a sensor, and the numerical output is the power for an actuator (e.g a motor).
 *
 *? Why do we use PID Controller?
 ** It allows us to have more consistent autonomous routines,
 ** as well as improving how our robots travel in autonomous when put under high load.
 *
 *? What is a laterial PID controller used for?
 ** We use this lateral contoroller in order to ensure that our forwards and backwards movements are consistant, smooth, and fast.
 ** Our lateral controller allows us to gain these improvements and gives us a leg up on the competition.
 *
 */

// lateral PID controller
lemlib::ControllerSettings lateralController(1,  // proportional gain (kP)
                                             0,   // integral gain (kI)
                                             0,   // derivative gain (kD)
                                             0,   // anti windup
                                             0,   // small error range, in inches
                                             0, // small error range timeout, in milliseconds
                                             0,   // large error range, in inches
                                             0, // large error range timeout, in milliseconds
                                             0   // maximum acceleration (slew)
);

/**
 *
 *! This is our angular PID controller.
 *
 *? What is a angular PID controller used for?
 ** We use an angular PID controller to ensure correct turning radius and consitancy.
 ** Having these levels of consistancy in both our lateral and angular movements allows us to have well function autonomous rutines.
 *
 */
// angular PID controller
lemlib::ControllerSettings angularController(1,   // proportional gain (kP)
                                             0,   // integral gain (kI)
                                             0,  // derivative gain (kD)
                                             0,   // anti windup
                                             0, // small error range, in deg
                                             0, // small error range timeout, in milliseconds
                                             0, // large error range, in deg
                                             0, // large error range timeout, in milliseconds
                                             0    // maximum acceleration (slew)
);

/* End of PID Code */

/* Start of chassis */

/**
 *
 * CHASSIS:
 *! This is the amalgomation of our last 4 blocks of code. We combine our drivetrain, lateralController, angularController, and sensors.
 *! This sort of acts as a container for us that allows us to access all of these areas of code without having to memorize all these names.
 *! This is also what we will be calling when using any autonomous rutines or drive controlls.
 */

lemlib::Chassis chassis(DRIVETRAIN,        // drivetrain settings
                        lateralController, // lateral PID settings
                        angularController, // angular PID settings
                        sensors            // odometry sensors
);

/* End of Chassis */

/**
 *! Runs initialization code. This occurs as soon as the program is started.
 *
 ** All other competition modes are blocked by initialize; it is recommended
 ** to keep execution time for this mode under a few seconds.
 */

bool chassis_reversed = false;
void chassisControl(){
    if (!chassis_reversed)
    {
        chassis.tank(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
        master.set_text(0,0,"Forward");
    } 
    else
    {
        chassis.tank(-master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y), -master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
        master.set_text(0,0,"Reversed");
    }
    if (master.get_digital_new_press(DIGITAL_LEFT))
    {
        chassis_reversed = !chassis_reversed;
    }
}