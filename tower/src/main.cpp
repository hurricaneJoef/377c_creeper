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
vex::motor rightrear(vex::PORT20, vex::gearSetting::ratio18_1, true);
vex::motor leftrear(vex::PORT11, vex::gearSetting::ratio18_1, true);
vex::motor leftfront(vex::PORT12, vex::gearSetting::ratio18_1, true);
vex::motor rightfront(vex::PORT19, vex::gearSetting::ratio18_1, true);
vex::motor lift(vex::PORT14, vex::gearSetting::ratio18_1, true);
vex::motor tilt(vex::PORT15, vex::gearSetting::ratio18_1, true);
vex::motor lefttread(vex::PORT16, vex::gearSetting::ratio18_1, true);
vex::motor righttread(vex::PORT17, vex::gearSetting::ratio18_1, true);
vex::vision visionsensor(vex::PORT10);
vex::controller controller1 = vex::controller();
vex::controller::lcd disp = vex::controller::lcd();
vex::brain::lcd lcd = vex::brain::lcd();


bool blutrue = true;
int prog = 0;






void mecanum_move(float forward, float rotation, float strafe, bool dist=false, float velocitymult= 60){
  if (!blutrue){
    rotation= -1*rotation;
    strafe= -1*strafe;
  }
  if (!blutrue){
    rotation= -1*rotation;
    strafe= -1*strafe;
  }
  if(dist){
    float max=0;
    uint8_t maxnum;
    if(max<fabs(forward+strafe-rotation)){
      max=fabs(forward+strafe-rotation);
      maxnum=0;//right rear
    }
    if(max<fabs(-rotation+strafe-forward)){
      max=fabs(-rotation+strafe-forward);
      maxnum=1;//left rear
    }
    if(max<fabs(forward-strafe-rotation)){
      max=fabs(forward-strafe-rotation);
      maxnum=2;//right front
    }
    if(max<fabs(-rotation-forward-strafe)){
      max=fabs(-rotation-forward-strafe);
      maxnum=3;//left front
    }
    velocitymult=max/velocitymult;
    switch(maxnum){
      case 0:
      leftrear.rotateFor(vex::directionType::fwd,   (-rotation+strafe-forward),vex::rotationUnits::rev,2*(-rotation+strafe-forward)/velocitymult,vex::velocityUnits::rpm,false);
      rightfront.rotateFor(vex::directionType::fwd, (forward-strafe-rotation),vex::rotationUnits::rev,2*(forward-strafe-rotation)/velocitymult,vex::velocityUnits::rpm,false);
      leftfront.rotateFor(vex::directionType::fwd,  (-rotation-forward-strafe),vex::rotationUnits::rev,2*(-rotation-forward-strafe)/velocitymult,vex::velocityUnits::rpm,false);
      rightrear.rotateFor(vex::directionType::fwd,  (forward+strafe-rotation),vex::rotationUnits::rev,2*(forward+strafe-rotation)/velocitymult,vex::velocityUnits::rpm);
      break;
      case 1:
      rightrear.rotateFor(vex::directionType::fwd,  (forward+strafe-rotation),vex::rotationUnits::rev,2*(forward+strafe-rotation)/velocitymult,vex::velocityUnits::rpm,false);
      rightfront.rotateFor(vex::directionType::fwd, (forward-strafe-rotation),vex::rotationUnits::rev,2*(forward-strafe-rotation)/velocitymult,vex::velocityUnits::rpm,false);
      leftfront.rotateFor(vex::directionType::fwd,  (-rotation-forward-strafe),vex::rotationUnits::rev,2*(-rotation-forward-strafe)/velocitymult,vex::velocityUnits::rpm,false);
      leftrear.rotateFor(vex::directionType::fwd,   (-rotation+strafe-forward),vex::rotationUnits::rev,2*(-rotation+strafe-forward)/velocitymult,vex::velocityUnits::rpm);
      break;
      case 2:
      rightrear.rotateFor(vex::directionType::fwd,  (forward+strafe-rotation),vex::rotationUnits::rev,2*(forward+strafe-rotation)/velocitymult,vex::velocityUnits::rpm,false);
      leftrear.rotateFor(vex::directionType::fwd,   (-rotation+strafe-forward),vex::rotationUnits::rev,2*(-rotation+strafe-forward)/velocitymult,vex::velocityUnits::rpm,false);
      leftfront.rotateFor(vex::directionType::fwd,  (-rotation-forward-strafe),vex::rotationUnits::rev,2*(-rotation-forward-strafe)/velocitymult,vex::velocityUnits::rpm,false);
      rightfront.rotateFor(vex::directionType::fwd, (forward-strafe-rotation),vex::rotationUnits::rev,2*(forward-strafe-rotation)/velocitymult,vex::velocityUnits::rpm);
      break;
      case 3:
      rightrear.rotateFor(vex::directionType::fwd,  (forward+strafe-rotation),vex::rotationUnits::rev,2*(forward+strafe-rotation)/velocitymult,vex::velocityUnits::rpm,false);
      leftrear.rotateFor(vex::directionType::fwd,   (-rotation+strafe-forward),vex::rotationUnits::rev,2*(-rotation+strafe-forward)/velocitymult,vex::velocityUnits::rpm,false);
      rightfront.rotateFor(vex::directionType::fwd, (forward-strafe-rotation),vex::rotationUnits::rev,2*(forward-strafe-rotation)/velocitymult,vex::velocityUnits::rpm,false);
      leftfront.rotateFor(vex::directionType::fwd,  (-rotation-forward-strafe),vex::rotationUnits::rev,2*(-rotation-forward-strafe)/velocitymult,vex::velocityUnits::rpm);
      break;
    }
    
  }else{  
    rightrear.spin(vex::directionType::fwd,  2*(forward+strafe-rotation),vex::velocityUnits::rpm);
    leftrear.spin(vex::directionType::fwd,   2*(-rotation+strafe-forward),vex::velocityUnits::rpm);
    rightfront.spin(vex::directionType::fwd, 2*(forward-strafe-rotation),vex::velocityUnits::rpm);
    leftfront.spin(vex::directionType::fwd,  2*(-rotation+forward-strafe),vex::velocityUnits::rpm);
  }if (!blutrue){
    rotation= -1*rotation;
    strafe= -1*strafe;
  }
  if(dist){
    float max=0;
    uint8_t maxnum;
    if(max<fabs(forward+strafe-rotation)){
      max=fabs(forward+strafe-rotation);
      maxnum=0;//right rear
    }
    if(max<fabs(-rotation+strafe-forward)){
      max=fabs(-rotation+strafe-forward);
      maxnum=1;//left rear
    }
    if(max<fabs(forward-strafe-rotation)){
      max=fabs(forward-strafe-rotation);
      maxnum=2;//right front
    }
    if(max<fabs(-rotation-forward-strafe)){
      max=fabs(-rotation-forward-strafe);
      maxnum=3;//left front
    }
    velocitymult=max/velocitymult;
    switch(maxnum){
      case 0:
      leftrear.rotateFor(vex::directionType::fwd,   (-rotation+strafe-forward),vex::rotationUnits::rev,2*(-rotation+strafe-forward)/velocitymult,vex::velocityUnits::rpm,false);
      rightfront.rotateFor(vex::directionType::fwd, (forward-strafe-rotation),vex::rotationUnits::rev,2*(forward-strafe-rotation)/velocitymult,vex::velocityUnits::rpm,false);
      leftfront.rotateFor(vex::directionType::fwd,  (-rotation-forward-strafe),vex::rotationUnits::rev,2*(-rotation-forward-strafe)/velocitymult,vex::velocityUnits::rpm,false);
      rightrear.rotateFor(vex::directionType::fwd,  (forward+strafe-rotation),vex::rotationUnits::rev,2*(forward+strafe-rotation)/velocitymult,vex::velocityUnits::rpm);
      break;
      case 1:
      rightrear.rotateFor(vex::directionType::fwd,  (forward+strafe-rotation),vex::rotationUnits::rev,2*(forward+strafe-rotation)/velocitymult,vex::velocityUnits::rpm,false);
      rightfront.rotateFor(vex::directionType::fwd, (forward-strafe-rotation),vex::rotationUnits::rev,2*(forward-strafe-rotation)/velocitymult,vex::velocityUnits::rpm,false);
      leftfront.rotateFor(vex::directionType::fwd,  (-rotation-forward-strafe),vex::rotationUnits::rev,2*(-rotation-forward-strafe)/velocitymult,vex::velocityUnits::rpm,false);
      leftrear.rotateFor(vex::directionType::fwd,   (-rotation+strafe-forward),vex::rotationUnits::rev,2*(-rotation+strafe-forward)/velocitymult,vex::velocityUnits::rpm);
      break;
      case 2:
      rightrear.rotateFor(vex::directionType::fwd,  (forward+strafe-rotation),vex::rotationUnits::rev,2*(forward+strafe-rotation)/velocitymult,vex::velocityUnits::rpm,false);
      leftrear.rotateFor(vex::directionType::fwd,   (-rotation+strafe-forward),vex::rotationUnits::rev,2*(-rotation+strafe-forward)/velocitymult,vex::velocityUnits::rpm,false);
      leftfront.rotateFor(vex::directionType::fwd,  (-rotation-forward-strafe),vex::rotationUnits::rev,2*(-rotation-forward-strafe)/velocitymult,vex::velocityUnits::rpm,false);
      rightfront.rotateFor(vex::directionType::fwd, (forward-strafe-rotation),vex::rotationUnits::rev,2*(forward-strafe-rotation)/velocitymult,vex::velocityUnits::rpm);
      break;
      case 3:
      rightrear.rotateFor(vex::directionType::fwd,  (forward+strafe-rotation),vex::rotationUnits::rev,2*(forward+strafe-rotation)/velocitymult,vex::velocityUnits::rpm,false);
      leftrear.rotateFor(vex::directionType::fwd,   (-rotation+strafe-forward),vex::rotationUnits::rev,2*(-rotation+strafe-forward)/velocitymult,vex::velocityUnits::rpm,false);
      rightfront.rotateFor(vex::directionType::fwd, (forward-strafe-rotation),vex::rotationUnits::rev,2*(forward-strafe-rotation)/velocitymult,vex::velocityUnits::rpm,false);
      leftfront.rotateFor(vex::directionType::fwd,  (-rotation-forward-strafe),vex::rotationUnits::rev,2*(-rotation-forward-strafe)/velocitymult,vex::velocityUnits::rpm);
      break;
    }
    
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
void onepoint(){
  mecanum_move(-3,0,0,true);  
  mecanum_move(2,0,0,true);//*/
  //*
}
void threetower(){
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
  mecanum_move(.5,0,0,true);
  treadstop();
  mecanum_move(1,0,0,true);
  mecanum_move(0,1.8,0,true);
  mecanum_move(2,0,0,true);
  treadin();
  mecanum_move(1,0,0,true);
  treadstop();
  mecanum_move(-1.5,0,0,true);
  mecanum_move(0,0,3,true);
  //lift.resetPosition();
  //lift.rotateTo(-1,vex::rotationUnits::rev);
  mecanum_move(1,0,0,true);
  tilt.rotateTo(-1.8, vex::rotationUnits::rev);
  treadout();
  mecanum_move(-1.3, -.1,0,true);
  treadstop();//*/
  
}
void auto8(){

}
void auto9(){

}
void wait4but(){
  while(
   !(controller1.ButtonA.pressing()||
   controller1.ButtonB.pressing()||
   controller1.ButtonX.pressing()||
   controller1.ButtonY.pressing()||
  controller1.ButtonL1.pressing()||
  controller1.ButtonL2.pressing()||
  controller1.ButtonR1.pressing()||
  controller1.ButtonR2.pressing()||
  controller1.ButtonLeft.pressing()||
  controller1.ButtonRight.pressing()||
  controller1.ButtonUp.pressing()||
  controller1.ButtonDown.pressing()
  )){

  }
  while(
   (controller1.ButtonA.pressing()||
   controller1.ButtonB.pressing()||
   controller1.ButtonX.pressing()||
   controller1.ButtonY.pressing()||
  controller1.ButtonL1.pressing()||
  controller1.ButtonL2.pressing()||
  controller1.ButtonR1.pressing()||
  controller1.ButtonR2.pressing()||
  controller1.ButtonLeft.pressing()||
  controller1.ButtonRight.pressing()||
  controller1.ButtonUp.pressing()||
  controller1.ButtonDown.pressing()
  )){

  }
  
}
void onestackonetower(){
  rightrear.resetPosition();
  leftrear.resetPosition();
  rightfront.resetPosition();
  leftfront.resetPosition();
  tilt.resetPosition();
  lift.resetPosition();
  lift.stop(vex::brakeType::hold);
  tilt.rotateTo(-1, vex::rotationUnits::rev);
  tilt.rotateTo(0, vex::rotationUnits::rev);
  lift.startRotateTo(-.5, vex::rotationUnits::rev);
  treadin();
  mecanum_move(.7,0,0,true,20);
  //vex::task::sleep(1000);
  //treadin();
  vex::task::sleep(50);
  
  mecanum_move(-.4,0,0,true);
  treadstop();
  //treadstop();
  vex::task::sleep(100);
  lift.startRotateTo(-3.9,vex::rotationUnits::rev);
  mecanum_move(0.2,0,2.5,true);
  vex::task::sleep(100);
  mecanum_move(0,0,-2.4,true);
  vex::task::sleep(100);
  mecanum_move(1.2,0,0,true);
  vex::task::sleep(100);
  mecanum_move(0,-1.8,0,true);
  //vex::task::sleep(500);
  //lift.resetPosition();
  //lift.rotateTo(-1,vex::rotationUnits::rev);
  //mecanum_move(1,0,0,true);
  //vex::task::sleep(5000);
  //tilt.rotateTo(-1.8, vex::rotationUnits::rev);
  treadout();
 
  vex::task::sleep(1000);
  treadstop();
  mecanum_move(-2.8,0,0,true);
  vex::task::sleep(100);
  mecanum_move(.3,0,0,true);
  vex::task::sleep(100);
  mecanum_move(0,0,1.8,true);
  vex::task::sleep(100);
  mecanum_move(-.4,0,0,true);
  vex::task::sleep(100);
  mecanum_move(0,0,-2.5,true,100);
  //vex::task::sleep(100);
  mecanum_move(0,0,2,true,100);
}
void playback(void){ // line num
  printf("begining playback \n");
  rightrear.resetPosition();
  leftrear.resetPosition();
  rightfront.resetPosition();
  leftfront.resetPosition();
  tilt.resetPosition();
  lift.resetPosition();
  float secs = 0;
  float RevPerSec = 200;
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
    secs=(max/RevPerSec);
    printf("secs: %f |",secs);
    if (lin==2||lin==4||lin==16) {
        righttread.spin(vex::directionType::fwd, -200, vex::velocityUnits::rpm);
        lefttread.spin(directionType::fwd, 200, vex::velocityUnits::rpm);
      } else {
        if (lin==6||lin==21) {
          righttread.spin(directionType::fwd, 200, vex::velocityUnits::rpm);
          lefttread.spin(directionType::fwd, -200, vex::velocityUnits::rpm);
        } else {
          righttread.spin(directionType::fwd, 0, vex::velocityUnits::rpm);
          lefttread.spin(directionType::fwd, 0, vex::velocityUnits::rpm);
          lefttread.stop(vex::brakeType::hold);
          righttread.stop(vex::brakeType::hold);
        }
      }
    rightrear.startRotateTo(auton[lin][0], vex::rotationUnits::rev,(auton[lin][0] - auton[lin - 1][0]) / secs,vex::velocityUnits::rpm);
    leftrear.startRotateTo(auton[lin][1], vex::rotationUnits::rev,(auton[lin][1] - auton[lin - 1][1]) / secs,vex::velocityUnits::rpm);
    rightfront.startRotateTo(auton[lin][2], vex::rotationUnits::rev,(auton[lin][2] - auton[lin - 1][2]) / secs,vex::velocityUnits::rpm);
    leftfront.startRotateTo(auton[lin][3], vex::rotationUnits::rev,(auton[lin][3] - auton[lin - 1][3]) / secs,vex::velocityUnits::rpm);
    tilt.startRotateTo(auton[lin][4], vex::rotationUnits::rev,(auton[lin][4] - auton[lin - 1][4]) / secs,vex::velocityUnits::rpm);
    lift.startRotateTo(auton[lin][5], vex::rotationUnits::rev,(auton[lin][5] - auton[lin - 1][5]) / secs,vex::velocityUnits::rpm);
    switch(maxnum){
      case 0:
      rightrear.rotateTo(auton[lin][0], vex::rotationUnits::rev,(auton[lin][0] - auton[lin - 1][0]) * secs,vex::velocityUnits::rpm);
      break;
      case 1:
      leftrear.rotateTo(auton[lin][1], vex::rotationUnits::rev,(auton[lin][1] - auton[lin - 1][1]) * secs,vex::velocityUnits::rpm);
      break;
      case 2:
      rightfront.rotateTo(auton[lin][2], vex::rotationUnits::rev,(auton[lin][2] - auton[lin - 1][2]) * secs,vex::velocityUnits::rpm);
      break;
      case 3:
      leftfront.rotateTo(auton[lin][3], vex::rotationUnits::rev,(auton[lin][3] - auton[lin - 1][3]) * secs,vex::velocityUnits::rpm);
      break;
      case 4:
      tilt.rotateTo(auton[lin][4], vex::rotationUnits::rev,(auton[lin][4] - auton[lin - 1][4]) * secs,vex::velocityUnits::rpm);
      break;
      case 5:
      lift.rotateTo(auton[lin][5], vex::rotationUnits::rev,(auton[lin][5] - auton[lin - 1][5]) * secs,vex::velocityUnits::rpm);
      break;
    }
    
    //printf("rightrear vel: %f |",(auton[lin][0] - auton[lin - 1][0]) * secs);
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
void showchoice(int choice){
  int mult=0;
  color cube;
  color tile;
  if(blutrue){
    mult=1;
    cube = green;
    tile=color(30,123,80);
  }else{
    mult=-1;
    cube =orange;
    tile=color(196,33,52);
  }
  //disp.setCursor(0,0);
  //disp.clearScreen();
  lcd.clearScreen();
  if(blutrue){
        lcd.drawImageFromFile("bluefield.png",0,0);
      }else{
        lcd.drawImageFromFile("redfield.png",0,0);
      }
  switch(choice){
    case 2:
      lcd.drawImageFromFile("robotup.png",  210 + (mult*90),160);//three stack pos
      lcd.drawRectangle((240-10) + (mult*(220)),200,20,20,cube);
      lcd.drawRectangle((240-10) + (mult*(80)),140,20,20,color(131,131,131));
      lcd.drawRectangle((240-10) + (mult*(160)),140,20,20,tile);
      lcd.printAt((240-10) + (mult*(160)),200,false,"3 G \n0 O \n0 P ");
      lcd.printAt(240,220,"place preload in tread");
    break;
    case 3:
      
      lcd.drawImageFromFile("robotup.png",  210 + (mult*90),160);//two stack one tower pos
      lcd.drawRectangle((240-10) + (mult*(220)),180,20,40,cube);
      lcd.drawRectangle(230, 150, 20, 20, cube);
      lcd.drawRectangle((240-10) + (mult*(80)),140,20,20,color(131,131,131));
      lcd.drawRectangle((240-10) + (mult*(160)),140,20,20,tile);
      lcd.printAt((240-10) + (mult*(160)),180,false,"2 G \n0 O \n0 P ");
      lcd.printAt(20,20,"place preload to side of robot toward prot zone");
    break;
    case 8:
      
      lcd.drawImageFromFile("robotup.png",  210 + (mult*90),160);//two stack one tower pos
      lcd.drawRectangle((240-10) + (mult*(220)),180,20,40,cube);
      lcd.drawRectangle(230, 150, 20, 20, cube);
      lcd.drawRectangle((240-10) + (mult*(80)),140,20,20,color(131,131,131));
      lcd.drawRectangle((240-10) + (mult*(160)),140,20,20,tile);
      lcd.printAt((240-10) + (mult*(160)),180,false,"2 G \n0 O \n0 P ");
      lcd.printAt(20,20,"place preload to side of robot toward prot zone");
    break;
    case 9:
      
      lcd.drawImageFromFile("robotup.png",  210 + (mult*90),160);//two stack one tower pos
      lcd.drawRectangle((240-10) + (mult*(220)),180,20,40,cube);
      lcd.drawRectangle(230, 150, 20, 20, cube);
      lcd.drawRectangle((240-10) + (mult*(80)),140,20,20,color(131,131,131));
      lcd.drawRectangle((240-10) + (mult*(160)),140,20,20,tile);
      lcd.printAt((240-10) + (mult*(160)),180,false,"2 G \n0 O \n0 P ");
      lcd.printAt(20,20,"place preload to side of robot toward prot zone");
    break;
    case 10:
      
      lcd.drawImageFromFile("robotup.png",  210 + (mult*90),160);//two stack one tower pos
      lcd.drawRectangle((240-10) + (mult*(220)),180,20,40,cube);
      lcd.drawRectangle(230, 150, 20, 20, cube);
      lcd.drawRectangle((240-10) + (mult*(80)),140,20,20,color(131,131,131));
      lcd.drawRectangle((240-10) + (mult*(160)),140,20,20,tile);
      lcd.printAt((240-10) + (mult*(160)),180,false,"2 G \n0 O \n0 P ");
      lcd.printAt(20,20,"place preload to side of robot toward prot zone");
    break;
    default:
      lcd.drawImageFromFile("robotleft.png",  210 + (mult*80),180);//3g stack
      lcd.drawRectangle((240-10) + (mult*(120)),200,20,20,cube);
      lcd.drawImageFromFile("robotright.png",  210 + (mult*90),160);//3g stack
      lcd.drawRectangle((240-10) + (mult*(120)),200,20,20,cube);
    
      //disp.setCursor(2,0);
      //disp.print("READY TO");
      //disp.setCursor(3,0);
      //disp.print("BEGIN MATCH");
      //Brain.Screen.print("place robot in with rear facing scoring zone\n and less than 8 in away \nand place cube between robot and zone");
    break;
  }
  
   
}
bool pressing(int x, int y,int width,int height){
  return(lcd.pressing()&&(lcd.xPosition()>x)&&(lcd.xPosition()<x+width)&&(lcd.yPosition()>y)&&(lcd.yPosition()<y+width));
}
void pos1(){//this position is the one near the team colored tiles
  int mult=0;
  color cube;
  color side;
  int selected =1;
  resetpos1:
  if(blutrue){
    cube=green;
    side=blue;
    mult=1;
  }else{
    cube=orange;
    side=red;
    mult=-1;
  }
  showchoice(selected);
  // robot.png is 80x60
      
      lcd.drawRectangle(200-200*mult,0,80,240,black);
      switch(selected){
        case 2:
        lcd.drawRectangle(200-200*mult,80,80,80,side);
        break;
        case 3:
        lcd.drawRectangle(200-200*mult,160,80,80,side);
        break;
        default:
        lcd.drawRectangle(200-200*mult,0,80,80,side);
        break;
      }
      lcd.setPenColor(white);
      lcd.drawLine(200-200*mult,80,280-200*mult,80);
      lcd.drawLine(200-200*mult,160,280-200*mult,160);
      /*
          Stacks towers1
      Green  1    0
      Orange 0    0
      Purple 0    0
      _________________
          Stacks towers2
      Green  3    0
      Orange 0    0
      Purple 0    0
      _________________
          Stacks towers3
      Green  2    1
      Orange 0    0
      Purple 0    0
      _________________*/
      lcd.printAt(210-200*mult,10,false, "      Stacks towers\nGreen  %i    %i\nOrange %i    %i\nPurple %i    %i",blutrue*1,0,1-blutrue*1,0,0,0);
      lcd.printAt(210-200*mult,90,false, "      Stacks towers\nGreen  %i    %i\nOrange %i    %i\nPurple %i    %i",blutrue*3,0,3-blutrue*3,0,0,0);
      lcd.printAt(210-200*mult,170,false,"      Stacks towers\nGreen  %i    %i\nOrange %i    %i\nPurple %i    %i",blutrue*2,blutrue*1,2-blutrue*2,1-blutrue*1,0,0);
      
      while(true){
        if(pressing(200-200*mult,0,80,80)){
          prog=1;
          selected=1;
          goto resetpos1;
        }else if(pressing(200-200*mult,80,80,80)){
          prog=2;
          selected=2;
          goto resetpos1;
        }else if(pressing(200-200*mult,160,80,80)){
          prog=3;
          selected=3;
          goto resetpos1;
        }
      }
}
void pos2(){
  int mult=0;
  color cube;
  color side;
  int selected=1;
  resetpos2:
  if(blutrue){
    cube=green;
    side=blue;
    mult=1;
  }else{
    cube=orange;
    side=red;
    mult=-1;
  }
  showchoice(selected);
  // robot.png is 80x60
      
      lcd.drawRectangle(200+200*mult,0,80,240,black);
      switch(selected){
        case 8:
        lcd.drawRectangle(200+200*mult,80,80,80,side);
        break;
        case 9:
        lcd.drawRectangle(200+200*mult,160,80,80,side);
        break;
        default:
        lcd.drawRectangle(200+200*mult,0,80,80,side);
        break;
      }
      lcd.setPenColor(white);
      lcd.drawLine(200+200*mult,80,280+200*mult,80);
      lcd.drawLine(200+200*mult,160,280+200*mult,160);
  
      /*
          Stacks towers  1
      Green  1    0
      Orange 0    0
      Purple 0    0
      _________________
          Stacks towers  8
      Green  2    0
      Orange 2    0
      Purple 1    0
      _________________
          Stacks towers  9
      Green  1    1
      Orange 2    0
      Purple 1    0
      _________________*/
      lcd.printAt(210+200*mult,10,false, "      Stacks towers\nGreen  %i    %i\nOrange %i    %i\nPurple %i    %i",blutrue*1,0,1-blutrue*1,0,0,0);
      lcd.printAt(210+200*mult,90,false, "      Stacks towers\nGreen  %i    %i\nOrange %i    %i\nPurple %i    %i",2,0,2,0,1,0);
      lcd.printAt(210+200*mult,170,false,"      Stacks towers\nGreen  %i    %i\nOrange %i    %i\nPurple %i    %i",2-blutrue*1,blutrue*1,1+blutrue*1,1-blutrue*1,0,0);
      while(true){
        if(pressing(200+200*mult,0,80,80)){
          prog=1;
          selected=1;
          goto resetpos2;
        }else if(pressing(200+200*mult,80,80,80)){
          prog=8;
          selected=8;
          goto resetpos2;
        }else if(pressing(200+200*mult,160,80,80)){
          prog=9;
          selected=9;
          goto resetpos2;
        }
      }
}
void autonselect(){
  int mult=0;
  color cube;
  if(blutrue){
    mult=1;
    cube = green;
  }else{
    mult=-1;
    cube =orange;
  }
  //lcd.drawImageFromFile("back.png",0,0);
  if(blutrue){
    lcd.drawImageFromFile("bluefield.png",0,0);
  }else{
    lcd.drawImageFromFile("redfield.png",0,0);
  }
  // robot.png is 80x60
      lcd.drawImageFromFile("robotup.png",  210 - (mult*150),160);//5 stack
      lcd.drawRectangle((240-10) - (mult*150),160,20,20,cube);

      lcd.drawImageFromFile("robotup.png",  210 + (mult*90),160);//two stack one tower
      lcd.drawRectangle((240-10) + (mult*(120)),200,20,20,cube);
  while(true){
    if(pressing(200 + (mult*90),160,80,80)){
      showchoice(2);
    }
    if(!(prog==0)){
      showchoice(prog);
    }else{
      disp.setCursor(1,0);
      disp.clearLine();
      
      disp.print("down for safe 1pt");
        disp.setCursor(2,0);
        disp.print("left for 3s 3pt");
        disp.setCursor(3,0);
        disp.print("right for 1t1s 2pt");
      if(controller1.ButtonDown.pressing()){
        prog=-1;
      }else if(controller1.ButtonLeft.pressing()){
        while(controller1.ButtonLeft.pressing()){

        }
        prog=1;
      }else if(controller1.ButtonRight.pressing()){
        while(controller1.ButtonRight.pressing()){
        
        }
        prog=2;
      }
      
      vex::task::sleep(125);
    }
  }
}
double temp[8]={0,0,0,0,0,0,0,0};
void gettemp(){
  temp[0]=(rightrear.temperature(vex::temperatureUnits::celsius) - 20) / 50 * 100;
  temp[1]=(rightfront.temperature(vex::temperatureUnits::celsius) - 20) / 50 * 100;
  temp[2]=(leftrear.temperature(vex::temperatureUnits::celsius) - 20) / 50 * 100;
  temp[3]=(leftfront.temperature(vex::temperatureUnits::celsius) - 20) / 50 * 100;
  temp[4]=(righttread.temperature(vex::temperatureUnits::celsius) - 20) / 50 * 100;
  temp[5]=(lefttread.temperature(vex::temperatureUnits::celsius) - 20) / 50 * 100;
  temp[6]=(lift.temperature(vex::temperatureUnits::celsius) - 20) / 50 * 100;
  temp[7]=(tilt.temperature(vex::temperatureUnits::celsius) - 20) / 50 * 100;
}
void tempc(){
  disp.setCursor(1,0);
  disp.clearScreen();
  gettemp();
  int maxtemppct=75;
  while((temp[0]>maxtemppct)||(temp[1]>maxtemppct)||(temp[2]>maxtemppct)||(temp[3]>maxtemppct)||(temp[4]>maxtemppct)||(temp[5]>maxtemppct)||(temp[6]>maxtemppct)||(temp[7]>maxtemppct)){
  gettemp();
    disp.print("MOTOR OVERTEMP");
    disp.setCursor(2,0);
    uint8_t mmt=0;
    for(int i=0;i<8;i++){
      if(temp[i]>temp[mmt]){
        mmt=i;
      }
    }
    switch(mmt){
        case 0:
        disp.print("RIGHT REAR");
        break;
        case 1:
        disp.print("RIGHT FRONT");
        break;
        case 2:
        disp.print("LEFT REAR");
        break;
        case 3:
        disp.print("LEFT FRONT");
        break;
        case 5:
        disp.print("LEFT TREAD");
        break;
        case 4:
        disp.print("RIGHT TREAD");
        break;
        case 6:
        disp.print("LIFT MOTOR");
        break;
        case 7:
        disp.print("TILT MOTOR");
        break;
      }
    disp.setCursor(3,0);
    disp.print("AT %3f DEG C",((temp[mmt])/100*50)+20);
  }
}
void pre_auton( void ) {//this runs before the auton
  disp.setCursor(1,0);
  disp.clearScreen();
  lcd.drawRectangle(000,0,240,240,red );
  lcd.drawRectangle(240,0,240,240,blue);
  disp.print("left blue");
      disp.setCursor(2,0);
      disp.print("right red");
      disp.setCursor(3,0);
      disp.print("leave for reverse");
  while(true){
    disp.print("1");
    printf("xpos %long pressing %i",lcd.xPosition(),lcd.pressing());
    if(controller1.ButtonRight.pressing()||(lcd.pressing()&&(lcd.xPosition()<240))){
      disp.clearScreen();
      lcd.clearScreen(red);
      while(controller1.ButtonRight.pressing()||lcd.pressing()){
       
      }
      blutrue=false;     
      autonselect();
    }else if(controller1.ButtonLeft.pressing()||(lcd.pressing()&&(lcd.xPosition()>=240))){
      disp.clearScreen();
      lcd.clearScreen(blue);
      while(controller1.ButtonLeft.pressing()||lcd.pressing()){
      
      }
      blutrue=true;
      autonselect();
    }else if(controller1.ButtonA.pressing()){
      prog=-1;
    }
    if(prog==-1){
      disp.clearScreen();
      disp.setCursor(1,0);
      disp.print("safe auto chosen");
    }
    //vex::task::sleep(125);
  }
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
#define mintilt -1000 //deg
#define maxtilt 300 //deg 
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
void tower(){
lift.spin(vex::directionType::fwd,20,vex::velocityUnits::rpm);
task::sleep(1000);
lift.resetPosition();
lift.setVelocity(200,vex::velocityUnits::rpm);
lift.startRotateTo(-3, vex::rotationUnits::rev);
mecanum_move(3,0,0,true);
task::sleep(2000);
treadout();
task::sleep(1000);
treadstop();
lift.startRotateTo(0, vex::rotationUnits::rev);
mecanum_move(0,1.8,0,true);
task::sleep(1000);
treadin();
mecanum_move(3.5,0,0,true);
lift.startRotateTo(-3, vex::rotationUnits::rev);
treadstop();
mecanum_move(2.5,0,0,true);
task::sleep(1000);
mecanum_move(0,-1.8,0,true);
task::sleep(1000);
treadout();
task::sleep(2000);
treadstop();
lift.startRotateTo(0, vex::rotationUnits::rev);
mecanum_move(0,3.6,0,true);
task::sleep(1000);
treadin();
mecanum_move(2,0,0,true);
treadout();
task::sleep(1000);
treadstop();
lift.startRotateTo(-4, vex::rotationUnits::rev);
mecanum_move(0,1.8,0,true);
task::sleep(1000);
mecanum_move(1,0,0,true);
task::sleep(1000);
treadout();
task::sleep(500);
treadstop();
lift.startSpinTo(0,vex::rotationUnits::rev);
mecanum_move(0,1.8,0,true);
task::sleep(1000);
mecanum_move(0,0,-.5,true);
task::sleep(1000);
treadin();
mecanum_move(4,0,0,true);
task::sleep(1000);
treadstop();
lift.startRotateTo(-4, vex::rotationUnits::rev);
mecanum_move(4,0,0,true);
task::sleep(1000);
mecanum_move(0,0,.5,true);
task::sleep(1000);
mecanum_move(0,-1.8,0,true);
treadout();
task::sleep(1000);
treadstop();
mecanum_move(0,0,-2,true);
task::sleep(1000);
treadin();
mecanum_move(2,0,0,true);
task::sleep(1000);
treadstop();
lift.rotateTo(-5, vex::rotationUnits::rev);
mecanum_move(0,-1.8,0,true);
treadout();
task::sleep(1000);
treadstop();
}
void autonomous( void ) {//this runs without human interaction
  tower();
  /*switch(prog){
    case 1:
    threetower();
    break;
    case 2:
    onestackonetower();
    break;
    case 8:
    auto8();
    break;
    case 9:
    auto9();
    break;
    default:
    onepoint();
    break;
  }
  //playback();
  
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
     if(controller1.ButtonB.pressing()&&(tilt.rotation(vex::rotationUnits::deg)<=maxtilt)){
       tilt.spin(directionType::fwd, 200, vex::velocityUnits::rpm);
     }else{
       if(controller1.ButtonA.pressing()&&(tilt.rotation(vex::rotationUnits::deg)>=mintilt)){
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
       printf("r2 \n");
     }else{
       if(controller1.ButtonR1.pressing()){
         printf("r1 \n");
         lift.spin(directionType::fwd, -200, vex::velocityUnits::rpm);
       }else{
         lift.spin(directionType::fwd, 0, vex::velocityUnits::rpm);
         lift.stop(vex::brakeType::hold);
       }
     }
     if(controller1.ButtonL2.pressing()){
       righttread.spin(directionType::fwd, 200, vex::velocityUnits::rpm);
       lefttread.spin(directionType::fwd, -200, vex::velocityUnits::rpm);
     }else{
       if(controller1.ButtonL1.pressing()){
        righttread.spin(directionType::fwd, -200, vex::velocityUnits::rpm);
         lefttread.spin(directionType::fwd, 200, vex::velocityUnits::rpm);
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
  tower();
  
}