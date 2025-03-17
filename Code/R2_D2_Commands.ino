// R2-D2 Commands
// This part of the project is about to receive data accurately from an app which provides collaboration between an Android phone and Arduino Uno is called R2-D2.
// Each of choices on Commands Screen which is the first screen on the app transmits a char from Android phone to a compatible Bluetooth module with Arduino such as HC-O6.
// Using the volatile boolean system makes it easy while transmitting data for controlling R2-D2 replica.
//
// Requirements for this:
// Arduino Due
// A HC-06 Bluetooth module
// Four Servo motors(one of them has to be a continuous Servo)
// A DHT11 module
// A LCD screen(16,2)
// Two L298N Pair Motor Drivers
// Four Wheel and DC Motor Kits
// Two 9V batteries
// Five HC-SR04 Ultrasonic Distance Sensors
// A mini breadboard
// Learning Servo library
// Learning LiquidCrystal library
// Learning DHT library
//
//
// First of all, you have to change HC-06 module name to "Commands" with AT commands for proceeding app with accurate data.
// And Arduino Due has three extra TX-RX pins so HC-06 module can be used with them instead of SoftwareSerial libary. 
//
// DHT11 module is for getting the value of temperature and humidity. My searching shows me that DHT11 library is the best option for this module, you can download it on here:
// https://github.com/markruys/arduino-DHT.git
//
// LCD screen is for seeing data which comes from DHT11 module and it can be used as R2-D2 eye.
// If you want, you can change the LCD pins on Arduino Due and create different marks to use lcd.createChar() with bytes.
//
// L298N Pair Motor Driver allows working two DC motor which are controlled by Arduino pins seperately at the same time and controlling which way each of motors turns through data you choose.
//
// 9V battery is enough to operate motors which work with up to 24V.
//
// Wheel and DC Motor Kit is easy to use while operating motors by L298N Pair Motor Driver because they are compatible each other.
//
// HC-SR04 Ultrasonic Distance Sensor works based on the range of wavelength of sound waves as a radar. However the compelling thing at this process is that module needs time to understand 
// where is the obstacle so that giving the right delay time to module is necessary.
// When HC-SR04 Ultrasonic Distance Sensors are set up with the right delay time, the project has a basic obstacle recognition system. I set up each of HC-SR04 Ultrasonic Distance Sensors
// to react 40cm for any obstacles. Using five HC-SR04 Ultrasonic Distance Sensor is adequate for seeing all obstacles by R2-D2 replica.
//
// I designed a robot arm which includes two joints(you can increase the number of joints but if you did this, you would have to add another external battery on your project because of the
// insufficiency of Arduino Due)for the project. Each of the joints consists of a servo motor and a component which is compatible with Servo such as 3D printing parts, old toys parts etc.
// If you have already had a robot arm, you can change my design with it.
//
// Two joints require two Servo motors(I have used SG90 9G Servo Motors for a long time but you can use a different sort of Servo). Using a continuous Servo(like Feetech FS90R 
// Continuously Rotary Micro Servo) at the end of the robot arm gives you a multi-functional turning part like I used.
//
// And the fourth Servo Motor is for giving the rotary motion to R2-D2 replica head.
//
// Connections:
//                                Arduino Due

