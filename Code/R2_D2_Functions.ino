// R2-D2 Functions 
// This part of the project is about to receive data accurately from an app which provides collaboration between an Android phone and Arduino Uno is called R2-D2.
// Each of choices on Functions Screen which is the second screen on the app transmits a char from Android phone to a compatible Bluetooth module with Arduino such as HC-O6.
// Using the volatile boolean system makes it easy while transmitting data for controlling R2-D2 replica.
// 
// Requirements for this:
//
// A breadboard and a mini breadboard
// Arduino Uno
// A HC-06 bluetooth module(or HC-05)
// A 74HC595 shift register
// A 4 way relay
// A buzzer
// A RGB Led(common anode)
// A MG996R Servo Motor(or any Servo Motor)
// Learning Servo library
// Learning SoftwareSerial library
// Optional;
// A Fan(which works with 220V)
// A Plasma Globe(which works with 220V)
// A Bulb(which works with 220V)   
//
//
// 
// First of all, you have to change HC-06 module name to "Functions" with AT commands for proceeding app with accurate data.
//
// 74HC595 shift register gives you 8 output for 8 leds with 3 pins which controlled with "shiftOut()" and allows you obtain each of led with bytes.
// You can learn connections and pin names if you do not know on here:
// https://learn.adafruit.com/adafruit-arduino-lesson-4-eight-leds/the-74hc595-shift-register
//   
// Every note has a unique frequency value and through the range of buzzer frequency you can play whatever song you want.
// My searching suggests that Tone() and noTone() are the best choices for this project.
// Letter notes frequency list:
// A = 440;
// A_=466;
// B =494;
// C=523;
// C_=554;
// D = 622;
// D_=622;
// E = 659;
// F = 698;
// F_=740;
// G = 784;
// G_=830;
// I added Imperial March and Star Wars Main Theme. If you want to change them, you can find another song you like  easily on here:
// http://www.letternoteplayer.com/
// 
// 4 way relay is used for controlling with Arduino pins up to 4 object. Choosing object deoend on your replica's sizes.
// 
// RGB LED is an adjustable LED with PWM(pulse width modulation) pins to change color is chosen. Blue, red and green are options I used in my replica.
//
// MG996R Servo Motor is for giving the rotary motion to bulb.
//
// Connections:
//
//                         Arduino Uno
// HC-06 module
// RX               -  Pin 12
// TX               -  Pin 11
// VCC              -  5V
// GND              -  GND    
// 74HC595 Shift Register
// LatchPin         -  Pin 2
// DataPin          -  Pin 4
// ClockPin         -  Pin 13
// RGB Led     
//                  -  Pin 3(pwm)
//                  -  5V  
//                  -  Pin 5(pwm)
//                  -  Pin 6(pwm)
// BuzzerPin        -  Analog Pin 0
// 4 Way relay 
// In1              -  Pin 8
// In2              -  Pin 9
// In3              -  Pin 7
// Servo
// ServoPin         -  Pin 10   

#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial Functions(11,12);// RX | TX
Servo bulb;

volatile boolean Active=false;
volatile boolean Inactive=false;
volatile boolean Blue=false;
volatile boolean Green=false;
volatile boolean Red=false;
volatile boolean Buzzer=false;
volatile boolean Bulb=false;
volatile boolean Plasma_Globe=false;
volatile boolean Fan=false;
volatile boolean Off=false;
volatile boolean Bulb_R=false;
volatile boolean Bulb_L=false;

char c;

const int latch=2;
const int data=4;
const int clocK=13;

const int rgb1=3;
const int rgb2=5;
const int rgb3=6;

const int in1=8;
const int in2=9;
const int in3=7;

const int buzzerPin = A0;
const int Imperial_notes = 60;
const int Main_notes=60;

const int A = 440;
const int A_=466;
const int B =494;
const int C=523;
const int C_=554;
const int D = 622;
const int D_=622;
const int E = 659;
const int F = 698;
const int F_=740;
const int G = 784;
const int G_=830;

