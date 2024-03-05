#include "main.h"
#include "api.h"
#include "initialize.h"
#include <string>

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void Gotoposition(double *desx,double *desy){

    int angle = GPS.get_rotation();

	double *x;
	double *y;
    GPS.get_offset(x, y);

    int diffx = int (desx - x);
    int diffy = int (desy - y);

    double resultx = pow(diffx,2);
    double resulty = pow(diffy,2);
    double hyp = sqrt(resultx + resulty);
    
    int distance = (hyp/360)*(4*PI);

	int turnAngle;
	int turnAnglePlus;
	int turnAngleMinus;
    
	if(diffx > 0){

	    turnAngle = (atan(diffy/(diffx)) + 180);

        if (turnAngle >= 360){
            turnAngle = turnAngle - 360;
        }

	    turnAnglePlus =	turnAngle + 5;
	    turnAngleMinus = turnAngle - 5;

    }else if(diffx <= 0){

        turnAngle = atan(diffy/(diffx));
	    turnAnglePlus =	turnAngle + 5;
	    turnAngleMinus = turnAngle - 5;

    }

    leftWheels.move(64);
    rightWheels.move(-64);
    
	if (turnAngle)

	waitUntil((GPS.get_rotation()>turnAngleMinus)&&(GPS.get_rotation()<turnAnglePlus));

	allWheels.brake();

	pros::delay(500);
}


void opcontrol() {

double *x;
double *y;

GPS.set_position(1.6,0.85,270);
GPS.set_data_rate(100);

	while (true) {
	
		drvtrFB = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    	drvtrLR = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
   
    	if((abs(drvtrFB)>drvtrDZ)||(abs(drvtrLR)>drvtrDZ)) {

    	    rightWheels.move((drvtrFB-drvtrLR));
    	    leftWheels.move((drvtrFB+drvtrLR));

    	}else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)== true){

			double *x;
			double *y;

			allWheels.move_relative(360,100);
			waitUntil(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)== false);

		}else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP) == true){

			Gotoposition(0,0);
			
		} else{

    	    allWheels.brake();

    	}
	}
}
