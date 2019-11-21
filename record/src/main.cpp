/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\hurri                                            */
/*    Created:      Mon Nov 04 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#define maxtilt 300 // deg
#define mintilt -1030   // deg
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
vex::controller::lcd disp =  vex::controller::lcd();
vex::brain::sdcard sd;
float rec[][7] =   
 {{ 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,0.0},
{ 2.582222, -2.490000, 2.520000, -2.506667, 0.000000, 0.000000,0.0},
{ 5.906667, 0.752222, -0.728889, -5.882222, 0.000000, 0.000000,0.0},
{ 3.040000, 3.541111, -3.528889, -3.097778, 0.000000, 0.000000,0.0},
{ 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,0}
};

//};
void playback() { // line num
rightrear.resetPosition();
leftrear.resetPosition();
rightfront.resetPosition();
leftfront.resetPosition();
tilt.resetPosition();
lift.resetPosition();
lefttread.resetPosition();
righttread.resetPosition();
float speedmult = 0;
float RevPerSec = 75;
//int speedadd=00;
printf("begining playback \n");
  for (int lin = 1; lin < (37-32); lin++) {
    printf("line %i |",lin);
    float max=0;
    int maxnum;
    for(int i=0;i<6;i++){
      if(max<fabs(rec[lin][i])){
        max=fabs(rec[lin][i]);
        maxnum=i;
      }
    }
    printf("max: %f |",max);
    speedmult=(max/RevPerSec);
    printf("speedmult: %f |",speedmult);
    /*if (lin==30||lin==70||lin==160) {
        righttread.spin(vex::directionType::fwd, -200, vex::velocityUnits::rpm);
        lefttread.spin(vex::directionType::fwd, 200, vex::velocityUnits::rpm);
      } else {
        if (lin==100||lin==210) {
          righttread.spin(vex::directionType::fwd, 200, vex::velocityUnits::rpm);
          lefttread.spin(vex::directionType::fwd, -200, vex::velocityUnits::rpm);
        } else {
          righttread.spin(vex::directionType::fwd, 0, vex::velocityUnits::rpm);
          lefttread.spin(vex::directionType::fwd, 0, vex::velocityUnits::rpm);
          lefttread.stop(vex::brakeType::hold);
          righttread.stop(vex::brakeType::hold);
        }
      }//*/
    rightrear.startRotateTo(rec[lin][0], vex::rotationUnits::rev,(rec[lin][0] - rec[lin - 1][0]) / speedmult,vex::velocityUnits::rpm);
    leftrear.startRotateTo(rec[lin][1], vex::rotationUnits::rev,(rec[lin][1] - rec[lin - 1][1]) / speedmult,vex::velocityUnits::rpm);
    rightfront.startRotateTo(rec[lin][2], vex::rotationUnits::rev,(rec[lin][2] - rec[lin - 1][2]) / speedmult,vex::velocityUnits::rpm);
    leftfront.startRotateTo(rec[lin][3], vex::rotationUnits::rev,(rec[lin][3] - rec[lin - 1][3]) / speedmult,vex::velocityUnits::rpm);
    tilt.startRotateTo(rec[lin][4], vex::rotationUnits::rev,(rec[lin][4] - rec[lin - 1][4]) / speedmult,vex::velocityUnits::rpm);
    lift.startRotateTo(rec[lin][5], vex::rotationUnits::rev,(rec[lin][5] - rec[lin - 1][5]) / speedmult,vex::velocityUnits::rpm);
    lefttread.startRotateTo(rec[lin][4], vex::rotationUnits::rev,(rec[lin][6] - rec[lin - 1][6]) / speedmult,vex::velocityUnits::rpm);
    righttread.startRotateTo(rec[lin][4], vex::rotationUnits::rev,(rec[lin][6] - rec[lin - 1][6]) / (-speedmult),vex::velocityUnits::rpm);
    switch(maxnum){
      case 0:
      rightrear.rotateTo(rec[lin][0], vex::rotationUnits::rev,(rec[lin][0] - rec[lin - 1][0]) / speedmult,vex::velocityUnits::rpm);
      break;
      case 1:
      leftrear.rotateTo(rec[lin][1], vex::rotationUnits::rev,(rec[lin][1] - rec[lin - 1][1]) / speedmult,vex::velocityUnits::rpm);
      break;
      case 2:
      rightfront.rotateTo(rec[lin][2], vex::rotationUnits::rev,(rec[lin][2] - rec[lin - 1][2]) / speedmult,vex::velocityUnits::rpm);
      break;
      case 3:
      leftfront.rotateTo(rec[lin][3], vex::rotationUnits::rev,(rec[lin][3] - rec[lin - 1][3]) / speedmult,vex::velocityUnits::rpm);
      break;
      case 4:
      tilt.rotateTo(rec[lin][4], vex::rotationUnits::rev,(rec[lin][4] - rec[lin - 1][4]) / speedmult,vex::velocityUnits::rpm);
      break;
      case 5:
      lift.rotateTo(rec[lin][5], vex::rotationUnits::rev,(rec[lin][5] - rec[lin - 1][5]) / speedmult,vex::velocityUnits::rpm);
      break;
      case 6:
      lefttread.startRotateTo(rec[lin][4], vex::rotationUnits::rev,(rec[lin][6] - rec[lin - 1][6]) / speedmult,vex::velocityUnits::rpm);
      righttread.rotateTo(rec[lin][4], vex::rotationUnits::rev,(rec[lin][6] - rec[lin - 1][6]) / (-speedmult),vex::velocityUnits::rpm);
      break;
    }
    
    //printf("rightrear vel: %f |",(rec[lin][0] - rec[lin - 1][0]) * speedmult);
    printf(" waiting for input on up button \n");
    if(lin==19){
      righttread.startRotateFor(1,vex::rotationUnits::rev,100, vex::velocityUnits::rpm);
      lefttread.rotateFor(-1,vex::rotationUnits::rev, 100, vex::velocityUnits::rpm);
    }
    while(!(controller1.ButtonUp.pressing())){
      
    }
    while((controller1.ButtonUp.pressing())){
      
    }
    //printf(" done \n");
  }
  righttread.startRotateFor(-1,vex::rotationUnits::rev, 100, vex::velocityUnits::rpm);
  lefttread.rotateFor(1,vex::rotationUnits::rev, 100, vex::velocityUnits::rpm);
  printf("end of playback \n");

}
void storevals(){
  printf("{ %f, %f, %f, %f, %f, %f, %f},\n",
             rightrear.rotation(vex::rotationUnits::rev),
             leftrear.rotation(vex::rotationUnits::rev),
             rightfront.rotation(vex::rotationUnits::rev),
             leftfront.rotation(vex::rotationUnits::rev),
             tilt.rotation(vex::rotationUnits::rev),
             lift.rotation(vex::rotationUnits::rev),
             lefttread.rotation(vex::rotationUnits::rev));
}
void printvals(){
  printf("{ %f, %f, %f, %f, %f, %f, %f},\n",
             rightrear.rotation(vex::rotationUnits::rev),
             leftrear.rotation(vex::rotationUnits::rev),
             rightfront.rotation(vex::rotationUnits::rev),
             leftfront.rotation(vex::rotationUnits::rev),
             tilt.rotation(vex::rotationUnits::rev),
             lift.rotation(vex::rotationUnits::rev),
             lefttread.rotation(vex::rotationUnits::rev));
}
void controlervals(){
  disp.clearLine();
  disp.print("%.2f %.2f \n %.2f %.2f",
             rightrear.rotation(vex::rotationUnits::rev),
             leftrear.rotation(vex::rotationUnits::rev),
             rightfront.rotation(vex::rotationUnits::rev),
             leftfront.rotation(vex::rotationUnits::rev));
}
void record() {
  rightrear.resetPosition();
  leftrear.resetPosition();
  rightfront.resetPosition();
  leftfront.resetPosition();
  tilt.resetPosition();
  lift.resetPosition();
  //bool prevX=false;
  while (true) {
  /*
  if(!prevX&&controller1.ButtonX.pressing()){
    prevX=true;
    printvals();
    
  }else if(!controller1.ButtonX.pressing()){
    prevX=false;
  }//*/
  controlervals();
      int fwd = controller1.Axis3.value();
      int sts = controller1.Axis4.value();
      int rtn = -controller1.Axis1.value();
      if (controller1.ButtonA.pressing() &&
          (tilt.rotation(vex::rotationUnits::deg) <= maxtilt)) {
        tilt.spin(vex::directionType::fwd, 200, vex::velocityUnits::rpm);
      } else {
        if (controller1.ButtonB.pressing() &&
            (tilt.rotation(vex::rotationUnits::deg) >= mintilt)) {
          tilt.spin(vex::directionType::fwd, -200, vex::velocityUnits::rpm);
        } else {
          tilt.spin(vex::directionType::fwd, 0, vex::velocityUnits::rpm);
          tilt.stop(vex::brakeType::brake);
        }
      }
      if (controller1.ButtonR2.pressing()) {
        lift.spin(vex::directionType::fwd, 200, vex::velocityUnits::rpm);
      } else {
        if (controller1.ButtonR1.pressing()) {
          lift.spin(vex::directionType::fwd, -200, vex::velocityUnits::rpm);
        } else {
          lift.spin(vex::directionType::fwd, 0, vex::velocityUnits::rpm);
          lift.stop(vex::brakeType::hold);
        }
      }
      if (controller1.ButtonL2.pressing()) {
        righttread.spin(vex::directionType::fwd, 200, vex::velocityUnits::rpm);
        lefttread.spin(vex::directionType::fwd, -200, vex::velocityUnits::rpm);
      } else {
        if (controller1.ButtonL1.pressing()) {
          righttread.spin(vex::directionType::fwd, -200,
                          vex::velocityUnits::rpm);
          lefttread.spin(vex::directionType::fwd, 200, vex::velocityUnits::rpm);
        } else {
          righttread.spin(vex::directionType::fwd, 0, vex::velocityUnits::rpm);
          lefttread.spin(vex::directionType::fwd, 0, vex::velocityUnits::rpm);
          lefttread.stop(vex::brakeType::hold);
          righttread.stop(vex::brakeType::hold);
        }
      }
      rightrear.spin(vex::directionType::fwd, 2 * (fwd + sts + rtn),
                     vex::velocityUnits::rpm);
      leftrear.spin(vex::directionType::fwd, 2 * (rtn + sts - fwd),
                    vex::velocityUnits::rpm);
      rightfront.spin(vex::directionType::fwd, 2 * (fwd - sts + rtn),
                      vex::velocityUnits::rpm);
      leftfront.spin(vex::directionType::fwd, 2 * (rtn - fwd - sts),
                     vex::velocityUnits::rpm);

      
      vex::task::sleep(25);
    }
  }

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while (1) {
    if (controller1.ButtonX.pressing()) {
      printf("recording "
             "\n========================================================== "
             "\n========================================================== "
             "\n {");
      record();
    }
    
    if (controller1.ButtonY.pressing()) {
      printf("begin playback \n");
      playback();
    }
  }
}
