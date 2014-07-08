/*
  Copyright: iTapArcade, Inc.
  Twitter: @iTapArcade
  Website: itaparcade.com 
  Date: February 4, 2014
  Last Modified: July 6, 2014
  Code: Mouse, Keyboard, and Gamepad Emulation Code based on Cade-Shield (USB)
  Controller: Teensy 2.0
  Revision: 1.0
  6 Modes of Operation:  Last 3 Modes are Joystick Only Modes
  */
  
#include <Bounce.h>
#include <EEPROM.h>

int led = 11;
int powerled = 6;
int trigger = 10;
int joyup1switch = 13;
int joydown2switch = 12;
int joyright4switch = 14;
int joyleft3switch = 15;
int red5switch = 10;
int red6switch = 9;
int black7switch = 4;
int black8switch = 3;
int black9switch = 5;
int black0switch = 1;
int whiteE1switch = 0;
int whiteE2switch = 2;
int count = 1;
int moveup = 0;
int movedown = 0;
int moveright = 0;
int moveleft = 0;
int stepsize = 5;
int addr = 0;
int modecount = 4;
int controllermode = '4';
long previousMillis = 0; 
long interval = 10;           // interval at which to send keyboard updates and mouse movements (milliseconds)
long debounceinterval = 5;


Bounce button0 = Bounce(red5switch, debounceinterval);
Bounce button1 = Bounce(joyup1switch,debounceinterval+5);
Bounce button2 = Bounce(joydown2switch,debounceinterval+5);
Bounce button3 = Bounce(joyright4switch,debounceinterval+5);
Bounce button4 = Bounce(joyleft3switch,debounceinterval+5);
Bounce button5 = Bounce(red6switch,debounceinterval);
Bounce button6 = Bounce(black7switch,debounceinterval);
Bounce button7 = Bounce(black8switch,debounceinterval);
Bounce button8 = Bounce(black9switch,debounceinterval);
Bounce button9 = Bounce(black0switch,debounceinterval);
Bounce button10 = Bounce(whiteE2switch,debounceinterval);
Bounce button11 = Bounce(whiteE1switch,debounceinterval);

// the setup routine runs once when you press reset:
void setup() { 
  //
  delay(1000);
  
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);  
  pinMode(powerled, OUTPUT);
  pinMode(red5switch, INPUT_PULLUP);  
  pinMode(joyup1switch, INPUT_PULLUP); 
  pinMode(joydown2switch, INPUT_PULLUP); 
   pinMode(joyright4switch, INPUT_PULLUP); 
  pinMode(joyleft3switch, INPUT_PULLUP); 
  pinMode(trigger, INPUT_PULLUP); 
  pinMode(red6switch, INPUT_PULLUP); 
  pinMode(black7switch, INPUT_PULLUP);
  pinMode(black8switch, INPUT_PULLUP);
  pinMode(black9switch, INPUT_PULLUP);
  pinMode(black0switch, INPUT_PULLUP);
  pinMode(whiteE1switch, INPUT_PULLUP);
  pinMode(whiteE2switch, INPUT_PULLUP);
  
  Keyboard.begin();
  
   // initialize control over the mouse:
  Mouse.begin();
  Mouse.release(MOUSE_LEFT);
  
  Joystick.button(1, 0);
  Joystick.button(2, 0);
  Joystick.button(3, 0);
  Joystick.button(4, 0);
  Joystick.button(5, 0);
  Joystick.button(6, 0);
  Joystick.button(7, 0);
  Joystick.button(8, 0);
  Joystick.button(9, 0);
  Joystick.button(10, 0);
  Joystick.button(11, 0);
  Joystick.button(12, 0);
  Joystick.button(13, 0);
  Joystick.button(14, 0);
  Joystick.X(512);
  Joystick.Y(512);
  Joystick.Z(512);
  
  if(modecount == 0) modecount = modecount + 1;
  
  if(digitalRead(joyup1switch)){
    
  modecount = 4;
  controllermode = '4';
  
  }else
  {
  modecount = 1;
  controllermode = '1';  
  
  }
  
       if (modecount == 1)
    { controllermode = '1';
    digitalWrite(powerled, HIGH); 
    delay(250);
    digitalWrite(powerled, LOW);
    }
     if (modecount == 2) {
       controllermode = '2';
    digitalWrite(powerled, HIGH); 
    delay(250);
    digitalWrite(powerled, LOW);
    delay(250);
    digitalWrite(powerled, HIGH); 
    delay(250);
    digitalWrite(powerled, LOW);
     }
     if (modecount == 3) {
       controllermode = '3';
    digitalWrite(powerled, HIGH); 
    delay(250);
    digitalWrite(powerled, LOW);
   delay(250);
    digitalWrite(powerled, HIGH); 
   delay(250);
    digitalWrite(powerled, LOW); 
   delay(250);
    digitalWrite(powerled, HIGH); 
   delay(250);
    digitalWrite(powerled, LOW);
    modecount = 0;
     }
     if (modecount == 4) {
       controllermode = '4';
          digitalWrite(powerled, HIGH); 
    delay(250);
    digitalWrite(powerled, LOW);
     }
          if (modecount == 5) {
       controllermode = '5';
    digitalWrite(powerled, HIGH); 
   delay(250);
    digitalWrite(powerled, LOW);
    delay(250);
    digitalWrite(powerled, HIGH); 
   delay(250);
    digitalWrite(powerled, LOW);
     }
       if (modecount == 6) {
       controllermode = '6';
    digitalWrite(powerled, HIGH); 
    delay(250);
    digitalWrite(powerled, LOW);
    delay(250);
    digitalWrite(powerled, HIGH); 
    delay(250);
    digitalWrite(powerled, LOW); 
    delay(250);
    digitalWrite(powerled, HIGH); 
    delay(250);
    digitalWrite(powerled, LOW);
    modecount = 3;
     }
}



