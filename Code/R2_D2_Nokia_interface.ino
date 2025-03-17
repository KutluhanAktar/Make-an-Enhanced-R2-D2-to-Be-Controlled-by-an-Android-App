// R2-D2 Nokia interface 
//
// Following code gives you a menu has three screen and each of screens can be changed with buttons.
//
// Requirements for this:
// Arduino Uno
// A Nokia 5110 LCD Screen                              
// Three buttons                                        
// Two joysticks (or a joystick shield  if you have one)
// A green LED (it is optional and just for fun)      
// Learning LCD5110_Graph.h library (Indeed LCD5110_Basic.h library can be useful as LCD5110_Graph.h library if you do not want to scroll info text)
//
// If the first screen is chosen with pushing the first button, it activates sleeping mode for Nokia 5110 LCD when the counter stops.
// If the second screen is chosen with pushing the second button, it sets up a picture section that occurs pictures you choose.
// If the third screen is chosen with pushing the third button, it gets a menu full of Star Wars characters you choose and allows you to choose each of them with joysticks movements. Then if 
// you want to get info to these characters, you can push joysticks buttons when character has a mark on itself.
// 
// If master Yoda has been chosen on third screen in my interface, a green led is activated until another character or screen is chosen.
//
// All characters and pictures are optional, you can change or add any character and picture you want.
//
// LCD5110_Graph.h library is very useful and easy, you can download it here:
// http://www.rinkydinkelectronics.com/library.php?id=47
//
// And it is for converting your pictures:
// http://www.rinkydinkelectronics.com/t_imageconverter_mono.php
//
// The menu is made with using the volatile boolean system and you can create different combinations by changing the value of joysticks, for instance, using three joysticks or dividing
// screen three parts.
// 
// Connections:
//
//                     Arduino Uno 
//    Nokia 5110 LCD         
//                     -  5V
//                     -  GND
//    SCK              -  Pin 2
//    MOSI             -  Pin 3
//    DC               -  Pin 4
//    RST              -  Pin 5
//    CS               -  Pin 6 
// 
//    Led              -  Pin 10 
//
//    Joystick1 x axis -  Analog Pin 0        
//    Joystick1 y axis -  Analog Pin 1
//    Joystick2 x axis -  Analog Pin 2
//    Joystick2 y axis -  Analog Pin 3
//    Joystick1 SW     -  Pin 7
//    Joystick2 SW     -  Pin 8
//
//    Button1          -  Pin 9 (for opening Screen1)
//    Button2          -  Pin 11(for opening Screen2)
//    Button3          -  Pin 12(for opening Screen3)


#include <LCD5110_Graph.h>
LCD5110 myGLCD(2,3,4,5,6);
const int X_axis1 = A0;
const int Y_axis1 =A1;
const int X_axis2 =A2;
const int Y_axis2 =A3;
const int SW_1 =7;
const int SW_2 =8;
const int screen_1=9;
const int screen_2=11;
const int screen_3=12;
int led=10;
extern uint8_t SmallFont[];
extern uint8_t MediunmFont[];
extern uint8_t BigFont[];
extern uint8_t Batman[];
extern uint8_t Spiderman[];
extern uint8_t starwars[];
extern uint8_t vader[];
extern uint8_t r2_d2[];
extern uint8_t chew[];
extern uint8_t trek[];
volatile boolean up = false;
volatile boolean down = false;
volatile boolean right = false;
volatile boolean left = false;
volatile boolean up_1 = false;
volatile boolean down_1 = false;
volatile boolean right_1 = false;
volatile boolean left_1 = false;


void setup() {

myGLCD.InitLCD();
randomSeed(analogRead(4));
pinMode(screen_1, INPUT);
digitalWrite(screen_1, HIGH);
pinMode(screen_2, INPUT);
digitalWrite(screen_2, HIGH);
pinMode(screen_3, INPUT);
digitalWrite(screen_3, HIGH);
pinMode(SW_1, INPUT);
digitalWrite(SW_1, HIGH);
pinMode(SW_2, INPUT);
digitalWrite(SW_2, HIGH);
pinMode(led, OUTPUT);
}

