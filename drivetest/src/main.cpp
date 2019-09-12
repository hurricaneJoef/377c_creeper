/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\hurri                                            */
/*    Created:      Thu Sep 12 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here

int main() {
    int count = 0;
    vex::motor rightrear (vex::PORT10, vex::gearSetting::ratio18_1, true);
    vex::motor leftrear (vex::PORT9, vex::gearSetting::ratio18_1, true);
    vex::motor leftfront (vex::PORT7, vex::gearSetting::ratio18_1, true);
    vex::motor rightfront (vex::PORT8, vex::gearSetting::ratio18_1, true);
    vex::controller controller1 = vex::controller();
    while(1) {
        Brain.Screen.printAt( 10, 50, "Hello V5 %d", count++ );
        // Allow other tasks to run
        this_thread::sleep_for(10);
        int fwd = controller1.Axis3.value(); 
        int sts = controller1.Axis4.value();
        int rtn = controller1.Axis1.value();
        rightrear.spin(vex::directionType::fwd,  fwd+sts+rtn,vex::velocityUnits::pct);
        leftrear.spin(vex::directionType::fwd,   sts-fwd+rtn,vex::velocityUnits::pct);
        rightfront.spin(vex::directionType::fwd, fwd-sts+rtn,vex::velocityUnits::pct);
        leftfront.spin(vex::directionType::fwd,  rtn-fwd-sts,vex::velocityUnits::pct);
    }
}
