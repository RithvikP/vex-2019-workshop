#include "main.h"

// A macro (shortcut) that allows one to just use "delay" to pause code execution.
// Time is in milliseconds.
#define delay(time) pros::delay(time)

/**
 * Runs autonomous code where the robot moves without any driver input.
 * 
 * This mode is activated using a match or field controller.
 */
void autonomous() {
  // Create a chassis to use for autonomous (this has built in autonomous control)
  // The last two numbers are used to tune turn and move amounts
  auto chassis = ChassisControllerFactory::create(
    -RIGHT_DRIVE_PORT, LEFT_DRIVE_PORT,
    AbstractMotor::gearset::green,
    {4_in, 12.6_in});

  chassis.setMaxVelocity(70);

  // Move forwards 10 inches
  chassis.moveDistance(10_in);

  // Close the claw
  move_claw(127);
  delay(150);
  // Apply constant power to hold a cube
  move_claw(25);

  // Lift up for 300 milliseconds
  move_lift(127);
  delay(300);
  // Apply constant power to hold the arm up
  move_lift(10);


  // Turn 90 degrees to the left
  chassis.turnAngle(90_deg);

  chassis.moveDistance(5_in);
  
  
  /*
   * Add new autonomous code here (and edit or remove the example above)
   */
}
