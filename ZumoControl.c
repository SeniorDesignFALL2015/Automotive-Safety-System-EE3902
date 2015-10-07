
#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <ZumoBuzzer.h>
ZumoBuzzer buzzer;

ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
int lastError = 0;
const int MAX_SPEED = 400;
int val;


void setup() {
  Serial.begin(9600);
  button.waitForButton();

  reflectanceSensors.init();
   delay(1000);
  int i;
  for(i = 0; i < 80; i++)
  {
    if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
      motors.setSpeeds(-200, 200);
    else
      motors.setSpeeds(200, -200);
      reflectanceSensors.calibrate();

    // Since our counter runs to 80, the total delay will be
    // 80*20 = 1600 ms.
    delay(20);
  }
  motors.setSpeeds(0,0);
  button.waitForButton();
  
  Serial.begin(115200);
  
    
}

void loop() {
  
  linefollow();
  
  int incoming = Serial.available();
  if (incoming > 0)
  {
    val = Serial.parseInt();  //Reads integers as integer rather than ASCI. Anything else returns 0
    if(val == 10){
      buzzer.play(">g32>>c32");
     Serial.println(val); 
      }
     if(val == 1){
      buzzer.play(">g32>>c32");
     Serial.println(val); 
      }
  
  // Other code that *DOESN'T* analyze ping results can go here.
}
  
   


}

 void linefollow(){// turns on drive motor in forward and leaves it on
  unsigned int sensors[6];
  int position = reflectanceSensors.readLine(sensors);
  int error = position - 2500;
 int speedDifference = error / 4 + 6 * (error - lastError);
 lastError = error;
   int m1Speed = MAX_SPEED + speedDifference;
  int m2Speed = MAX_SPEED - speedDifference;
 if (m1Speed < 0)
    m1Speed = 0;
  if (m2Speed < 0)
    m2Speed = 0;
  if (m1Speed > MAX_SPEED)
    m1Speed = MAX_SPEED;
  if (m2Speed > MAX_SPEED)
    m2Speed = MAX_SPEED;
     motors.setSpeeds(m1Speed, m2Speed);
  
}
void linefollow2()//
{// turns on drive motor in reverse and leaves it on
    unsigned int sensors[6];
  int position = reflectanceSensors.readLine(sensors);
  int error = position - 1000;
 int speedDifference = error / 4 + 6 * (error - lastError);
 lastError = error;
   int m1Speed = MAX_SPEED + speedDifference;
  int m2Speed = MAX_SPEED - speedDifference;
 if (m1Speed < 0)
    m1Speed = 0;
  if (m2Speed < 0)
    m2Speed = 0;
  if (m1Speed > MAX_SPEED)
    m1Speed = MAX_SPEED;
  if (m2Speed > MAX_SPEED)
    m2Speed = MAX_SPEED;
      
     motors.setSpeeds(m1Speed, m2Speed);
}

void changeleftlane(){
     motors.setLeftSpeed(-100);
     motors.setRightSpeed(200);
     delay(500);
}

void changerightlane(){
     motors.setLeftSpeed(200);
     motors.setRightSpeed(-100);
     delay(500);
}

void stop()//stop both motors
{
     motors.setLeftSpeed(0);
     motors.setRightSpeed(0);
     
}
