#include "main.h"
#include "pros/misc.h"
void setIntakePiston(bool trigger)
{
    IntakePu1.set_value(trigger);
    IntakePu2.set_value(trigger);
}
void setWingPiston(bool trigger)
{
    WingPu1.set_value(trigger);
    WingPu2.set_value(trigger);
}
void setPistonStates()
{

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
    {
        IntakeOut = IntakeOut ? false : true;
        setIntakePiston(IntakeOut);
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2))
    {
        WingsOut = WingsOut ? false : true;
        setWingPiston(WingsOut);
    }
}