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
  auto chassis = ChassisControllerFactory::create(
    RIGHT_DRIVE_PORT, -LEFT_DRIVE_PORT,
    AbstractMotor::gearset::green,
    {4.15_in, 10.5_in});

  // Move forwards 10 inches
  chassis.moveDistance(10_in);
  // Turn 90 degrees
  chassis.turnAngle(90_deg);
  // Lift up for 300 milliseconds
  move_lift(127);
  delay(300);
  move_lift(0);

  /*
   * Add new autonomous code here (and edit or remove the example above)
   */
}
