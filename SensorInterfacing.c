#include <NewPing.h>


#define SONAR_NUM     2 // Number or sensors.
#define MAX_DISTANCE 200 // Max distance in cm.
#define PING_INTERVAL 200 // Milliseconds between pings.
unsigned long pingTimer[SONAR_NUM]; // When each pings.
unsigned int cm[SONAR_NUM]; // Store ping distances.
uint8_t currentSensor = 0; // Which sensor is active.
 
NewPing sonar[SONAR_NUM] = { // Sensor object array.
  NewPing(3, 3, MAX_DISTANCE),
  NewPing(4, 4, MAX_DISTANCE),
 };
void setup() {
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  pingTimer[0] = millis() + 75;           // First ping starts at 75ms, gives time for the Arduino to chill before starting.
  for (uint8_t i = 1; i < SONAR_NUM; i++) // Set the starting time for each sensor.
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
}
void loop() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through all the sensors.
     if (millis() >= pingTimer[i]) {         // Is it this sensor's time to ping?
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;  // Set next time this sensor will be pinged.
      if (i == 0 && currentSensor == SONAR_NUM - 1) oneSensorCycle(); // Sensor ping cycle complete, do something with the results.
      sonar[currentSensor].timer_stop();          // Make sure previous timer is canceled before starting a new ping (insurance).
      currentSensor = i;                          // Sensor being accessed.
      cm[currentSensor] = 0;                      // Make distance zero in case there's no ping echo for this sensor.
      sonar[currentSensor].ping_timer(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
     }
  }
  // Other code that *DOESN'T* analyze ping results can go here.
}
void echoCheck() { // If ping received, set the sensor distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

byte x = 0x00;
void oneSensorCycle() { // Sensor ping cycle complete,
//do something with the ping results.
if( cm[0] < 35 && cm[0] > 3 && cm[1] < 15 && cm[1] > 3){
    x |= 0xFF;
   Serial.write(0xFF);
}
else if( cm[0] > 35 && cm[1] < 15 && cm[1] > 3){
   x &= 0x0C;
   x |= 0x0C;
   Serial.write(x);
}
else if( cm[0] < 35 && cm[0] > 3 && cm[1] > 15){
   x &= 0xF0;
   x |= 0xF0;
   Serial.write(0xF0);
}
else if( cm[0] > 35  && cm[1] > 15){
  x &= 0x00;    
  Serial.write(0x00);
}

//     Serial.println(4);
//Serial.println(cm[0]);
//Serial.print(cm[0]);
//Serial.print(' ');
//Serial.print(cm[1]);
//Serial.println();
}


