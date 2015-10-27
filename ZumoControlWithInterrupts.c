
#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <ZumoBuzzer.h>
#include <avr/io.h>
#include <avr/interrupt.h>
ZumoBuzzer buzzer;

#define F_CPU 16000000
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16))) - 1)

ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
int lastError = 0;
const int MAX_SPEED = 300;
int corrector;

void setup() {
  //Serial.begin(9600);
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
  
  cli();

    UBRR0H = BAUD_PRESCALE >> 8;
    UBRR0L = BAUD_PRESCALE ;
    
    UCSR0B = (1 << RXCIE0)|(1 << RXEN0);
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
    sei();
   
 
}

ISR(USART_RX_vect){  //the USART receive Interrupt Service Routine
char c = UDR0;
          //linefollow();
     //   } 
     if(c == 0xf0)
     {
     stop();
     }
     else if(c == 0xff)
     {
     stop();
     }
     else if(c == 0x00)
     {
       linefollow();
     }
     else if(c = 0x0C)
     {
       stop();
     }
}

void loop() {
  linefollow();

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
     delayMicroseconds(15); 
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

