#include <NewPing.h>
#include <Average.h>

#define SONAR_NUM     2 // Number or sensors.
#define MAX_DISTANCE 100 // Max distance in cm.
#define PING_INTERVAL 100 // Milliseconds between pings.
bool flag = 0; 
bool flag2 = 0;
unsigned long pingTimer[SONAR_NUM]; // When each pings.
unsigned long avgping0;
unsigned long avgping1;
unsigned int cm[SONAR_NUM]; // Store ping distances.
uint8_t currentSensor = 0; // Which sensor is active.
Average<unsigned int> ave(5);

 
NewPing sonar[SONAR_NUM] = { // Sensor object array.
  NewPing(3, 3, MAX_DISTANCE),
  NewPing(6, 6, MAX_DISTANCE),
  NewPing(9, 9, MAX_DISTANCE),
 };
 
 
void setup() {
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
ave.push(cm[0]);
for(int i = 0; i < 5; i++) {
ave.get(i);

 }

}
void echoCheck() { // If ping received, set the sensor distance to array.
  if (sonar[currentSensor].check_timer()){
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
  }else{
    cm[currentSensor]=MAX_DISTANCE;  }
}


void oneSensorCycle() { // Sensor ping cycle complete,
//do something with the ping results.
avgping0= ave.mean();


if( avgping0 <= 50  && avgping0 > 5 && cm[1] <= 15 && cm[1] > 2 && cm[2] > 12 ){
   Serial.write(0xFF);
}
else if( avgping0 > 50 && cm[1] <= 15 && cm[1] > 2 && cm[2] > 12 ){
   Serial.write(0x0C);
}
else if( avgping0 <= 50 && avgping0 > 5 && cm[1] > 15 && cm[2] > 12 ){
   Serial.write(0xF0);
}
else if( avgping0 > 50  && cm[1] > 15 && cm[2] > 12 ){  
  Serial.write(0x00);
}

else if( avgping0 <= 50  && avgping0 > 5 && cm[1] <= 15 && cm[1] > 2 && cm[2] <= 12 ){
   Serial.write(0xFF);
}
/// NF SS ///
else if( avgping0 > 50 && cm[1] <= 15 && cm[1] > 2 && cm[2] <= 12 ){
   Serial.write(0x00);
}
/// SF NS ///
else if( avgping0 <= 50 && avgping0 > 5 && cm[1] > 15 && cm[2] <= 12 ){
   Serial.write(0xF0);
}
/// NF NS ///
else if( avgping0 > 50  && cm[1] > 15 && cm[2] <= 12 ){  
  Serial.write(0x00);
}


}




