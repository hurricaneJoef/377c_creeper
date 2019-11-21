// To complete the VEXcode V5 Text project upgrade process, please follow the
// steps below.
// 
// 1. You can use the Robot Configuration window to autoreate your V5 devices
//   - including any motors, sensors, 3-wire devices, and controllers.
// 
// 2. All previous code located in main.cpp has now been commented out. You
//   will need to migrate this code to the new "int main" structure created
//   below and keep in mind any new device names you may have set from the
//   Robot Configuration window. 
// 
// If you would like to go back to your original project, a complete backup
// of your original (pre-upgraded) project was created in a backup folder
// inside of this project's folder.

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "vex.h"
#include "blue.cpp"
using namespace vex;
vex::motor rightrear(vex::PORT10, vex::gearSetting::ratio18_1, true);
vex::motor leftrear(vex::PORT9, vex::gearSetting::ratio18_1, true);
vex::motor leftfront(vex::PORT7, vex::gearSetting::ratio18_1, true);
vex::motor rightfront(vex::PORT8, vex::gearSetting::ratio18_1, true);
vex::motor lift(vex::PORT18, vex::gearSetting::ratio18_1, true);
vex::motor tilt(vex::PORT19, vex::gearSetting::ratio18_1, true);
vex::motor lefttread(vex::PORT17, vex::gearSetting::ratio18_1, true);
vex::motor righttread(vex::PORT6, vex::gearSetting::ratio18_1, true);
vex::vision visionsensor(vex::PORT20);
vex::controller controller1 = vex::controller();










void mecanum_move(float forward, float rotation, float strafe, bool dist=false, float velocitymult= 30){
  if(dist){
    rightrear.startRotateFor(vex::directionType::fwd,  (forward+strafe-rotation),vex::rotationUnits::rev,2*(forward+strafe-rotation)*velocitymult,vex::velocityUnits::rpm);
    leftrear.startRotateFor(vex::directionType::fwd,   (-rotation+strafe-forward),vex::rotationUnits::rev,2*(-rotation-strafe-forward)*velocitymult,vex::velocityUnits::rpm);
    rightfront.startRotateFor(vex::directionType::fwd, (forward-strafe-rotation),vex::rotationUnits::rev,2*(forward-strafe-rotation)*velocitymult,vex::velocityUnits::rpm);
    leftfront.rotateFor(vex::directionType::fwd,  (-rotation-forward-strafe),vex::rotationUnits::rev,2*(-rotation-forward+strafe)*velocitymult,vex::velocityUnits::rpm);
  }else{  
    rightrear.spin(vex::directionType::fwd,  2*(forward+strafe-rotation),vex::velocityUnits::rpm);
    leftrear.spin(vex::directionType::fwd,   2*(-rotation+strafe-forward),vex::velocityUnits::rpm);
    rightfront.spin(vex::directionType::fwd, 2*(forward-strafe-rotation),vex::velocityUnits::rpm);
    leftfront.spin(vex::directionType::fwd,  2*(-rotation+forward-strafe),vex::velocityUnits::rpm);
  }
}
void treadin(){
  righttread.spin(directionType::fwd, -100, vex::velocityUnits::rpm);
  lefttread.spin(directionType::fwd, 100, vex::velocityUnits::rpm);
}
void treadout(){
  righttread.spin(directionType::fwd, 100, vex::velocityUnits::rpm);
  lefttread.spin(directionType::fwd, -100, vex::velocityUnits::rpm);
}
void treadstop(){
  righttread.spin(directionType::fwd, 0, vex::velocityUnits::rpm);
  lefttread.spin(directionType::fwd, 0, vex::velocityUnits::rpm);
  lefttread.stop(vex::brakeType::hold);
  righttread.stop(vex::brakeType::hold);
}
void hardcode(){
  /*
  mecanum_move(-3,0,0,true);  
  mecanum_move(2,0,0,true);//*/
  //*
  rightrear.resetPosition();
  leftrear.resetPosition();
  rightfront.resetPosition();
  leftfront.resetPosition();
  tilt.resetPosition();
  lift.resetPosition();
  lift.stop(vex::brakeType::hold);
  tilt.rotateTo(-1, vex::rotationUnits::rev);
  tilt.rotateTo(0, vex::rotationUnits::rev);
  treadin();
  mecanum_move(1.5,0,0,true);
  treadstop();
  mecanum_move(0,-1.8,0,true);
  mecanum_move(2,0,0,true);
  treadin();
  mecanum_move(1,0,0,true);
  treadstop();
  mecanum_move(-1.5,0,0,true);
  mecanum_move(0,0,-3,true);
  //lift.resetPosition();
  //lift.rotateTo(-1,vex::rotationUnits::rev);
  mecanum_move(1,0,0,true);
  tilt.rotateTo(-1.8, vex::rotationUnits::rev);
  treadout();
  mecanum_move(-1.3, .1,0,true);
  treadstop();//*/
  
}

