#include "main.h"

/**
 * This is basic robot code that allows your robot to move and manipulate objects using a remote controller.
 * 
 * While this code does allow the robot to fully function, it can be improved and expanded in numerous ways.
 * If you desire, you can talk to a volunteer about ways to improve this code to better prepare it for competitions ahead.
 */

#define DRIVE_SPEED 0.75 // Changes the maximum drive speed (range between 0 and 1)
#define ARCADE true // Controls whether the drive is tank style (false) or arcade style (true)
#define DRIVE_THRESHOLD 8 // Controls the minimum power that can be assigned to drive motors

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
	/*
	 * Define variables used by different robot functionality
	 */
	// Drive code variables
	int left_y;
	int right_x;
	int right_y;
	int right_power;
	int left_power;

	// Define motors and the controller for the robot in driver control.
	// Motors are defined locally to prevent confusion in autonomous coding.
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	pros::Motor left_drive (1);
	pros::Motor right_drive (2);
	pros::Motor lift (3);
	pros::Motor claw (3);

	lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	claw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	while (true) {
		/*
		 * Drivetrain code
		 * This code controls how the robot moves around the field
		 */

		left_y = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		right_x = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		right_y = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

		// Filter joystick values to prevent the drive from responding to miscalibrated joysticks
		if (std::abs(left_y) < DRIVE_THRESHOLD) {
			left_y = 0;
		}
		if (std::abs(right_y) < DRIVE_THRESHOLD) {
			right_y = 0;
		}
		if(std::abs(right_x) < DRIVE_THRESHOLD) {
			right_x = 0;
		}

		// Choose between arcade and tank drive controls
		if (ARCADE) {
			right_power = left_y - right_x;
			left_power = left_y + right_x;
		}
		else {
			right_power = right_y;
			left_power = left_y;
		}

		// Limit motor powers
		if (std::abs(right_power) > 127) {
			right_power = std::copysign(127, right_power); // Copies the sign of right_power to 127
		}
		if (std::abs(left_power) > 127) {
			left_power = std::copysign(127, left_power); // Copies the sign of left_power to 127
		}

		// Limit drivetrain speed
		right_power = (int) (right_power * DRIVE_SPEED);
		left_power = (int) (left_power * DRIVE_SPEED);

		// Assign power to the motors
		right_drive.move(right_power);
		left_drive.move(left_power);

		/*
		 * Lift code
		 * This code controls the arm of the robot
		 */

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) == 1) {	// Check if a button on the controller is pressed
			lift.move(127); // Move the lift up
			while (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) == 1) { // Wait for the button to be released
				pros::delay(10);
			}
			lift.move(0);
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) == 1) {
			lift.move(-127); // Move the lift down
			while (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) == 1) {
				pros::delay(10);
			}
			lift.move(0);
		}

		/*
		 * Claw code
		 * This code controls the claw on the robot
		 */
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) == 1) {
			claw.move(127); // Close the claw
			while (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) == 1) {
				pros::delay(10);
			}
			claw.move(0);
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) == 1) {
			claw.move(-127); // Open the claw
			while (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) == 1) {
				pros::delay(10);
			}
			claw.move(0);
		}
		

		// IMPORTANT DO NOT REMOVE
		// This delay allows all robot related functionality to be run between iterations of this while loop.
		pros::delay(10);
	}
}
