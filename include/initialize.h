#include "api.h"
#include "main.h"

    int drvtrFB;
	int drvtrLR;
	int drvtrDZ = 10;
    
    pros::Controller master(pros::E_CONTROLLER_MASTER);

	pros::Motor leftFront(5,0);
	pros::Motor leftBack(4,0);
	pros::MotorGroup leftWheels({leftFront,leftBack});

	pros::Motor rightFront(1,1);
	pros::Motor rightBack(3,1);
	pros::MotorGroup rightWheels({rightFront,rightBack});

	pros::MotorGroup allWheels({leftFront,leftBack,rightFront,rightBack});

	pros::GPS GPS (10);