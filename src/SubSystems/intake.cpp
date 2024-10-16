#include "main.h"

bool overrideIntake = false;
//     Intake.move((127*controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2))-(127*controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)));

void setIntake(int power,int power2)
{
    Intake.move(power);
    Intake2.move(power2);

}
void setIntake(int power)
{
    Intake.move(power);
    Intake2.move(power);

}
bool isTriBall(pros::Optical op)
{
    
    double hue = op.get_hue();
    return ((hue <= hueRange[0][0] && hue >= hueRange[0][1]) || (hue <= hueRange[1][0] && hue >= hueRange[1][1]) || (hue <= hueRange[2][0] && hue >= hueRange[2][1]));
}
void setIntakeMotor()
{
    if (controller.get_digital(controls::intakeOverride))
    {
        overrideIntake = (overrideIntake ? false : true);
    }
    bool isReverse = false;
    bool isForward = false;
    int intakePower = 127 * (controller.get_digital(controls::intakeOut) - controller.get_digital(controls::intakeIn));
    int intake2Power = 85 * (controller.get_digital(controls::intakeOut) - controller.get_digital(controls::intakeIn));

    isReverse = (intakePower <= 0 ? false : true);
    isForward = (intakePower >= 0 ? false : true);

    if (!overrideIntake)
    {
        // if tri ball is detected and the intake is spinning forward
        if ((isTriBall(IntakeOpticalIn2) || isTriBall(IntakeOpticalIn) )&& isForward)
        {
            intakePower = 0;
            intake2Power = 0;
            // return;
        }
        // if tri ball is detected and the intake is NOT spinning backwards

        if (isTriBall(IntakeOpticalOut) && !isReverse)
        {
            intakePower = -127;
            intake2Power = -100;
        }
    }

    setIntake(intakePower,intake2Power);
}