void playback(void) { // line num
printf("begining playback \n");
rightrear.resetPosition();
leftrear.resetPosition();
rightfront.resetPosition();
leftfront.resetPosition();
tilt.resetPosition();
lift.resetPosition();
float speedmult = 0;
float RevPerSec = .5;
//int speedadd=00;
printf("begining playback \n");
  for (int lin = 1; lin < legth; lin++) {
    printf("line %i |",lin);
    float max=0;
    int maxnum;
    for(int i=0;i<6;i++){
      if(max<fabs(auton[lin][i])){
        max=fabs(auton[lin][i]);
        maxnum=i;
      }
    }
    printf("max: %f |",max);
    speedmult=(max/RevPerSec);
    printf("speedmult: %f |",speedmult);
    if (lin==2||lin==4||lin==16) {
        righttread.spin(vex::directionType::fwd, -100, vex::velocityUnits::rpm);
        lefttread.spin(directionType::fwd, 100, vex::velocityUnits::rpm);
      } else {
        if (lin==6||lin==21) {
          righttread.spin(directionType::fwd, 100, vex::velocityUnits::rpm);
          lefttread.spin(directionType::fwd, -100, vex::velocityUnits::rpm);
        } else {
          righttread.spin(directionType::fwd, 0, vex::velocityUnits::rpm);
          lefttread.spin(directionType::fwd, 0, vex::velocityUnits::rpm);
          lefttread.stop(vex::brakeType::hold);
          righttread.stop(vex::brakeType::hold);
        }
      }
    rightrear.startRotateTo(auton[lin][0], vex::rotationUnits::rev,(auton[lin][0] - auton[lin - 1][0]) * speedmult,vex::velocityUnits::rpm);
    leftrear.startRotateTo(auton[lin][1], vex::rotationUnits::rev,(auton[lin][1] - auton[lin - 1][1]) * speedmult,vex::velocityUnits::rpm);
    rightfront.startRotateTo(auton[lin][2], vex::rotationUnits::rev,(auton[lin][2] - auton[lin - 1][2]) * speedmult,vex::velocityUnits::rpm);
    leftfront.startRotateTo(auton[lin][3], vex::rotationUnits::rev,(auton[lin][3] - auton[lin - 1][3]) * speedmult,vex::velocityUnits::rpm);
    tilt.startRotateTo(auton[lin][4], vex::rotationUnits::rev,(auton[lin][4] - auton[lin - 1][4]) * speedmult,vex::velocityUnits::rpm);
    lift.startRotateTo(auton[lin][5], vex::rotationUnits::rev,(auton[lin][5] - auton[lin - 1][5]) * speedmult,vex::velocityUnits::rpm);
    switch(maxnum){
      case 0:
      rightrear.rotateTo(auton[lin][0], vex::rotationUnits::rev,(auton[lin][0] - auton[lin - 1][0]) * speedmult,vex::velocityUnits::rpm);
      break;
      case 1:
      leftrear.rotateTo(auton[lin][1], vex::rotationUnits::rev,(auton[lin][1] - auton[lin - 1][1]) * speedmult,vex::velocityUnits::rpm);
      break;
      case 2:
      rightfront.rotateTo(auton[lin][2], vex::rotationUnits::rev,(auton[lin][2] - auton[lin - 1][2]) * speedmult,vex::velocityUnits::rpm);
      break;
      case 3:
      leftfront.rotateTo(auton[lin][3], vex::rotationUnits::rev,(auton[lin][3] - auton[lin - 1][3]) * speedmult,vex::velocityUnits::rpm);
      break;
      case 4:
      tilt.rotateTo(auton[lin][4], vex::rotationUnits::rev,(auton[lin][4] - auton[lin - 1][4]) * speedmult,vex::velocityUnits::rpm);
      break;
      case 5:
      lift.rotateTo(auton[lin][5], vex::rotationUnits::rev,(auton[lin][5] - auton[lin - 1][5]) * speedmult,vex::velocityUnits::rpm);
      break;
    }
    
    //printf("rightrear vel: %f |",(auton[lin][0] - auton[lin - 1][0]) * speedmult);
    printf(" waiting for input on up button \n");
    if(lin==19){
      righttread.startRotateFor(1,vex::rotationUnits::rev,100, vex::velocityUnits::rpm);
      lefttread.rotateFor(-1,vex::rotationUnits::rev, 100, vex::velocityUnits::rpm);
    }
    //while((controller1.ButtonUp.pressing())){
      
    //}
    //while((controller1.ButtonUp.pressing())){
      
    //}
    //printf(" done \n");
  }
  righttread.startRotateFor(-1,vex::rotationUnits::rev, 100, vex::velocityUnits::rpm);
  lefttread.rotateFor(1,vex::rotationUnits::rev, 100, vex::velocityUnits::rpm);
  printf("end of playback \n");

}
void pre_auton( void ) {//this runs before the auton
   
  // vex::motor rightrear (vex::PORT10, vex::gearSetting::ratio18_1, true);
   //vex::motor leftrear (vex::PORT9, vex::gearSetting::ratio18_1, true);
   //vex::motor leftfront (vex::PORT7, vex::gearSetting::ratio18_1, true);
   //vex::motor rightfront (vex::PORT8, vex::gearSetting::ratio18_1, true);
   // All activities that occur before the competition starts
//   // Example: clearing encoders, setting servo positions, ...
 }



