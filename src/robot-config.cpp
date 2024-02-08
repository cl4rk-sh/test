#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LeftBwd = motor(PORT1, ratio18_1, false);
motor RightBwd = motor(PORT15, ratio18_1, true);
motor Cata = motor(PORT18, ratio18_1, false);
motor LeftFwd = motor(PORT12, ratio18_1, true);
motor LeftCtr = motor(PORT13, ratio18_1, true);
motor RightFwd = motor(PORT16, ratio18_1, false);
motor RightCtr = motor(PORT17, ratio18_1, false);
limit Limit = limit(Brain.ThreeWirePort.H);
digital_out PistonThingy = digital_out(Brain.ThreeWirePort.G);
motor Motor11 = motor(PORT11, ratio18_1, false);

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