void loop() {
if(digitalRead(screen_1)==1){
myGLCD.disableSleep();
interface();
joystick1_control();
joystick2_control();
}
if(digitalRead(screen_2)==1){
myGLCD.disableSleep();
pictures_interface();
}
if(digitalRead(screen_3)==1){
sleepingMode();
}
}
void interface(){
  
myGLCD.setFont(SmallFont);
myGLCD.print("Characters :",0,0);
myGLCD.print("Yoda",0,8);
myGLCD.print("Obiwan",0,16);
myGLCD.print("Sidious",0,24);
myGLCD.print("Vader",0,32);
myGLCD.print("Luke",40,8);
myGLCD.print("Leia",40,16);
myGLCD.print("Anakin",40,24);
myGLCD.print("Dooku",40,32);

}
void joystick1_control(){
int x1 = analogRead( X_axis1);
int y1 = analogRead( Y_axis1);
int button1=digitalRead(SW_1);
  
if(x1<300){
  right=true;
  left=false;
  down_1=false;
  up_1=false;
}
else if(x1>600){
  right=false;
  left=true;
  down_1=false;
  up_1=false;
}
 if(left==true){
   if(y1<400){
     down=true;
     up=false;
      }
    else if(y1>600){
     down=false;
     up=true;
      }

        if(up ==true){
          do{
          myGLCD.invertText(true);
          myGLCD.print("Yoda",0,8);
          myGLCD.invertText(false);
          delay(50);
          }while(up==false);
        if(button1==0){
         digitalWrite(led,HIGH);
         ScrollingText_Character("Yoda was the oldest living character  in canon");
        }
        else{
          digitalWrite(led,LOW);
        }
        }
         if(down ==true){
          do{
          myGLCD.invertText(true);
          myGLCD.print("Obiwan",0,16);
          myGLCD.invertText(false);
          delay(50);
          }while(down==false);
        if(button1==0){
         ScrollingText_Character("a mentor to whom he introduces thewaysoftheJedi");
        }
  }
 }
 if(right==true){
    if(y1<400){
    down=true;
    up=false;
    }
    else if(y1>600){
    down=false;
    up=true;
  }

      if(up ==true){
       do{
       myGLCD.invertText(true);
       myGLCD.print("Luke",40,8);
       myGLCD.invertText(false);
       delay(50);
       }while(up==false);
           if(button1==0){
         ScrollingText_Character("The son of fallen Jedi Anakin and Padmé");
        }
      }
        if(down ==true){
         do{
         myGLCD.invertText(true);
         myGLCD.print("Leia",40,16);
         myGLCD.invertText(false);
         delay(50);
         }while(down==false);
          if(button1==0){
         ScrollingText_Character("The daughter of fallen Jedi Anakin and Padmé");
        }
      
      }

     }
  

}

