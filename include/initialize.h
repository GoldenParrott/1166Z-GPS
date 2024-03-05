#include "api.h"
#include "main.h"

    int drvtrFB;
	int drvtrLR;
	int drvtrDZ = 10;
     
    pros::Controller master(pros::E_CONTROLLER_MASTER);

	pros::Motor leftFront(1,0);
	pros::Motor leftMiddle(2,0);
	pros::Motor leftBack(3,0);
	pros::MotorGroup leftWheels({leftFront,leftMiddle,leftBack});

	pros::Motor rightFront(4,1);
	pros::Motor rightMiddle(5,0);
	pros::Motor rightBack(6,1);
	pros::MotorGroup rightWheels({rightFront,rightMiddle,rightBack});

	pros::MotorGroup allWheels({leftFront,leftMiddle,leftBack,rightFront,rightMiddle,rightBack});

	pros::GPS GPS (10);