/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       pl32                                                      */
/*    Created:      Thu Feb 17 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// M1                   motor         1               
// M2                   motor         2               
// M4                   motor         4               
// M5                   motor         5               
// M6                   motor         6               
// M7                   motor         7               
// M11                  motor         11              
// M12                  motor         12              
// M14                  motor         14              
// M15                  motor         15              
// M16                  motor         16              
// M17                  motor         17              
// M19                  motor         19              
// M20                  motor         20              
// M8                   motor         8               
// M9                   motor         9               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

namespace robotSys{
  motor_group mainDrvL = motor_group(M6, M4, M2);
  motor_group mainDrvR =  motor_group(M7, M5, M1);
  motor_group craneDown = motor_group(M11, M12);
  motor_group craneUp = motor_group(M8, M9);
  motor_group claw = motor_group(M19, M20);
  motor_group craneShiftL = motor_group(M14, M15);
  motor_group craneShiftR = motor_group(M16, M17);
  drivetrain mainDrivetrain = drivetrain(mainDrvL, mainDrvR);
  drivetrain craneShiftDrivetrain = drivetrain(craneShiftL, craneShiftR);
  drivetrain craneDrivetrain = drivetrain(craneDown, craneUp);
  const int scSize = 3;
  int selectedSCIndex = 0;
  int speedCap[3] = { 100, 60, 80 };
  bool loop = true;

  void stop(){
    mainDrivetrain.stop();
    craneDrivetrain.stop();
    craneShiftDrivetrain.stop();
    claw.stop();
  }

  void controllerMode(){
    bool mainDrvLSpin = false;
    bool mainDrvRSpin = false;
    int controllerDriveMode = 0;
    int motorSpeed[2];
    craneDrivetrain.setDriveVelocity(speedCap[1], percent);
    craneDrivetrain.setStopping(hold);
    craneShiftDrivetrain.setDriveVelocity(speedCap[2], percent);

    while(loop){
      if(Controller1.ButtonA.pressing()){
        if(Controller1.ButtonDown.pressing())
          loop = false;

        if(Controller1.ButtonUp.pressing())
          stop();

        if(Controller1.ButtonL1.pressing()){
          stop();
          while(!Controller1.ButtonX.pressing());
        }

      }else if(Controller1.ButtonB.pressing()){
        if(Controller1.ButtonLeft.pressing() && speedCap[selectedSCIndex] > 10)
          speedCap[selectedSCIndex] -= 10;

        if(Controller1.ButtonRight.pressing() && speedCap[selectedSCIndex < 100])
          speedCap[selectedSCIndex] += 10;

        if(Controller1.ButtonUp.pressing() && selectedSCIndex < scSize - 1)
          selectedSCIndex++;
        
        if(Controller1.ButtonDown.pressing() && selectedSCIndex > 0)
          selectedSCIndex--;

        wait(50, msec);
      }else{
        switch(controllerDriveMode){
          default:
            motorSpeed[0] = Controller1.Axis3.position() - (100 - speedCap[0]);
            motorSpeed[1] = Controller1.Axis2.position() - (100 - speedCap[0]);
        }

        if(motorSpeed[0] < 5 && motorSpeed[0] > -5){
          mainDrvL.stop();
          mainDrvLSpin = false;
        }else{
          mainDrvL.setVelocity(motorSpeed[0], percent);
          mainDrvLSpin = true;
        }

        if(motorSpeed[1] < 5 && motorSpeed[1] > -5){
          mainDrvR.stop();
          mainDrvRSpin = false;
        }else{
          mainDrvR.setVelocity(motorSpeed[1], percent);
          mainDrvRSpin = true;
        }

        if(mainDrvLSpin)
          mainDrvL.spin(forward);

        if(mainDrvRSpin)
          mainDrvR.spin(forward);

        if(Controller1.ButtonR1.pressing()){
          craneDrivetrain.drive(forward);
        }else if(Controller1.ButtonR2.pressing()){
          craneDrivetrain.drive(reverse);
        }else{
          craneDrivetrain.stop();
        }

        if(Controller1.ButtonL1.pressing()){
          claw.spin(forward);
        }else if(Controller1.ButtonL2.pressing()){
          claw.spin(reverse);
        }else{
          claw.stop();
        }

        if(Controller1.ButtonUp.pressing()){
          craneShiftDrivetrain.drive(forward);
        }else if(Controller1.ButtonDown.pressing()){
          craneShiftDrivetrain.drive(reverse);
        }else{
          craneShiftDrivetrain.stop();
        }
      }
      wait(20, msec);
    }
  }

  void debug(){
    Controller1.Screen.clearScreen();
    while(loop){
      Controller1.Screen.setCursor(1,1);
      Controller1.Screen.print("Speed Cap: %d, %d, %d", speedCap[0], speedCap[1], speedCap[2]);
      Controller1.Screen.newLine();
      Controller1.Screen.print("Selected Index: %d", selectedSCIndex);
    }
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  vex::thread controllerThread = vex::thread(robotSys::controllerMode);
  vex::thread debugThread = vex::thread(robotSys::debug);

  controllerThread.join();
  debugThread.join();

  robotSys::stop();
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("System Halted");
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("System Halted");
}
