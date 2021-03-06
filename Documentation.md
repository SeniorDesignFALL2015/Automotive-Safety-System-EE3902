# Automotic-Speed coordination (ASC)

## Index

- 0_0 Introduction
  - 0_1. What is HASS?
  - 0_2. What does HASS do?
  - 0_3. What does HASS require?
  - 0_4. Contant information
  - 0_5. Questions & Answers
  
- 1_0 About
  - 1_1. Original Idea
  - 1_2. Andy
  - 1_3. Goutam
  - 1_4. Rohan
  - 1_5. Kristen

- 2.0 Hardware, Firmware, and Software
  - 2_1. Microcontroller
      - 2_1_1. Arduino UNO
      - 2_1_2. A-Star Prime
      - 2_1_3. Leonardo
  - 2_2. Ultrasonic Sensor
      - 2_2_1. Parallax Ping)))
      - 2_2_2. SR04 
      - 2_2_3. SRF05, SRF06
      - 2_2_4. DYP-ME007
  - 3_1. Libraries
     - 3_1_1. NewPing
     - 3_1_2. ZumoShieldLibraries

- 3_0 Assembly and Installation
  - 3_1 Hardware assembly
    - 3_1_1 Zumo configuration
    - 3_1_2 Additional parts
  - 3_2 Software installation
    - 3_2_1 Arduino IDE (if its for kids)
    - 3_2_2 Libraries

- 4_0 Usage and Information
  - 4_1
  - 4_2
  - 4_3
[hardware assembly, 
[zumo libraries, zumo installation, ping library, ultrasonic senior, arduino uno, materials]  

## Introduction
0_1. What is HASS?

At relatively high speeds, an autonomous vehicle should able to react intelligently. HASS is a safety control system that helps prevent collisions for autonomous vehicles on public roadways.

0_2. What does HASS do?

HASS will prevent auto collisions with safe lane changing capabilities. This project is coded with C in an Arduino IDE, and is meant to prove the concept with smale-scale robotic vehicles.

0_3. What does HASS require?

HASS requires an microcontroller and ZUMO shield on an robotic vehicle. In addition, this project requires a distance sensor, reflectance sensor, and dual motor drivers. For software uploading, the Arduino IDE will be used.


0_4. Contact information

0_5. Questions & Answers




## About
1_1. Original Idea - 
HASS is an electrical engineering senior design project. It intends improve the method of which autonomous vehicles currently operate.

1_2. Andy - Group Leader and Assistant Coder

1_3. Goutam - Business Expert

1_4. Rohan - Project Manager and Coder (documentation)

1_5. Kristen - R&D and Web Dev (documentation)

# Hardware, Firmware, and Software
2_1 Microcontrollers

Microcontrollers that can be used with the ZUMO shield are Arduino, A-Star Prime, or Freescale boards.

2_2_1.. Arduino Uno R3:
* Microcontroller	ATmega328P
* Operating Voltage	5V
* Input Voltage (recommended)	7-12V
* Input Voltage (limit)	6-20V
* Digital I/O Pins	14 (of which 6 provide PWM output)
* PWM Digital I/O Pins	6
* Analog Input Pins	6
* DC Current per I/O Pin	20 mA
* DC Current for 3.3V Pin	50 mA
* Flash Memory	32 KB (ATmega328P) of which 0.5 KB used by bootloader
* SRAM	2 KB (ATmega328P)
* EEPROM	1 KB (ATmega328P)
* Clock Speed	16 MHz
* Length	68.6 mm
* Width	53.4 mm
* Weight	25 g

2_2_2. A-Star 32U4 Prime
* Microcontroller ATmega32u4 
* Operating Voltage 5V 
* Input Voltage (recommended) 2.7 V to 11.8 V 
* Input Voltage (limits) 6-20V 
* Digital I/O Pins 26
* PWM Channels 7 
* Analog Input Channels 12 
* DC Current per I/O Pin 40 mA 
* DC Current for 3.3V Pin 50 mA 
* Flash Memory 32 KB (ATmega32u4) of which 4 KB used by bootloader 
* SRAM 2.5 KB (ATmega32u4) 
* EEPROM 1 KB (ATmega32u4) 
* Clock Speed 16 MHz 
* Length 68.6 mm 
* Width 53.3 mm 
* Weight 22g 

2_2_3. Arduino Leonardo 
* Microcontroller ATmega32u4 
* Operating Voltage 5V 
* Input Voltage (recommended) 7-12V 
* Input Voltage (limits) 6-20V 
* Digital I/O Pins 20 
* PWM Channels 7 
* Analog Input Channels 12 
* DC Current per I/O Pin 40 mA 
* DC Current for 3.3V Pin 50 mA 
* Flash Memory 32 KB (ATmega32u4) of which 4 KB used by bootloader 
* SRAM 2.5 KB (ATmega32u4) 
* EEPROM 1 KB (ATmega32u4) 
* Clock Speed 16 MHz 
* Length 68.6 mm 
* Width 53.3 mm 
* Weight 20g 



Project Costs:
* Zumo Robot For Arduino (3) = $100
* Parallax Ping Ultrasonic Sensor (9) = $30
* Nylon Accessories = $8.50
* Acrylic Glass = $9.00
* Arduino (3) =$20
* Parallax ping Ultrasonic Range Sensor28015 = $32.99
* Zumo Robert for Arduino,v1.2 (2) = $210.80
* premium Jumper Wire 10-pack F-F 3*Black = $2.85
* Parallax PING Ultrasonic Sensor#28015 = $29.99
* 0.100"(2.54mm) Female Header:1*3-pin, Straight=$6.80
* Adafruit Perma-Proto Quater-Sized Breadboard PCB(3-Pack)= 17.90
* Wire with Pre-crimped Terminals 50-Piece Rainbow Assortment M-M 3"=$8.95
* 170-Point Breadboard(White)=$5.90
* 100.1 Micro Metal Gearmotor HP with Extended Motor Shaft =$33.90
* 0.100"(2.54mm)Female Header:1*2-Pin, Straight =$2.90
* Magnatic Encoder Pair Kit for Micro Metal Gearmotors,12 CRP,2.7-18V =$8.95
* 
* 
* Perforated Soldering Board
* Female Header Connector
* Servo
* Jumper Wire


Total = 3($100) + 9($30) + $8.5 + $9 +3($20) 


## Assembly and Installation

3_1. There are many different projects within this project:
-> Line Following
-> Obstacle Avoidance
-> Multiple Position Sensor Interfacing

## References
## Scope of Work

The ideas and steps that were taken in to account in order to build HASS were complex and dependent of each other. The testing process followed a specific order of checkpoints that were required to meet in order to have everything working as expected. 

1. Getting the Zumo robot to properly line follow.
2. Installing ultrasonic sensors on Zumo for object detection and avoidance along with the continuation of line following.
3. Once Zumo is line following and the sensors are installed, Zumo will be able to detect a similar vehicle traveling at a slower rate of speed in the same direction and adjust its speed in order to travel at a safe distance. 
4. Once Zumo has adjusted to a safe distance, sensors will engauge on the left lane of the road and detect any other vehicles or object. From here Zumo sensors will determine weather or not enough time and speed is available in order to safely overtake the vehicle traveling in front of Zumo. 
5. If the sensors detects a vehicle or object, stay in lane and continue traveling behind the vehicle.
6. If no object is detected Zumo will change lanes, the motors will increase speeds, and the sensor will determine when changing back to the right lane without a collision is possible. 
7. Once a safe distance is reached, Zumo will change back to the right lane and continue to follow the line.



