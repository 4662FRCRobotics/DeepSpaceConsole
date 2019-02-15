#include <LiquidCrystal_I2C.h>

#include <Joystick.h>


Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
16, 2,
true, true, true,
false, false, false,
false, true,
false, false, false);

LiquidCrystal_I2C lcd(0x3F, 20, 4);

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
                                 "ball1      ",
                                 "ball2      ",
                                 "ball3      ",
                                 "port1      ",
                                 "port2      ",
                                 "port3      ",
                                 "spair1     ",
                                 "spair2     ",
                                 "spair3     "
                                 };
                                 
  String strPosSwitchStatement = "N/A    ";
                                 
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
  
}