// HC-06 Bluetooth module
// RX                             -  TX3- Pin 14
// TX                             -  RX3- Pin 15
// VCC                            -  5V
// GND                            -  GND   
// Servo armr                     -  Pin 10
// Servo arml                     -  Pin 11
// Servo arm(continuous Servo)    -  Pin 3
// Servo head                     -  Pin 9
// DHT11 module
// Pin 1                          -  5V
// Pin 2                          -  Pin 38 and 5V with 10K resistor
// Pin 3                          -  empty
// Pin 4                          -  GND
// LCD screen(16,2)
//                                -  5V
//                                -  GND
// RS pin                         -  Pin 32
// Enable                         -  Pin 33
// D4 pin                         -  Pin 34
// D5 pin                         -  Pin 35
// D6 pin                         -  Pin 36
// D7 pin                         -  Pin 37
// R/W                            -  GND
//                                -  5V
// L298N Pair Motor Driver1
// In1                            -  Pin 40
// In2                            -  Pin 41
// In3                            -  Pin 42
// In4                            -  Pin43
// OUT1                           -  DC Motor (+)
// OUT2                           -  DC Motor (-)
// OUT3                           -  DC Motor (+)
// OUT4                           -  DC Motor (-)
// GND                            -  9V battery (-) and GND(Arduino)
// 12V                            -  9V battery (+)
// L298N Pair Motor Driver2
// In1                            -  Pin 44
// In2                            -  Pin 45
// In3                            -  Pin 46
// In4                            -  Pin47
// OUT1                           -  DC Motor (+)
// OUT2                           -  DC Motor (-)
// OUT3                           -  DC Motor (+)
// OUT4                           -  DC Motor (-)
// GND                            -  9V battery (-) and GND(Arduino)
// 12V                            -  9V battery (+)
// HC-SR04 Ultrasonic Distance Sensors
// Sensor1
// GND                            -  GND
// Trig                           -  Pin 22
// Echo                           -  Pin 23
// VCC                            -  5V
// Sensor2
// GND                            -  GND
// Trig                           -  Pin 24
// Echo                           -  Pin 25
// VCC                            -  5V
// Sensor3
// GND                            -  GND
// Trig                           -  Pin 26
// Echo                           -  Pin 27
// VCC                            -  5V
// Sensor4
// GND                            -  GND
// Trig                           -  Pin 28
// Echo                           -  Pin 29
// VCC                            -  5V
// Sensor5
// GND                            -  GND
// Trig                           -  Pin 30
// Echo                           -  Pin 31
// VCC                            -  5V



#define Commands Serial3 
#include <Servo.h>
#include <LiquidCrystal.h>
#include "DHT.h"

LiquidCrystal lcd(32,33,34,35,36,37);

DHT dht;

Servo arm;
Servo head;
Servo armr;
Servo arml;

const int in1=40;
const int in2=41;
const int in3=42;
const int in4=43;
const int in1_1=44;
const int in2_1=45;
const int in3_1=46;
const int in4_1=47;


const int sensor_1_trig =22;
const int sensor_1_echo=23;
const int sensor_2_trig =24;
const int sensor_2_echo =25;
const int sensor_3_trig =26;
const int sensor_3_echo =27;
const int sensor_4_trig =28;
const int sensor_4_echo =29;
const int sensor_5_trig =30;
const int sensor_5_echo=31;

long duration_1; 
long distance_1;
long duration_2; 
long distance_2;
long duration_3; 
long distance_3;
long duration_4; 
long distance_4;
long duration_5; 
long distance_5;

char c;

volatile boolean Arm_on=false;
volatile boolean Arm_off=false;
volatile boolean Right=false;
volatile boolean Left=false;
volatile boolean F_1=false;
volatile boolean B_1=false;
volatile boolean Auto=false;
volatile boolean Stop=false;
volatile boolean F_2=false;
volatile boolean B_2=false;
volatile boolean Arm_R=false;
volatile boolean Arm_L=false;

byte normal[8] = {
  0b10000,
  0b10000,
  0b10000,
  0b11110,
  0b11100,
  0b11110,
  0b11100,
  0b11110,
};
byte danger[8] = {
  0b10001,
  0b01010,
  0b00100,
  0b01010,
  0b10001,
  0b11111,
  0b11111,
  0b11111,
};