// /*----------------------------------------------------------------------------*/
// /*                                                                            */
// /*    Module:       main.cpp                                                  */
// /*    Author:       C:\Users\hurri                                            */
// /*    Created:      Thu Aug 29 2019                                           */
// /*    Description:  V5 project                                                */
// /*                                                                            */
// /*----------------------------------------------------------------------------*/
// #include "vex.h"
// 
// // ---- START VEXCODE CONFIGURED DEVICES ----
// // Robot Configuration:
// // [Name]               [Type]        [Port(s)]
// // ---- END VEXCODE CONFIGURED DEVICES ----
 #include "vision.h"
// 
// using namespace vex;
// 
// // A global instance of vex::brain used for printing to the V5 brain screen
 //vex::brain       Brain;
 // A global instance of vex::competition
vex::competition Competition;
#define mintilt -530 //deg
#define maxtilt 0 //deg 
// // define your global instances of motors and other devices here
// 
// 
// /*---------------------------------------------------------------------------*/
// /*                          Pre-Autonautonomous Functions                         */
// /*                                                                           */
// /*  You may want to perform some actions before the competition starts.      */
// /*  Do them in the following function.  You must return from this function   */
// /*  or the autonomous and usercontrol tasks will not be started.  This       */
// /*  function is only called once after the cortex has been powered on and    */ 
// /*  not every time that the robot is disabled.                               */
// /*---------------------------------------------------------------------------*/
// 
 
// 
// /*---------------------------------------------------------------------------*/
// /*                                                                           */
// /*                              Autonautonomous Task                              */
// /*                                                                           */
// /*  This task is used to control your robot during the autonomous phase of   */
// /*  a VEX Competition.                                                       */
// /*                                                                           */
// /*  You must modify the code to add your own robot specific commands here.   */
// /*---------------------------------------------------------------------------*/
// 
void autonomous( void ) {//this runs without human interaction
  hardcode();
  //playback();
  /*
  //init motors and sensors to ports=================================
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
    visionsensor.takeSnapshot(1);//autoord pic
    int fwd = 0;//init vars to number
    int sts = 0;
     int rtn = 50;
     Brain.Screen.clearScreen();//make the screen blank
     Brain.Screen.print("width:");//print line1                          "width:"
     Brain.Screen.print(visionsensor.largestObject.width);//print line2  "###"
     Brain.Screen.print("center X:");//print  line3                      "center X:"
     Brain.Screen.print(visionsensor.largestObject.centerX);//print line4"###
     if (visionsensor.largestObject.exists && visionsensor.largestObject.width>5) {
       //if the biggest object is bigger and 5 pixels wide
       rtn= (visionsensor.largestObject.centerX/3)-53;//turn the ammount off center
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
       
        
     }//move acording to the vars set up earlier the 2*val if the convert from pct to rpm
     rightrear.spin(directionType::fwd,  2*(fwd+sts-rtn),vex::velocityUnits::rpm);
     leftrear.spin(directionType::fwd,   2*(-rtn-sts-fwd),vex::velocityUnits::rpm);
     rightfront.spin(directionType::fwd, 2*(fwd-sts-rtn),vex::velocityUnits::rpm);
     leftfront.spin(directionType::fwd,  2*(-rtn-fwd+sts),vex::velocityUnits::rpm);
     vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources.
   }//*/
 }
 
 /*---------------------------------------------------------------------------*/
 /*                                                                           */
