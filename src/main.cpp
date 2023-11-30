#include "main.h"
#include "ARMS/config.h"
#include "ui.h"

bool debug = true;
void initialize()
{
    pros::Task CataController(cataControl);

    arms::init();
    arms::selector::destroy();
    selector::init(-1);
    while ((*arms::odom::imu).is_calibrating())
    {
        pros::delay(10);
    }
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

void autonomous()
{
    selector::shutdown();
    selector::runauton();
    //selector::runauton();

    // if (au)
    //   arms::odom::reset({0, 0}, 0);
    // au=false;
    // chassis::move({24, 0,0}, 100);
}

void opcontrol()
{
    // arms::chassis::move({0, 0, 0}, 100, 0.25);
    arms::chassis::setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    while (true)
    {
        if (debug)
            if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN) && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT))
                selector::init();
        selector::debugRuns();

        setDriveMotors();
        setIntakeMotor();
        setPistonStates();
        pros::delay(10);
    }
}