void joystick2_control(){
  int x2 = analogRead( X_axis2);
  int y2 = analogRead( Y_axis2);
  int button2=digitalRead(SW_2);
 if(x2<300){
  right_1=true;
  left_1=false;
  down=false;
  up=false;
  }
  else if(x2>600){
  right_1=false;
  left_1=true;  
  down=false;
  up=false;
  }
   if(left_1==true){
   if(y2<400){
   down_1=true;
   up_1=false;
   down=false;
   up=false;
   }
   else if(y2>600){
   down_1=false;
   up_1=true;
   down=false;
   up=false;
  }

if(up_1 ==true){
     do{
      myGLCD.invertText(true);
      myGLCD.print("Sidious",0,24);
      myGLCD.invertText(false);
      delay(50);
      }while(up_1==false);
         if(button2==0){
         ScrollingText_Character("Outwardly appearing to be supporter of democracy prior");
        }
      
        }
   
if(down_1 ==true){
      do{
       myGLCD.invertText(true);
       myGLCD.print("Vader",0,32);
       myGLCD.invertText(false);
       delay(50);
       }while(down_1==false);
       if(button2==0){
         ScrollingText_Character("The chosen Sith and The fallenJedi,Master,Father");
        }
       
    }
 }
 if(right_1==true){
  if(y2<400){
   down_1=true;
   up_1=false;
 }
  else if(y2>600){
    down_1=false;
    up_1=true;
  }

if(up_1 ==true){
     do{
      myGLCD.invertText(true);
      myGLCD.print("Anakin",40,24);
      myGLCD.invertText(false);
      delay(50);
      }while(up_1==false);
     if(button2==0){
         ScrollingText_Character("The chosen  Jedi,Master,Father");
        }
       
}
   
if(down_1 ==true){
     do{
        myGLCD.invertText(true);
       myGLCD.print("Dooku",40,32);
      myGLCD.invertText(false);
      delay(50);
      }while(down_1==false);
    if(button2==0){
         ScrollingText_Character("Once a respected Jedi Master until he falls ");
        }
      
    }
    }
  
}
void pictures_interface(){
 myGLCD.clrScr();
 myGLCD.drawBitmap(0,0,Spiderman,40,40);
 myGLCD.setFont(SmallFont);
  myGLCD.print("SPIDER",40,0);
  myGLCD.print("MAN",45,8);
  myGLCD.update();
  for (int i=0; i<2; i++)
  {
    myGLCD.invert(true);
    delay(500);
    myGLCD.invert(false);
    delay(500);
  }
   myGLCD.clrScr();
   myGLCD.drawBitmap(0,0,Batman,40,20);
  
 myGLCD.setFont(SmallFont);
  myGLCD.print("BATMAN",40,0);
  myGLCD.update();
  for (int i=0; i<2; i++)
  {
    myGLCD.invert(true);
    delay(500);
    myGLCD.invert(false);
    delay(500);
  }
  myGLCD.clrScr();
  myGLCD.drawBitmap(0,0,starwars,40,24);
  myGLCD.update();
 
  for (int i=0; i<2; i++)
  {
    myGLCD.invert(true);
    delay(500);
    myGLCD.invert(false);
    delay(500);
  }
   myGLCD.clrScr();
    myGLCD.drawBitmap(0,0 ,vader,60,61);
    myGLCD.update();
      for (int i=0; i<2; i++)
  {
    myGLCD.invert(true);
    delay(500);
    myGLCD.invert(false);
    delay(500);
}
 myGLCD.clrScr();
  myGLCD.drawBitmap(0,0,r2_d2,60,60);
  myGLCD.update();
  for (int i=0; i<2; i++)
  {
    myGLCD.invert(true);
    delay(500);
    myGLCD.invert(false);
    delay(500);
  }
   myGLCD.clrScr();
    myGLCD.drawBitmap(0,0,chew,60,60);
    myGLCD.update();
  for (int i=0; i<2; i++)
  {
    myGLCD.invert(true);
    delay(500);
    myGLCD.invert(false);
    delay(500);
  }
   myGLCD.clrScr();
   myGLCD.drawBitmap(0,0,trek,64,60);
   myGLCD.update();
  for (int i=0; i<2; i++)
  {
    myGLCD.invert(true);
    delay(500);
    myGLCD.invert(false);
    delay(500);
  }
   myGLCD.clrScr();
}
void sleepingMode(){
   myGLCD.clrScr();
    myGLCD.setFont(SmallFont);
    myGLCD.print("initializing",0,0);
     myGLCD.print("sleeping mode :",0,8);
      for(int i=0;i<100;i++){
        myGLCD.setFont(SmallFont);
      myGLCD.printNumF(i,CENTER,16,24,"-");
 
    delay(50);
    if(i==99){
      myGLCD.enableSleep();
    }
         myGLCD.update();
      }
}
void ScrollingText_Character(String info){
   myGLCD.clrScr();
  int y = random(0, 0);
  for (int i=84; i>=-(34*6); i--)
  {
   
    myGLCD.print(info, i, y);
    myGLCD.update();
    delay(50);
  }
   myGLCD.clrScr();
}