byte leds=0;
 
int Imperial_March[] = {A,A,A,F,C,A,F,C,A,
E,E,E,F,C,G_, F,C,A,
A,A,A,A,G_,G,F_,F,F_,
A_,D_,D,C_,C,B,C,
F,G_,F_,G,C,A,C,E,
A,A,A,A,G_,G,F_,F,F_,
A_,D_,D,C_,C,B,C,
F,G_,F_,C,A,F,C,A};
int Main_theme[]={G ,D ,C ,B ,A ,D ,C ,B,A, D,
C, B, C, A, D, D, G, D,
C, B, A, D ,C, B, A, D, C, B, C, A, D, D, E,
E, E, C, B, A, G, G, A, B, A, E, F_, D, D, E,
E, C, B, A, G, D, A, D, D};

void setup() {
 bulb.attach(10);
 Serial.begin(9600);
 Functions.begin(9600);
 
  pinMode(buzzerPin, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(data, OUTPUT);  
  pinMode(clocK, OUTPUT);
  pinMode(rgb1, OUTPUT);
  pinMode(rgb2, OUTPUT);  
  pinMode(rgb3, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);  
  pinMode(in3, OUTPUT);
   digitalWrite(in1,HIGH);
   digitalWrite(in2,HIGH);
   digitalWrite(in3,HIGH); 
}

void loop() {
Functions_Control();
}


void Functions_Control(){
  if(Functions.available()){
     c=Functions.read();
    Serial.print(c);
    
if(c=='2'){
Active=true;
Inactive=false;
Blue=false;
Green=false;
Red=false;
Buzzer=false;
Bulb=false;
Plasma_Globe=false;
Fan=false;
Off=false;
Bulb_R=false;
Bulb_L=false;
     }
else if(c=='3'){
Active=false;
Inactive=true;
Blue=false;
Green=false;
Red=false;
Buzzer=false;
Bulb=false;
Plasma_Globe=false;
Fan=false;
Off=false;
Bulb_R=false;
Bulb_L=false;
     }
else if(c=='4'){
Active=false;
Inactive=false;
Blue=true;
Green=false;
Red=false;
Buzzer=false;
Bulb=false;
Plasma_Globe=false;
Fan=false;
Off=false;
Bulb_R=false;
Bulb_L=false;
     }
else if(c=='5'){
Active=false;
Inactive=false;
Blue=false;
Green=true;
Red=false;
Buzzer=false;
Bulb=false;
Plasma_Globe=false;
Fan=false;
Off=false;
Bulb_R=false;
Bulb_L=false;     
}
else if(c=='6'){
Active=false;
Inactive=false;
Blue=false;
Green=false;
Red=true;
Buzzer=false;
Bulb=false;
Plasma_Globe=false;
Fan=false;
Off=false;
Bulb_R=false;
Bulb_L=false;
     }
else if(c=='7'){
Active=false;
Inactive=false;
Blue=false;
Green=false;
Red=false;
Buzzer=true;
Bulb=false;
Plasma_Globe=false;
Fan=false;
Off=false;
Bulb_R=false;
Bulb_L=false;
     }
else if(c=='8'){
Active=false;
Inactive=false;
Blue=false;
Green=false;
Red=false;
Buzzer=false;
Bulb=true;
Plasma_Globe=false;
Fan=false;
Off=false;
Bulb_R=false;
Bulb_L=false;
     }
else if(c=='9'){
Active=false;
Inactive=false;
Blue=false;
Green=false;
Red=false;
Buzzer=false;
Bulb=false;
Plasma_Globe=true;
Fan=false;
Off=false;
Bulb_R=false;
Bulb_L=false;
     }
else if(c=='a'){
Active=false;
Inactive=false;
Blue=false;
Green=false;
Red=false;
Buzzer=false;
Bulb=false;
Plasma_Globe=false;
Fan=true;
Off=false;
Bulb_R=false;
Bulb_L=false;
     }
else if(c=='b'){
Active=false;
Inactive=false;
Blue=false;
Green=false;
Red=false;
Buzzer=false;
Bulb=false;
Plasma_Globe=false;
Fan=false;
Off=true;
Bulb_R=false;
Bulb_L=false;
     }
else if(c=='d'){
 Active=false;
 Inactive=false;
 Blue=false;
 Green=false;
 Red=false;
 Buzzer=false;
 Bulb=false;
 Plasma_Globe=false;
 Fan=false;
 Off=false;
 Bulb_R=true;
 Bulb_L=false;
     }
else if(c=='e'){
 Active=false;
 Inactive=false;
 Blue=false;
 Green=false;
 Red=false;
 Buzzer=false;
 Bulb=false;
 Plasma_Globe=false;
 Fan=false;
 Off=false;
 Bulb_R=false;
 Bulb_L=true;
     }
     if(Active==true){
  knightr();
     }
     
      if(Inactive==true){
   knightl();
     }
     if(Buzzer==true){
       play();
     }
     if(Blue==true){
       analogWrite(rgb1, 255);
       analogWrite(rgb2, 255);
       analogWrite(rgb3, 0);
      
     }
     if(Green==true){
       analogWrite(rgb1, 255);
       analogWrite(rgb2 ,0);
       analogWrite(rgb3, 255);
      
     }
     if(Red==true){
       analogWrite(rgb1, 0);
       analogWrite(rgb2, 255);
       analogWrite(rgb3, 255);
     }
     if(Bulb==true){
      digitalWrite(in1,LOW);
     }
       if(Plasma_Globe==true){
      digitalWrite(in2,LOW);
     }
       if(Fan==true){
      digitalWrite(in3,LOW);
     }
       if(Off==true){
      digitalWrite(in1,HIGH);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,HIGH); 
      analogWrite(rgb1, 255);
      analogWrite(rgb2, 255);
      analogWrite(rgb3, 255);
     }
     if(Bulb_R==true){
    do { bulb.write(0);
    delay(50);
    bulb.write(45);
    delay(50);
    bulb.write(90);
    delay(50);}while(Bulb_R==false);
     }
     if(Bulb_L==true){
    do { bulb.write(90);
    delay(50);
    bulb.write(135);
    delay(50);
    bulb.write(180);
    delay(50);}while(Bulb_L==false);
     }


}
}
void knightr(){
  for (int i = 0; i < 8; i++)
  {
    bitSet(leds, i);
    digitalWrite(latch, LOW);
   shiftOut(data, clocK, LSBFIRST, leds);
   digitalWrite(latch, HIGH);
    delay(50);
  }
  for (int i = 8; i >= 0; i--)
{
    bitClear(leds, i);
    digitalWrite(latch, LOW);
   shiftOut(data, clocK, MSBFIRST, leds);
   digitalWrite(latch, HIGH);
    delay(50);
  }
}
void knightl(){
  for (int i = 0; i < 8; i++)
  {
    bitSet(leds, i);
    digitalWrite(latch, LOW);
   shiftOut(data, clocK, MSBFIRST, leds);
   digitalWrite(latch, HIGH);
    delay(50);
  }
  for (int i = 8; i >= 0; i--)
{
    bitClear(leds, i);
    digitalWrite(latch, LOW);
   shiftOut(data, clocK, LSBFIRST, leds);
   digitalWrite(latch, HIGH);
    delay(50);
  }
}

void play(){
  for (int i = 0; i < Imperial_notes; i++)
  {
    tone(buzzerPin, Imperial_March[i]);
    delay(500);
    noTone(buzzerPin);
    delay(20);
  }
  noTone(buzzerPin);
     
      for (int i = 0; i < Main_notes; i++)
  {
    tone(buzzerPin, Main_theme[i]);
    delay(500);
    noTone(buzzerPin);
    delay(20);
  }
  noTone(buzzerPin);
}


