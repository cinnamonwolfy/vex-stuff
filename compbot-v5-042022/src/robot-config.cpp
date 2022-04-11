#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor M1 = motor(PORT1, ratio36_1, true);
motor M2 = motor(PORT2, ratio36_1, false);
motor M4 = motor(PORT4, ratio36_1, false);
motor M5 = motor(PORT5, ratio36_1, true);
motor M6 = motor(PORT6, ratio36_1, false);
motor M7 = motor(PORT7, ratio36_1, true);
motor M11 = motor(PORT11, ratio18_1, true);
motor M12 = motor(PORT12, ratio18_1, false);
motor M14 = motor(PORT14, ratio18_1, false);
motor M15 = motor(PORT15, ratio18_1, false);
motor M16 = motor(PORT16, ratio18_1, true);
motor M17 = motor(PORT17, ratio18_1, true);
motor M19 = motor(PORT19, ratio18_1, false);
motor M20 = motor(PORT20, ratio18_1, true);
motor M8 = motor(PORT8, ratio18_1, false);
motor M9 = motor(PORT9, ratio18_1, true);
controller Controller1 = controller(primary);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}