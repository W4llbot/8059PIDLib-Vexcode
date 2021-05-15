using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor FL;
extern motor BL;
extern motor FR;
extern motor BR;
// extern inertial Imu;
extern motor LRoller;
extern motor RRoller;
extern motor Shooter;
extern motor Indexer;
extern line ShooterLine;
extern line IndexerLine;
extern encoder LEncoder;
extern encoder REncoder;
extern timer Timer;

extern competition Competition;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );