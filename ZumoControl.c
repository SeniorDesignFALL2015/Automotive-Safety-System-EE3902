
#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <ZumoBuzzer.h>
#include <avr/io.h>
#include <avr/interrupt.h>
ZumoBuzzer buzzer;



ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
int lastError = 0;
const int MAX_SPEED = 300;
byte c;
int corrector;

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
  
   
 
}


void loop() {
//  int a = 0;
//  int b = 0;
//  a = digitalRead(6);
//  b = digitalRead(7);
//  
//  if( a == LOW && b==LOW){
//    linefollow();
//  }
//  else if( a == HIGH && b==LOW){
//    changeleftlane();
//  }
  
   while (Serial.available()) {
      delay(10);  //small delay to allow input buffer to fill

      c = Serial.read();  //gets one byte from serial buffer
      Serial.print(c);
     } //makes the string readString

       if (c == 0 || c==12)   //Match ID 3
          {   //do something with it...
         // corrector=2500;
          linefollow();
  
           }
       else if(c = 240){
         //corrector= -3000
         changeleftlane();
         //buzzer.play(">g32>>b32");
        } 

}
  
   




 void slowlinefollow(){
const int SLOW_SPEED = 100;
  unsigned int sensors[6];
  int position = reflectanceSensors.readLine(sensors);
  int error = position - 1000;
 int speedDifference = error / 4 + 6 * (error - lastError);
 lastError = error;
   int m1Speed = SLOW_SPEED + speedDifference;
  int m2Speed = SLOW_SPEED - speedDifference;
 if (m1Speed < 0)
    m1Speed = 0;
  if (m2Speed < 0)
    m2Speed = 0;
  if (m1Speed > SLOW_SPEED)
    m1Speed = SLOW_SPEED;
  if (m2Speed > SLOW_SPEED)
    m2Speed = SLOW_SPEED;
    motors.setSpeeds(m1Speed, m2Speed);
}

void linefollow()//
{// turns on drive motor in reverse and leaves it on
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

void changeleftlane(){
     motors.setLeftSpeed(-100);
     motors.setRightSpeed(200);
     delayMicroseconds(1); 
}
void changerightlane(){
     motors.setLeftSpeed(200);
     motors.setRightSpeed(-100);
     delay(10);
}
void stop()//stop both motors
{
     motors.setLeftSpeed(0);
     motors.setRightSpeed(0); 
}
void slow()
{
   motors.setLeftSpeed(200);
   motors.setRightSpeed(200);
   delay(1);
}

