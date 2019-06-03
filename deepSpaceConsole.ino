#include <Joystick.h>
#include <LiquidCrystal_I2C.h>
/*
* name id 
* constant for type 
* number of buttons (limit 16 on drivestation) 
* number of POV hats (limit 2)
* x axis t/f 
* y axis t/f 
* z axis t/f 
* rudder / paddle / other names of no meaning to me 4 * t/f  
* throttle t/f 
* 3 * t/f 
* see arduino joystick on github for more info 
*/
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
16, 1,
false, false, false, 
false, false, false,  
false, false,
false, false, false);

LiquidCrystal_I2C lcd(0x3F, 20, 4);

int PosSwPin = A0;
int PosSwMax = 1023;
int PosSwMin = 0;
int PosSwSegments = 5;
int PosSwIncrement = PosSwMax / PosSwSegments;
int PosSwMidPoint = PosSwIncrement / 2;
int PosSwPosition = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);

  Joystick.begin();
  lcd.init();
  lcd.clear();
  lcd.setBacklight(255);
  
}

const int pinToButtonMap = 4;

int lastSwitchState[10] = {0,0,0,0,0,0,0,0,0,0};
String armPositions[10] = {"park     ",
                                 "ball1     ",
                                 "ball2     ",
                                 "ball3     ",
                                 "port1     ",
                                 "port2     ",
                                 "port3     ",
                                 "ballcs    ",
                                 "portcs    ",
                                 "spare3    "
                                 };
                                 
  String strPosSwitchStatement = "V3 2/19/19";
                                 
void loop() {
  lcd.home();
  lcd.print("ArmLevel: ");
  // put your main code here, to run repeatedly:
  for (int index = 0; index < 10; index++)
  {
    int currentSwitchState = !digitalRead(index + pinToButtonMap);
    //if (currentSwitchState != lastSwitchState[index])
    //{
      Joystick.setButton(index, currentSwitchState);
      lastSwitchState[index] = currentSwitchState;

    //  }

    if(currentSwitchState == true){
        
       // lcd.print(posSwitchStatements[index]);
       strPosSwitchStatement = armPositions[index];
    }
   }
   lcd.setCursor(10,0);
   lcd.print(strPosSwitchStatement);

   int PosSwValue = analogRead(PosSwPin);

   int PosSwPosition = (PosSwValue * PosSwSegments + PosSwMidPoint) / PosSwMax;
   lcd.setCursor(0,1);
   lcd.print("StartPos:");

   String strStartPos = "Teleop";

   switch(PosSwPosition){
    case 1:
      strStartPos = "LeftHab2  ";
      break;
    case 2:
      strStartPos = "RightHab2 ";
      break;
    default :
      strStartPos = "Teleop    ";

   }
   lcd.setCursor(10,1);
   lcd.print(strStartPos);

   Joystick.setHatSwitch(0, PosSwPosition*45);
  
}