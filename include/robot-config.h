using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor LeftBwd;
extern motor RightBwd;
extern motor Cata;
extern motor LeftFwd;
extern motor LeftCtr;
extern motor RightFwd;
extern motor RightCtr;
extern limit Limit;
extern digital_out PistonThingy;
extern motor Motor11;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );