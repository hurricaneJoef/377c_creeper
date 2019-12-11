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
#define maxtilt 495 //deg
#define mintilt 0 //deg 
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
vex::motor rightrear (vex::PORT10, vex::gearSetting::ratio18_1, true);
  vex::motor leftrear (vex::PORT9, vex::gearSetting::ratio18_1, true);
  vex::motor leftfront (vex::PORT7, vex::gearSetting::ratio18_1, true);
  vex::motor rightfront (vex::PORT8, vex::gearSetting::ratio18_1, true);
  vex::motor lift (vex::PORT18, vex::gearSetting::ratio18_1, true);
  vex::motor tilt (vex::PORT19, vex::gearSetting::ratio18_1, true);
  vex::motor lefttread (vex::PORT17, vex::gearSetting::ratio18_1, true);
  vex::motor righttread (vex::PORT6, vex::gearSetting::ratio18_1, true);
  vex::vision visionsensor (vex::PORT20);
  vex::controller controller1 = vex::controller();
void pre_auton( void ) {//this runs before the auton
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
void mecanum_move(int forward, int rotation, int strafe, bool dist=false, float velocitymult= .1){
  if(dist){
    rightrear.startRotateFor(vex::directionType::fwd,  (forward+strafe-rotation),vex::rotationUnits::rev,2*(forward+strafe-rotation)*velocitymult,vex::velocityUnits::rpm);
    leftrear.startRotateFor(vex::directionType::fwd,   (-rotation-strafe-forward),vex::rotationUnits::rev,2*(-rotation-strafe-forward)*velocitymult,vex::velocityUnits::rpm);
    rightfront.startRotateFor(vex::directionType::fwd, (forward-strafe-rotation),vex::rotationUnits::rev,2*(forward-strafe-rotation)*velocitymult,vex::velocityUnits::rpm);
    leftfront.rotateFor(vex::directionType::fwd,  (-rotation-forward+strafe),vex::rotationUnits::rev,2*(-rotation-forward+strafe)*velocitymult,vex::velocityUnits::rpm);
  }else{
    rightrear.spin(vex::directionType::fwd,  2*(forward+strafe-rotation),vex::velocityUnits::rpm);
    leftrear.spin(vex::directionType::fwd,   2*(-rotation-strafe-forward),vex::velocityUnits::rpm);
    rightfront.spin(vex::directionType::fwd, 2*(forward-strafe-rotation),vex::velocityUnits::rpm);
    leftfront.spin(vex::directionType::fwd,  2*(-rotation-forward+strafe),vex::velocityUnits::rpm);
  }
}
void hardcode(bool debug=true){
  mecanum_move(10, 0, 0,true);
  mecanum_move(0, 3, 0,true);
  mecanum_move(5, -4, 0,true);
  mecanum_move(15,0,0,true);
  mecanum_move(5,3,0,true);
}
int drivecolorpid(int colorin, int x, int width, bool debug=false){// 0 is not done  -1 is no cube in sight 1 is cube in correct pos
  if(debug){
    printf("color %i |",colorin);
    printf("x: %i |",x);
    printf("width setting: %i |",width);
  }
  int fwd = 0;//init vars to number
    //int sts = 0;
    int rtn = 0;
  visionsensor.takeSnapshot(colorin);//record pic  1is purple 2 is orange 3 is green
        //Brain.Screen.clearScreen();//make the screen blank
        //Brain.Screen.print("width:");//print line1                          "width:"
        //Brain.Screen.print(visionsensor.largestObject.width);//print line2  "###"
        //Brain.Screen.print("center X:");//print  line3                      "center X:"
        //Brain.Screen.print(visionsensor.largestObject.centerX);//print line4"###
  if (visionsensor.largestObject.exists && visionsensor.largestObject.width>5) {
    if(debug){
      printf("object exists wid>5 |");
    }
          //if the biggest object is bigger and 5 pixels wide
    rtn= (visionsensor.largestObject.centerX/visionsensor.largestObject.height)-x;//turn the ammount off center
    if(debug){
      printf("rtn %i |",rtn);
    }
    fwd=50; //3000/visionsensor.largestObject.width;//do this move fwd inverse propotionaly to the size
    if(debug){
      printf("width : %i x: %i |",visionsensor.largestObject.width,x);
    }
    if(visionsensor.largestObject.height>width){//and if fwd speed if less that 30%
      if(rtn<5){
        return 1;
      }
        fwd=0;// just dont move
      }
    mecanum_move(fwd,rtn,0);
        // Allow other tasks to run
        //this_thread::sleep_for(10);
  }else{
    if(debug){
      printf("largest size too small %i at x= %i |",visionsensor.largestObject.width, visionsensor.largestObject.centerX);
    }
    return-1;
  }
  return 0;
}


void autonomous( void ) {//this runs without human interaction
  int state = -1;
  
  //init motors and sensors to ports=================================
  //vex::controller controller1 = vex::controller();// this code does nothing
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  while(true){//loop forever
    printf("state: %i |", state);
    //int fwd = 0;//init vars to number
    //int sts = 0;
    //int rtn = 50;
    Brain.Screen.clearScreen();//make the screen blank
        Brain.Screen.print("state:");//print line1                          "width:"
        Brain.Screen.print(state);//print line2  "###"
    hardcode();
    switch(state){// for class
      case -1:{
        hardcode();
      break;
      }
      case 0: { // the orange sec before the white
        //visionsensor.takeSnapshot(3);//record pic  1is purple 2 is orange 3 is green
        //Brain.Screen.clearScreen();//make the screen blank
        //Brain.Screen.print("width:");//print line1                          "width:"
        //Brain.Screen.print(visionsensor.largestObject.width);//print line2  "###"
        //Brain.Screen.print("center X:");//print  line3                      "center X:"
        //Brain.Screen.print(visionsensor.largestObject.centerX);//print line4"###
        int dcp=drivecolorpid(2,250,150,true);
        printf("dcp: %i |", dcp);

        if(dcp==-1){
          Brain.Screen.print("no cube in sight");
        }else{
          if(dcp==1){
            //state=1;//1
          }
        }
        break;//0
      }
      case 1: { //white straight away
        int dcp=drivecolorpid(1,250,100);
        if(dcp==-1){
          Brain.Screen.print("no cube in sight");
        }else{
          if(dcp==1){
            state=7;//1
          }
        }
        
      
        // Allow other tasks to run
        //this_thread::sleep_for(10);
        
        break;//1
      }
      case 2: {// the 2nd orange section with the purple heading towards the green
      break;//2
      }
      case 3: {// the green section before the pickup
      break;//3
      }
      case 4: {// the pickup
      break; //4
      }
      case 5: {// backing up
      break;//5
      }
      case 6: {// lineing up for the white
      break;//6
      }
      case 7: {//final turn
      break;//7
      }

    }//end switch case*/
    
    //move acording to the vars set up earlier the 2*val if the convert from pct to rpm
    //rightrear.spin(vex::directionType::fwd,  2*(fwd+sts-rtn),vex::velocityUnits::rpm);
    //leftrear.spin(vex::directionType::fwd,   2*(-rtn-sts-fwd),vex::velocityUnits::rpm);
    //rightfront.spin(vex::directionType::fwd, 2*(fwd-sts-rtn),vex::velocityUnits::rpm);
    //sleftfront.spin(vex::directionType::fwd,  2*(-rtn-fwd+sts),vex::velocityUnits::rpm);
    printf("\n   ");

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
 //init motors and sensors to ports
  vex::motor rightrear (vex::PORT10, vex::gearSetting::ratio18_1, true);
  vex::motor leftrear (vex::PORT9, vex::gearSetting::ratio18_1, true);
  vex::motor leftfront (vex::PORT7, vex::gearSetting::ratio18_1, true);
  vex::motor rightfront (vex::PORT8, vex::gearSetting::ratio18_1, true);
  vex::motor lift (vex::PORT18, vex::gearSetting::ratio18_1, true);
  vex::motor tilt (vex::PORT19, vex::gearSetting::ratio18_1, true);
  vex::motor lefttread (vex::PORT17, vex::gearSetting::ratio18_1, true);
  vex::motor righttread (vex::PORT6, vex::gearSetting::ratio18_1, true);
 // vex::motor tipper (vex::PORT19, vex::gearSetting::ratio18_1, true);
  // User control code here, inside the loop
  while (1) {
    printf("%s","driveing");
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
    //bool l1=;
    //bool l2=;
    if(controller1.ButtonL1.pressing()&&(tilt.rotation(vex::rotationUnits::deg)<=maxtilt)){
      tilt.spin(vex::directionType::fwd, 50, vex::velocityUnits::rpm);
    }else{
      if(controller1.ButtonL2.pressing()&&(tilt.rotation(vex::rotationUnits::deg)>=mintilt)){
        tilt.spin(vex::directionType::fwd, -50, vex::velocityUnits::rpm);
      }else{
        tilt.spin(vex::directionType::fwd, 0, vex::velocityUnits::rpm);
        tilt.stop(vex::brakeType::brake);
      }
    }
    //bool r1=controller1.ButtonR1.pressing();
    //bool r2=controller1.ButtonR2.pressing();
    if(controller1.ButtonR2.pressing()){
      lift.spin(vex::directionType::fwd, 100, vex::velocityUnits::rpm);
    }else{
      if(controller1.ButtonR1.pressing()){
        lift.spin(vex::directionType::fwd, -100, vex::velocityUnits::rpm);
      }else{
        lift.spin(vex::directionType::fwd, 0, vex::velocityUnits::rpm);
        lift.stop(vex::brakeType::hold);
      }
    }
    if(controller1.ButtonA.pressing()){
      righttread.spin(vex::directionType::fwd, 100, vex::velocityUnits::rpm);
      lefttread.spin(vex::directionType::fwd, -100, vex::velocityUnits::rpm);
    }else{
      if(controller1.ButtonB.pressing()){
        righttread.spin(vex::directionType::fwd, -100, vex::velocityUnits::rpm);
        lefttread.spin(vex::directionType::fwd, 100, vex::velocityUnits::rpm);
      }else{
        righttread.spin(vex::directionType::fwd, 0, vex::velocityUnits::rpm);
        lefttread.spin(vex::directionType::fwd, 0, vex::velocityUnits::rpm);
        lefttread.stop(vex::brakeType::hold);
        righttread.stop(vex::brakeType::hold);
      }
    }
    rightrear.spin(vex::directionType::fwd,  2*(fwd+sts+rtn),vex::velocityUnits::rpm);
    leftrear.spin(vex::directionType::fwd,   2*(rtn-sts-fwd),vex::velocityUnits::rpm);
    rightfront.spin(vex::directionType::fwd, 2*(fwd-sts+rtn),vex::velocityUnits::rpm);
    leftfront.spin(vex::directionType::fwd,  2*(rtn-fwd+sts),vex::velocityUnits::rpm);
    vex::task::sleep(10); //Sleep the task for a short amount of time to prevent wasted resources. 
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
      vex::task::sleep(10);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
      
} 


