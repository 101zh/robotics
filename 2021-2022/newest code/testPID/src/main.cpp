#include "main.h"
using namespace okapi;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
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
pros::ADIDigitalOut piston('E', false);
pros::Motor clawMotor(3);
pros::Motor liftMotor(16);

std::shared_ptr<okapi::OdomChassisController> chassis = okapi::ChassisControllerBuilder()
    .withMotors({2, -17}, {-15, 18})
	.withGains(
        {0.0015, 0, 0.00004},
        {0.002, 0, 0.00004},
        {0.0001, 0.0002, 0.00004}
    )
	.withSensors(
        ADIEncoder{'A', 'B'},
        ADIEncoder{'G', 'H', true}
    )
	.withDimensions(AbstractMotor::gearset::green, {{2.75_in, 15.25_in}, quadEncoderTPR})
    .withOdometry(StateMode::CARTESIAN)    
	.buildOdometry();
	okapi::OdomState state;
	std::shared_ptr<okapi::OdomChassisController> chassis2 = okapi::ChassisControllerBuilder()
    .withMotors({2, -17}, {-15, 18})
	.withDimensions(AbstractMotor::gearset::green, {{4_in, 14.75_in}, imev5GreenTPR})
	.withSensors(
        ADIEncoder{'A', 'B'},
        ADIEncoder{'G', 'H', true}
    )
    .withOdometry({{2.75_in, 15.25_in}, quadEncoderTPR}, StateMode::CARTESIAN)    
	.buildOdometry();
void my_task_fn(void* param) {
     std::cout << "My task runs" << std::endl;
     // ...
	 while (true)
	 {
		//pros::lcd::print(1, "x:%f, y:%f, t:%f", state.x, state.y, state.theta);
		state = chassis->getState();
		pros::delay(20);
	 }
}
void autonomous() {
	/*pros::Task my_task(my_task_fn);
	pros::Motor left_front(10);
	pros::Motor right_front(20, 1);
	pros::Motor left_back(1, 1);
	pros::Motor right_back(11);

	left_front.move_relative(4000, 200);
  	left_back.move_relative(4000, 200);
	right_front.move_relative(4000, 200);
  	right_back.move_relative(4000, 200);*/
	std::shared_ptr<AsyncMotionProfileController> chassisMP = okapi::AsyncMotionProfileControllerBuilder()
    .withLimits({
      1.0, // Maximum linear velocity of the Chassis in m/s
      1.0, // Maximum linear acceleration of the Chassis in m/s/s
      5.0 // Maximum linear jerk of the Chassis in m/s/s/s
    })
    .withOutput(chassis)
    .buildMotionProfileController();

	std::shared_ptr<AsyncPositionController<double, double>> claw = okapi::AsyncPosControllerBuilder()
    .withMotor(3) // lift motor port 3
    //.withGains({0.001, 0, 0})
    .build();

	std::shared_ptr<AsyncPositionController<double, double>> lift = okapi::AsyncPosControllerBuilder()
	.withMotor(16)
	//.withGains({0.001, 0, 0})
	.build();
	piston.set_value(false);
	claw->reset();
	//chassis->setState({0_ft, 7_ft, -90_deg});
	chassis->setState({0_ft, 0_ft, -90_deg});
	//claw->setTarget(3350);
	clawMotor.move_relative(3350, 100);
	pros::delay(2000);
	//claw->waitUntilSettled();
	chassis->moveDistance(-1.75_ft);
	chassis->waitUntilSettled();
	//claw->setTarget(1000);
	clawMotor.move_relative(-2350, 100);
	pros::delay(2000);
	//claw->waitUntilSettled();
	chassis->moveDistance(1.5_ft);
	//chassis->turnToAngle(0_deg);
	//chassis->turnToAngle(68.2_deg);
	//chassis->moveDistance(5.4_ft);
	chassis->driveToPoint({2_ft, 5_ft});
	piston.set_value(true);
	liftMotor.move_relative(-3500, 100);
	pros::delay(1000);
	chassis->driveToPoint({3.5_ft, 7.2_ft});
	chassis->turnToAngle(0_deg);
	chassis->moveDistance(10_in);
	liftMotor.move_relative(1000, 100);
	pros::delay(1000);
	piston.set_value(false);
	liftMotor.move_relative(-1000, 100);
	pros::delay(1000);
	chassis->moveDistance(-10_in);
	chassis->waitUntilSettled();
	liftMotor.move_relative(3500, 100);
	pros::delay(500);
	chassis->driveToPoint({-0_ft, 7.2_ft});
	piston.set_value(true);
	liftMotor.move_relative(-3500, 100);
	chassis->moveDistance(-2_ft);
	//chassis->turnToAngle(180_deg);
	chassis->driveToPoint({2_ft, 2.5_ft});
	//chassis->turnToAngle(90_deg);
	chassis->driveToPoint({5_ft, 2.5_ft});
	chassis->driveToPoint({5_ft, 3_ft});
	clawMotor.move_relative(1000, 100);
	piston.set_value(false);
	clawMotor.move_relative(-1000, 100);
	chassis->waitUntilSettled();
}

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
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_front(2);
	pros::Motor right_front(15, 1);
	pros::Motor left_back(17, 1);
	pros::Motor right_back(18);
	pros::Motor lift(18);
	pros::ADIEncoder leftTracking('A', 'B');
	pros::ADIEncoder rightTracking('G', 'H', 1);
	pros::Motor fourbar(14);

	while (true) {
		if (master.get_digital(DIGITAL_R1))
		{
			piston.set_value(true);
		}
		if (master.get_digital(DIGITAL_R2))
		{
			piston.set_value(false);
		}
		
		
		state = chassis->getState();
		//pros::lcd::print(1, "x:%f, y:%f, t:%f", state.x * mmToInch * 1000, state.y * 1000 * mmToInch, state.theta* radianToDegree);
		pros::lcd::print(1, "%f", leftTracking.get_value());
		pros::lcd::print(2, "%f", rightTracking.get_value());
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 				(pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 				(pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int power = master.get_analog(ANALOG_LEFT_Y);
    	int turn = master.get_analog(ANALOG_RIGHT_X);
    	int left = power + turn;
    	int right = power - turn;
		left_front.move(left);
		left_back.move(left);
		right_front.move(right);
		right_back.move(right);
		fourbar.set_brake_mode(MOTOR_BRAKE_HOLD);
		pros::delay(2);
	}
}