void setup() {
  Serial.begin(9600);
  Commands.begin(9600);
  lcd.createChar(1,normal);
  lcd.createChar(2,danger);
  lcd.begin(16, 2);  
  dht.setup(38);
  arm.attach(3);
  head.attach(9);
  armr.attach(10);
  arml.attach(11);
   pinMode(sensor_1_trig,OUTPUT);
   pinMode(sensor_1_echo,INPUT);
   pinMode(sensor_2_trig,OUTPUT);
   pinMode(sensor_2_echo,INPUT);
   pinMode(sensor_3_trig,OUTPUT);
   pinMode(sensor_3_echo,INPUT);
   pinMode(sensor_4_trig,OUTPUT);
   pinMode(sensor_4_echo,INPUT);
   pinMode(sensor_5_trig,OUTPUT);
   pinMode(sensor_5_echo,INPUT);
   
   pinMode(in1,OUTPUT);
   pinMode(in2,OUTPUT);
   pinMode(in3,OUTPUT);
   pinMode(in4,OUTPUT);
   pinMode(in1_1,OUTPUT);
   pinMode(in2_1,OUTPUT);
   pinMode(in3_1,OUTPUT);
   pinMode(in4_1,OUTPUT);


}

void loop() {
   
 
 get_and_write_data_DHT();
 Commands_Getting_Data_and_Controlling_System();
   
 
}
void get_and_write_data_DHT(){
 delay(dht.getMinimumSamplingPeriod());
 float humidity = dht.getHumidity();
 float temperature = dht.getTemperature();
 lcd.setCursor(0,0);
 lcd.print("Celsius=");
 lcd.setCursor(10,0);
 lcd.print( temperature );
 lcd.setCursor(0,1);
 lcd.print("Humidity=" );
 lcd.setCursor(10,1);
 lcd.print(humidity );
 if(temperature>35&&humidity<30){
  lcd.clear();
  lcd.write(1);
 }
 if(temperature<20&&humidity<58){

  for(int i=0;i<1000;i++){
  lcd.clear();
  lcd.write(2);
  }
 }
}
void get_distance_toHC_sr04_for_AutoMode(){

digitalWrite(sensor_1_trig,LOW);
  delay(2);
  digitalWrite(sensor_1_trig,HIGH);
  delay(10);
  digitalWrite(sensor_1_trig,LOW);
  duration_1 = pulseIn(sensor_1_echo,HIGH);
  distance_1= duration_1/29.1;

Serial.println(distance_1);

  digitalWrite(sensor_2_trig,LOW);
  delay(2);
  digitalWrite(sensor_2_trig,HIGH);
  delay(10);
  digitalWrite(sensor_2_trig,LOW);
  duration_2 = pulseIn(sensor_2_echo,HIGH);
  distance_2= duration_2/29.1;


  
  digitalWrite(sensor_3_trig,LOW);
  delay(2);
  digitalWrite(sensor_3_trig,HIGH);
  delay(10);
  digitalWrite(sensor_3_trig,LOW);
  duration_3 = pulseIn(sensor_3_echo,HIGH);
  distance_3= duration_3/29.1;



  digitalWrite(sensor_4_trig,LOW);
  delay(2);
  digitalWrite(sensor_4_trig,HIGH);
  delay(10);
  digitalWrite(sensor_4_trig,LOW);
  duration_4 = pulseIn(sensor_4_echo,HIGH);
  distance_4= duration_4/29.1;
  

  
  digitalWrite(sensor_5_trig,LOW);
  delay(2);
  digitalWrite(sensor_5_trig,HIGH);
  delay(10);
  digitalWrite(sensor_5_trig,LOW);
  duration_5 = pulseIn(sensor_5_echo,HIGH);
  distance_5= duration_5/29.1;
 


 if(distance_1<40){
digitalWrite(in1,LOW);
digitalWrite(in2,HIGH);
digitalWrite(in3,LOW);
digitalWrite(in4,HIGH);
digitalWrite(in1_1,LOW);
digitalWrite(in2_1,HIGH);
digitalWrite(in3_1,LOW);
digitalWrite(in4_1,HIGH);
  }
   if(distance_1>45){
digitalWrite(in1,HIGH);
digitalWrite(in2,LOW);
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);
digitalWrite(in1_1,HIGH);
digitalWrite(in2_1,LOW);
digitalWrite(in3_1,HIGH);
digitalWrite(in4_1,LOW);
  }

    if(distance_2<40){
digitalWrite(in1,LOW);
digitalWrite(in2,HIGH);
digitalWrite(in3,LOW);
digitalWrite(in4,HIGH);
digitalWrite(in1_1,LOW);
digitalWrite(in2_1,LOW);
digitalWrite(in3_1,LOW);
digitalWrite(in4_1,LOW);
  }

    if(distance_3<40){
digitalWrite(in1,HIGH);
digitalWrite(in2,LOW);
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);
digitalWrite(in1_1,LOW);
digitalWrite(in2_1,LOW);
digitalWrite(in3_1,LOW);
digitalWrite(in4_1,LOW);
  }

    if(distance_4<40){
digitalWrite(in1,LOW);
digitalWrite(in2,LOW);
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);
digitalWrite(in1_1,LOW);
digitalWrite(in2_1,HIGH);
digitalWrite(in3_1,LOW);
digitalWrite(in4_1,HIGH);
  }

    if(distance_5<40){
digitalWrite(in1,LOW);
digitalWrite(in2,LOW);
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);
digitalWrite(in1_1,HIGH);
digitalWrite(in2_1,LOW);
digitalWrite(in3_1,HIGH);
digitalWrite(in4_1,LOW);
  }

    if(distance_2<40&&distance_4<40){
digitalWrite(in1,LOW);
digitalWrite(in2,HIGH);
digitalWrite(in3,LOW);
digitalWrite(in4,HIGH);
digitalWrite(in1_1,LOW);
digitalWrite(in2_1,HIGH);
digitalWrite(in3_1,LOW);
digitalWrite(in4_1,HIGH);
  }

    if(distance_3<40&&distance_5<40){
digitalWrite(in1,HIGH);
digitalWrite(in2,LOW);
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);
digitalWrite(in1_1,HIGH);
digitalWrite(in2_1,LOW);
digitalWrite(in3_1,HIGH);
digitalWrite(in4_1,LOW);
  }

  
}
void Commands_Getting_Data_and_Controlling_System(){
   
   if(Commands.available()){
   c= Commands.read();
  
   
   if (c=='2'){
    
 Arm_on=true;
 Arm_off=false;
 Right=false;
 Left=false;
 F_1=false;
 B_1=false;
 Auto=false;
 Stop=false;
 F_2=false;
 B_2=false;
 Arm_R=false;
 Arm_L=false;
  
   }
   else if (c=='3'){
    
 Arm_on=false;
 Arm_off=true;
 Right=false;
 Left=false;
 F_1=false;
 B_1=false;
 Auto=false;
 Stop=false;
 F_2=false;
 B_2=false;
 Arm_R=false;
 Arm_L=false;
 
   }
    else   if (c=='4'){
    
 Arm_on=false;
 Arm_off=false;
 Right=true;
 Left=false;
 F_1=false;
 B_1=false;
 Auto=false;
 Stop=false;
 F_2=false;
 B_2=false;
 Arm_R=false;
 Arm_L=false;

   }
     else  if (c=='5'){
    
 Arm_on=false;
 Arm_off=false;
 Right=false;
 Left=true;
 F_1=false;
 B_1=false;
 Auto=false;
 Stop=false;
 F_2=false;
 B_2=false;
 Arm_R=false;
 Arm_L=false;
   }
   
   else  if (c=='6'){
    
 Arm_on=false;
 Arm_off=false;
 Right=false;
 Left=false;
 F_1=true;
 B_1=false;
 Auto=false;
 Stop=false;
 F_2=false;
 B_2=false;
 Arm_R=false;
 Arm_L=false;
   }
   else   if (c=='7'){
    
 Arm_on=false;
 Arm_off=false;
 Right=false;
 Left=false;
 F_1=false;
 B_1=true;
 Auto=false;
 Stop=false;
 F_2=false;
 B_2=false;
 Arm_R=false;
 Arm_L=false;
   }
   else  if (c=='8'){
    
 Arm_on=false;
 Arm_off=false;
 Right=false;
 Left=false;
 F_1=false;
 B_1=false;
 Auto=true;
 Stop=false;
 F_2=false;
 B_2=false;
 Arm_R=false;
 Arm_L=false;
   }
 else   if (c=='9'){
    
 Arm_on=false;
 Arm_off=false;
 Right=false;
 Left=false;
 F_1=false;
 B_1=false;
 Auto=false;
 Stop=true;
 F_2=false;
 B_2=false;
 Arm_R=false;
 Arm_L=false;
   }
  else   if (c=='a'){
    
 Arm_on=false;
 Arm_off=false;
 Right=false;
 Left=false;
 F_1=false;
 B_1=false;
 Auto=false;
 Stop=false;
 F_2=true;
 B_2=false;
 Arm_R=false;
 Arm_L=false;
   }
  else   if (c=='b'){
    
 Arm_on=false;
 Arm_off=false;
 Right=false;
 Left=false;
 F_1=false;
 B_1=false;
 Auto=false;
 Stop=false;
 F_2=false;
 B_2=true;
 Arm_R=false;
 Arm_L=false;
   }
 else if (c=='d'){
    
 Arm_on=false;
 Arm_off=false;
 Right=false;
 Left=false;
 F_1=false;
 B_1=false;
 Auto=false;
 Stop=false;
 F_2=false;
 B_2=false;
 Arm_R=true;
 Arm_L=false;
   }
   else if (c=='e'){
    
 Arm_on=false;
 Arm_off=false;
 Right=false;
 Left=false;
 F_1=false;
 B_1=false;
 Auto=false;
 Stop=false;
 F_2=false;
 B_2=false;
 Arm_R=false;
 Arm_L=true;
   }
    if(Arm_on==true){ 
       do {arm.write(180);
       delay(2000);
       arm.write(90);
       }while (Arm_on==false);
   }
  
    if(Arm_off==true){ 
       do { arm.write(0);
       delay(2000);
       arm.write(90);
       }while(Arm_off==false);
   }
  
    if(Right==true){
    do { head.write(0);
    delay(50);
    head.write(45);
    delay(50);
    head.write(90);
    delay(50);
    }while(Right==false);
  }

      if(Left==true){
   do{ head.write(90);
    delay(50);
    head.write(135);
    delay(50);
    head.write(180);
    delay(50);
   }while(Left==false);
  }

   if(F_1==true){
do{
digitalWrite(in1_1,HIGH);
digitalWrite(in2_1,LOW);
digitalWrite(in3_1,HIGH);
digitalWrite(in4_1,LOW);
}while(F_1==false);
  }

  if(B_1==true){
 do {digitalWrite(in1_1,LOW);
digitalWrite(in2_1,HIGH);
digitalWrite(in3_1,LOW);
digitalWrite(in4_1,HIGH);
 }while(B_1==false);
  }
 
   if(Auto==true){
  for(int i=0;i<4000;i++){
     get_distance_toHC_sr04_for_AutoMode();
  }
  }
   if(Stop==true){
    do {
digitalWrite(in1,LOW);
digitalWrite(in2,LOW);
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);
digitalWrite(in1_1,LOW);
digitalWrite(in2_1,LOW);
digitalWrite(in3_1,LOW);
digitalWrite(in4_1,LOW);
    }while(Stop==false);
  }

    if(F_2==true){
do {digitalWrite(in1,HIGH);
digitalWrite(in2,LOW);
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);
   }while(F_2==false);
  }
  

    if(B_2==true){
 do {digitalWrite(in1,LOW);
digitalWrite(in2,HIGH);
digitalWrite(in3,LOW);
digitalWrite(in4,HIGH); 
}while(B_2==false);
  }


    if(Arm_R==true){ 
   do { 
    arml.write(90);
    delay(50);
    armr.write(180);
    delay(50);
   
   }while(Arm_R==false);
   }

     if(Arm_L==true){ 
   do { 
    arml.write(0);
    delay(50);
    armr.write(90);
    delay(50);
  
   }while(Arm_L==false);
   }
  
 
   }
}