// /*                              User Control Task                            */
// /*                                                                           */
// /*  This task is used to control your robot during the user control phase of */
// /*  a VEX Competition.                                                       */
// /*                                                                           */
// /*  You must modify the code to add your own robot specific commands here.   */
// /*---------------------------------------------------------------------------*/
// 
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
       tilt.spin(directionType::fwd, 200, vex::velocityUnits::rpm);
     }else{
       if(controller1.ButtonL2.pressing()&&(tilt.rotation(vex::rotationUnits::deg)>=mintilt)){
         tilt.spin(directionType::fwd, -200, vex::velocityUnits::rpm);
       }else{
         tilt.spin(directionType::fwd, 0, vex::velocityUnits::rpm);
         tilt.stop(vex::brakeType::brake);
       }
     }
     //bool r1=controller1.ButtonR1.pressing();
     //bool r2=controller1.ButtonR2.pressing();
     if(controller1.ButtonR2.pressing()){
       lift.spin(directionType::fwd, 200, vex::velocityUnits::rpm);
     }else{
       if(controller1.ButtonR1.pressing()){
         lift.spin(directionType::fwd, -200, vex::velocityUnits::rpm);
       }else{
         lift.spin(directionType::fwd, 0, vex::velocityUnits::rpm);
         lift.stop(vex::brakeType::hold);
       }
     }
     if(controller1.ButtonB.pressing()){
       righttread.spin(directionType::fwd, 100, vex::velocityUnits::rpm);
       lefttread.spin(directionType::fwd, -100, vex::velocityUnits::rpm);
     }else{
       if(controller1.ButtonA.pressing()){
        righttread.spin(directionType::fwd, -100, vex::velocityUnits::rpm);
         lefttread.spin(directionType::fwd, 100, vex::velocityUnits::rpm);
       }else{
         righttread.spin(directionType::fwd, 0, vex::velocityUnits::rpm);
         lefttread.spin(directionType::fwd, 0, vex::velocityUnits::rpm);
         lefttread.stop(vex::brakeType::hold);
         righttread.stop(vex::brakeType::hold);
       }
     }
     rightrear.spin(directionType::fwd,  2*(fwd+sts+rtn),vex::velocityUnits::rpm);
     leftrear.spin(directionType::fwd,   2*(rtn+sts-fwd),vex::velocityUnits::rpm);
     rightfront.spin(directionType::fwd, 2*(fwd-sts+rtn),vex::velocityUnits::rpm);
     leftfront.spin(directionType::fwd,  2*(rtn-fwd-sts),vex::velocityUnits::rpm);
     vex::task::sleep(10); //Sleep the task for a short amount of time to prevent wasted resources. 
   }
 }
 
 //
 // Main will set up the competition functions and callbacks.
 //
// int main() {
//     
//     //Set up callbacks for autonomous and driver control periods.
//     Competition.autonomous( autonomous );
//     Competition.drivercontrol( usercontrol );
//     
//     //Run the pre-autonomous function. 
//     pre_auton();
//        
//     //Prevent main from exiting with an infinite loop.                        
//     while(1) {
//       vex::task::sleep(10);//Sleep the task for a short amount of time to prevent wasted resources.
//     }    
//       
// } 

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  
  vexcodeInit();
  Competition.autonomous( autonomous );
  Competition.drivercontrol( usercontrol );
//     
//     //Run the pre-autonomous function. 
  pre_auton();
  
}