// the loop routine runs over and over again forever:

void loop() {
 
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis; 
    
    if(modecount < 4)
    {
    if(moveup)
    {
        Mouse.move(0,-stepsize); 
    }else if(movedown)
    {
        Mouse.move(0,stepsize); 
    } else if(moveleft)
    {
        Mouse.move(-stepsize,0); 
    } else if(moveright)
    {
        Mouse.move(stepsize,0); 
    } 
    Keyboard.send_now();
    }
   
  }
  
  
  
button1.update();  // joyup1switch
   if (button1.fallingEdge()) {
     switch (controllermode) {
    case '1':
    moveup = 1; 
    break;
    case '2':
    Keyboard.set_key2(KEY_UP);
    break;
    case '3':
    moveup = 1;
    break;
    case '4':
    Joystick.button(9, 1);
    break;
    case '5':
    Joystick.Y(24);
    break;
    case '6':
    Joystick.Z(24);
    break;
    }
    digitalWrite(powerled, HIGH); 
   } 
      if (button1.risingEdge()) {
      switch (controllermode) {
    case '1':
    moveup = 0;
    break;
    case '2':
    Keyboard.set_key2(0); 
    break;
    case '3':
    moveup = 0;
    break;
    case '4':
    Joystick.button(9, 0);
    break;
    case '5':
    Joystick.Y(512);
    break;
    case '6':
    Joystick.Z(512);
    break;
    }     
    digitalWrite(powerled, LOW); 
      } 
      
   button2.update();  //joydown2switch
   if (button2.fallingEdge()) {
   switch (controllermode) {
    case '1':
    movedown = 1;      
    break;
    case '2':
    Keyboard.set_key3(KEY_DOWN);
    break;
    case '3':
    movedown = 1;
    break;
    case '4':
    Joystick.button(10, 1);
    break;
    case '5':
    Joystick.Y(1000);
    break;
    case '6':
    Joystick.Z(1000);
    break;
    }    
    digitalWrite(powerled, HIGH); 
   }
   
      if (button2.risingEdge()) {
    switch (controllermode) {
    case '1':
    movedown = 0;
    break;
    case '2':
    Keyboard.set_key3(0);
    break;
    case '3':
    movedown = 0;
    break;
    case '4':
    Joystick.button(10, 0);
    break;
    case '5':
    Joystick.Y(512);
    break;
    case '6':
    Joystick.Z(512);
    break;
    }    
    digitalWrite(powerled, LOW); 
   } 
      
    button3.update();  //joyright4switch
   if (button3.fallingEdge()) {
   switch (controllermode) {
    case '1':
    moveright = 1;
    break;
    case '2':
    Keyboard.set_key4(KEY_RIGHT);
    break;
    case '3':
    moveright = 1;
    break;
    case '4':
    Joystick.button(12, 1);
    break;
    case '5':
    Joystick.X(1000);
    break;    
    case '6':
    Joystick.Zrotate(1000);
    break;
    }      
    digitalWrite(powerled, HIGH); 
    } 
    if (button3.risingEdge()) {
    switch (controllermode) {
    case '1':
    moveright = 0;
    break;
    case '2':
    Keyboard.set_key4(0);
    break;
    case '3':
    moveright = 0; 
    break;
    case '4':
    Joystick.button(12, 0);
    break;
    case '5':
    Joystick.X(512);
    break;    
    case '6':
    Joystick.Zrotate(512);
    break;
    }  
    digitalWrite(powerled, LOW);
   } 
      
    button4.update();  //joyleft3switch
   if (button4.fallingEdge()) {
   switch (controllermode) {
    case '1':
    moveleft = 1;   
    break;
    case '2':
    Keyboard.set_key1(KEY_LEFT);
    break;
    case '3':
    moveleft = 1;
    break;
    case '4':
    Joystick.button(11, 1);
    break;
    case '5':
    Joystick.X(24);
    break;
    case '6':
    Joystick.Zrotate(24);
    break;
    }    
    digitalWrite(powerled, HIGH); 
    }
    if (button4.risingEdge()) {
    switch (controllermode) {
    case '1':
    moveleft = 0;
    break;
    case '2':
    Keyboard.set_key1(0);
    break;
    case '3':
    moveleft = 0;
    break;
    case '4':
    Joystick.button(11, 0);
    break;
    case '5':
    Joystick.X(512);
    break;
    case '6':
    Joystick.Zrotate(512);
    break;
    }      
    digitalWrite(powerled, LOW); 
    } 
      
    button0.update();  //red5switch
  if (button0.fallingEdge()) {
    switch (controllermode) {
    case '1':
    Mouse.press(MOUSE_LEFT); 
    break;
    case '2':
    Keyboard.set_key1(KEY_LEFT);
    break;
    case '3':
    Keyboard.set_key1(KEY_LEFT);
    break;
    case '4':
    Joystick.button(5, 1);
    break;
    case '5':
    Joystick.button(13, 1);
    break;
    case '6':
    Joystick.button(7, 1);
    break;
    } 
     digitalWrite(powerled, HIGH); 
  }
  
   if (button0.risingEdge()) {
      switch (controllermode) {
    case '1':
    Mouse.release(MOUSE_LEFT); 
    break;
    case '2':
    Keyboard.set_key1(0);
    break;
    case '3':
    Keyboard.set_key1(0);
    break;
    case '4':
    Joystick.button(5, 0);
    break;
    case '5':
    Joystick.button(13, 0);
    break;
    case '6':
    Joystick.button(7, 0);
    break;
    } 
     digitalWrite(powerled, LOW); 
  }  
      
      
   button5.update();  //red6switch
   if (button5.fallingEdge()) {
   switch (controllermode) {
    case '1':
    Mouse.press(MOUSE_LEFT);  
    break;
    case '2':
    Keyboard.set_key5(KEY_SPACE);
    break;
    case '3':
    Mouse.press(MOUSE_LEFT);
    break;
    case '4':
    Joystick.button(15, 1);
    break;
    case '5':
    Joystick.button(15, 1);
    break;
    case '6':
    Joystick.button(15, 1);
    break;
    }   
     digitalWrite(powerled, HIGH); 
      } 
      if (button5.risingEdge()) {
    switch (controllermode) {
    case '1':
    Mouse.release(MOUSE_LEFT);
    break;
    case '2':
    Keyboard.set_key5(0);
    break;
    case '3':
    Mouse.release(MOUSE_LEFT);
    break;
    case '4':
    Joystick.button(15, 0);
    break;
    case '5':
    Joystick.button(15, 0);
    break;
    case '6':
    Joystick.button(15, 0);
    break;
    }          
    digitalWrite(powerled, LOW); 
     } 
      
   button6.update();  // black7switch
   if (button6.fallingEdge()) {
    switch (controllermode) {
    case '1':
    Mouse.press(MOUSE_LEFT);  
    break;
    case '2':
    Keyboard.set_key2(KEY_DOWN);
    break;
    case '3':
    Keyboard.set_key2(KEY_UP);
    break;
    case '4':
    Joystick.button(3, 1);
    break;
    case '5':
    Joystick.button(3, 1);
    break;
    case '6':
    Joystick.button(3, 1);
    break;
    }     
         digitalWrite(powerled, HIGH); 
      } 
      if (button6.risingEdge()) {
       switch (controllermode) {
    case '1':
    Mouse.release(MOUSE_LEFT); 
    break;
    case '2':
    Keyboard.set_key2(0);
    break;
    case '3':
    Keyboard.set_key2(0);
    break;
    case '4':
    Joystick.button(3, 0);
    break;
    case '5':
    Joystick.button(3, 0);
    break;
    case '6':
    Joystick.button(3, 0);
    break;
    }       
    digitalWrite(powerled, LOW); 
      } 
      
   button7.update();  //black8switch
   if (button7.fallingEdge()) {
     
    switch (controllermode) {
    case '1':
    Mouse.press(MOUSE_LEFT);   
    break;
    case '2':
    Keyboard.set_key5(KEY_Z);
    break;
    case '3':
    Keyboard.set_key5(KEY_Z);
    break;
    case '4':
    Joystick.button(1, 1);
    break;
    case '5':
    Joystick.button(1, 1);
    break;
    case '6':
    Joystick.button(1, 1);
    break;
    }      
    digitalWrite(powerled, HIGH); 
      } 
      if (button7.risingEdge()) {
        
    switch (controllermode) {
    case '1':
    Mouse.release(MOUSE_LEFT); 
    break;
    case '2':
    Keyboard.set_key5(0);
    break;
    case '3':
    Keyboard.set_key5(0);
    break;
    case '4':
    Joystick.button(1, 0);
    break;
    case '5':
    Joystick.button(1, 0);
    break;
    case '6':
    Joystick.button(1, 0);
    break;
    }   
    digitalWrite(powerled, LOW); 
    } 
      
   button8.update(); //black9switch
   if (button8.fallingEdge()) {
    switch (controllermode) {
    case '1':
    Mouse.press(MOUSE_RIGHT);    
    break;
    case '2':
    Keyboard.set_key3(KEY_UP);
    break;
    case '3':
    Keyboard.set_key3(KEY_DOWN);
    break;
    case '4':
    Joystick.button(4, 1);
    break;
    case '5':
    Joystick.button(4, 1);
    break;
    case '6':
    Joystick.button(4, 1);
    break;
    }      
         digitalWrite(powerled, HIGH); 
      } 
      if (button8.risingEdge()) {
       switch (controllermode) {
    case '1':
    Mouse.release(MOUSE_RIGHT); 
    break;
    case '2':
    Keyboard.set_key3(0);
    break;
    case '3':
    Keyboard.set_key3(0);
    break;
    case '4':
    Joystick.button(4, 0);
    break;
    case '5':
    Joystick.button(4, 0);
    break;
    case '6':
    Joystick.button(4, 0);
    break;
    }  
    digitalWrite(powerled, LOW); 
   } 
      
     button9.update();  // black0switch
   if (button9.fallingEdge()) {
   switch (controllermode) {
    case '1':
    Mouse.press(MOUSE_RIGHT);    
    break;
    case '2':
    Keyboard.set_key6(KEY_X);
    break;
    case '3':
    Keyboard.set_key6(KEY_X);
    break;
    case '4':
    Joystick.button(2, 1);
    break;
    case '5':
    Joystick.button(2, 1);
    break;
    case '6':
    Joystick.button(2, 1);
    break;
    }       
    digitalWrite(powerled, HIGH); 
      } 
      if (button9.risingEdge()) {
     switch (controllermode) {
    case '1':
    Mouse.release(MOUSE_RIGHT); 
    break;
    case '2':
    Keyboard.set_key6(0);
    break;
    case '3':
    Keyboard.set_key6(0);
    break;
    case '4':
    Joystick.button(2, 0);
    break;
    case '5':
    Joystick.button(2, 0);
    break;
    case '6':
    Joystick.button(2, 0);
    break;
    }          
    digitalWrite(powerled, LOW); 
    } 
      
  button10.update();  //whiteE2switch
   if (button10.fallingEdge()) {
     
     modecount = modecount + 1;
     
     if (modecount == 1)
    { controllermode = '1';
    digitalWrite(powerled, HIGH); 
    delay(250);
    digitalWrite(powerled, LOW);
    EEPROM.write(addr, modecount);
    }
     if (modecount == 2) {
       controllermode = '2';
    digitalWrite(powerled, HIGH); 
    delay(250);
    digitalWrite(powerled, LOW);
    delay(250);
    digitalWrite(powerled, HIGH); 
    delay(250);
    digitalWrite(powerled, LOW);
    EEPROM.write(addr, modecount);
     }
     if (modecount == 3) {
       controllermode = '3';
    digitalWrite(powerled, HIGH); 
    delay(250);
    digitalWrite(powerled, LOW);
    delay(250);
    digitalWrite(powerled, HIGH); 
    delay(250);
    digitalWrite(powerled, LOW); 
    delay(250);
    digitalWrite(powerled, HIGH); 
    delay(250);
    digitalWrite(powerled, LOW); 
    modecount = 0;
   EEPROM.write(addr, modecount);
     }
     if (modecount == 4) {
       controllermode = '4';
    digitalWrite(powerled, HIGH); 
    delay(250);
    digitalWrite(powerled, LOW);
   EEPROM.write(addr, modecount);
     }
 if(modecount == 5) {
          controllermode = '5';
    digitalWrite(powerled, HIGH); 
    delay(250);
    digitalWrite(powerled, LOW);
    delay(250);
    digitalWrite(powerled, HIGH); 
    delay(250);
    digitalWrite(powerled, LOW);
    EEPROM.write(addr, modecount);
 }
 if(modecount == 6) {
       controllermode = '6';
    digitalWrite(powerled, HIGH); 
    delay(250);
    digitalWrite(powerled, LOW);
    delay(250);
    digitalWrite(powerled, HIGH); 
    delay(250);
    digitalWrite(powerled, LOW); 
    delay(250);
    digitalWrite(powerled, HIGH); 
    delay(250);
    digitalWrite(powerled, LOW); 
    modecount = 3;
    EEPROM.write(addr, modecount);
 }
  
     } 
     if (button10.risingEdge()) {
   
      } 
      
  button11.update();   //whiteE1switch
   if (button11.fallingEdge()) {
     switch (controllermode) {
    case '1':
    Mouse.press(MOUSE_RIGHT);   
    break;
    case '2':
    Keyboard.set_key4(KEY_RIGHT);
    break;
    case '3':
    Keyboard.set_key4(KEY_RIGHT);    
    break;
    case '4':
    Joystick.button(6, 1);
    break;
    case '5':
    Joystick.button(14, 1);
    break;
    case '6':
    Joystick.button(8, 1);
    break;
    }     
    digitalWrite(powerled, HIGH); 
    } 
      if (button11.risingEdge()) {
       switch (controllermode) {
    case '1':
    Mouse.release(MOUSE_RIGHT); 
    break;
    case '2':
    Keyboard.set_key4(0);
    break;
    case '3':
    Keyboard.set_key4(0);      
    break;
    case '4':
    Joystick.button(6, 0);
    break;
    case '5':
    Joystick.button(14, 0);
    break;
    case '6':
    Joystick.button(8, 0);
    break;
    }      
    digitalWrite(powerled, LOW); 
      } 
}
