/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\hurri                                            */
/*    Created:      Thu Aug 29 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "vision.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
// A global instance of vex::competition
vex::competition Competition;

// define your global instances of motors and other devices here


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */ 
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton( void ) {//this runs before the auton
  
  vex::motor rightrear (vex::PORT10, vex::gearSetting::ratio18_1, true);
  vex::motor leftrear (vex::PORT9, vex::gearSetting::ratio18_1, true);
  vex::motor leftfront (vex::PORT7, vex::gearSetting::ratio18_1, true);
  vex::motor rightfront (vex::PORT8, vex::gearSetting::ratio18_1, true);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous( void ) {//this runs without human interaction
  
  //init motors and sensors
  vex::motor rightrear (vex::PORT10, vex::gearSetting::ratio18_1, true);
  vex::motor leftrear (vex::PORT9, vex::gearSetting::ratio18_1, true);
  vex::motor leftfront (vex::PORT7, vex::gearSetting::ratio18_1, true);
  vex::motor rightfront (vex::PORT8, vex::gearSetting::ratio18_1, true);
  vex::vision visionsensor (vex::PORT20);
  //vex::controller controller1 = vex::controller();// this code does nothing
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  while(true){//loop forever
    visionsensor.takeSnapshot(1);//record pic
    int fwd = 0;//init vars 
    int sts = 0;
    int rtn = 50;
    Brain.Screen.clearScreen();
    Brain.Screen.print("width:");//line1
    Brain.Screen.print(visionsensor.largestObject.width);//line2
    Brain.Screen.print("center X:");//line3
    Brain.Screen.print(visionsensor.largestObject.centerX);//line4
    if (visionsensor.largestObject.exists && visionsensor.largestObject.width>5) {//if the biggest object is bigger and 5 pixels wide
      rtn= (visionsensor.largestObject.centerX/3)-53;//turn the ammount of center
      if((visionsensor.largestObject.centerX/3)-53<5){//if its less than 5 pixels off 
        if(visionsensor.largestObject.width<100){//and if the width is lessthan than 100 pixels
         fwd=3000/visionsensor.largestObject.width;//do this move fwd inverse propotionaly to the size
         if(fwd<30){//and if fwd speed if less that 30%
           fwd=0;// just dont move
         }
        }
      }
      
      // Allow other tasks to run
      //this_thread::sleep_for(10);
      
       
    }//move acording to the vars set up earlier
    rightrear.spin(vex::directionType::fwd,  2*(fwd+sts-rtn),vex::velocityUnits::rpm);
    leftrear.spin(vex::directionType::fwd,   2*(-rtn-sts-fwd),vex::velocityUnits::rpm);
    rightfront.spin(vex::directionType::fwd, 2*(fwd-sts-rtn),vex::velocityUnits::rpm);
    leftfront.spin(vex::directionType::fwd,  2*(-rtn-fwd+sts),vex::velocityUnits::rpm);
    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources.
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol( void ) {
  
  vex::motor rightrear (vex::PORT10, vex::gearSetting::ratio18_1, true);
  vex::motor leftrear (vex::PORT9, vex::gearSetting::ratio18_1, true);
  vex::motor leftfront (vex::PORT7, vex::gearSetting::ratio18_1, true);
  vex::motor rightfront (vex::PORT8, vex::gearSetting::ratio18_1, true);
  vex::motor tipper (vex::PORT19, vex::gearSetting::ratio18_1, true);
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo 
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to 
    // update your motors, etc.
    // ........................................................................
    
    vex::controller controller1 = vex::controller();
    // Allow other tasks to run
    this_thread::sleep_for(10);
    int fwd = controller1.Axis3.value(); 
    int sts = controller1.Axis4.value();
    int rtn = -controller1.Axis1.value();
    rightrear.spin(vex::directionType::fwd,  2*(fwd+sts+rtn),vex::velocityUnits::rpm);
    leftrear.spin(vex::directionType::fwd,   2*(rtn-sts-fwd),vex::velocityUnits::rpm);
    rightfront.spin(vex::directionType::fwd, 2*(fwd-sts+rtn),vex::velocityUnits::rpm);
    leftfront.spin(vex::directionType::fwd,  2*(rtn-fwd+sts),vex::velocityUnits::rpm);
    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
      
} 