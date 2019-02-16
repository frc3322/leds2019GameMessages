    #include "FastLED.h"
    #include <Wire.h>
    #define COLOR_ORDER GRB
const int buttonPin1 = 2;
const int buttonPin2 = 8;
long Color = 0;
int ColorRecieve = 0;
int LED = 13;


CRGB blinkBackup[85];
CRGB leds[85];
void setup() { 
  Serial.begin(9600); 
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  FastLED.addLeds<WS2811, 5, COLOR_ORDER>(leds, 85); 
  randomSeed(analogRead(0)); 
  Wire.begin(4); 
  Wire.onReceive(receiveEvent);
   Serial.println(ColorRecieve);
  }

void receiveEvent(int bytes) {
 ColorRecieve = Wire.read();
   Serial.println(ColorRecieve); 

}

int Sense(int InputNum) {
  //Array of lights features alternating direction of lights. This is a fix
  if (InputNum <= 16) {return InputNum;}
  if ((InputNum >=17) and (InputNum <=33)) {return -InputNum + 50;}
  if ((InputNum >=34) and (InputNum <=50)) {return InputNum;}
  if ((InputNum >=51) and (InputNum <=67)) {return -InputNum + 118;}
  if ((InputNum >=68) and (InputNum <=84)) {return InputNum;}
}


void Scroll(long col1, long col2, long col3, long col4, long col5, int stay) {
//Creates a scrolling effect for each induvidual line by moving each light value left one light
//First five inputs are the five new rightmost lights, bottom to top
//Last input is the number of lights, right-to-left, that the scrolling ignores
  for ( int i = 16-stay; i > 0; i--) {
    
    leds[i]=leds[i-1];
    }

  for ( int i = 33-stay; i > 17; i--) {
      
    leds[Sense(i)]=leds[Sense(i-1)];
    }

  for ( int i = 50-stay; i > 34; i--) {
      
    leds[i]=leds[i-1];
    }

  for ( int i = 67-stay; i > 51; i--) {
      
    leds[Sense(i)]=leds[Sense(i-1)];
    }

  for ( int i = 84-stay; i > 68; i--) {
      
    leds[i]=leds[i-1];
    }

  leds[0] = col1;
  leds[Sense(17)] = col2;
  leds[34] = col3;
  leds[Sense(51)] = col4;
  leds[68] = col5; FastLED.show(); delay(250);
}

void Sclorr(long col1, long col2, long col3, long col4, long col5, int stay, int Update=0) {
//Copy-and-paste of scroll() but flipped along the y-axis
//if the name looks weird, it's because the r's and l's in the name were swapped too
//Update will stop fastleds.show from being called, if it is not set to 0
  for ( int i = 0+stay; i < 16; i++) {
    
    leds[i]=leds[i+1];
    }

  for ( int i = 17+stay; i < 33; i++) {
      
    leds[Sense(i)]=leds[Sense(i+1)];
    }

  for ( int i = 34+stay; i < 50; i++) {
      
    leds[i]=leds[i+1];
    }

  for ( int i = 51+stay; i < 67; i++) {
      
    leds[Sense(i)]=leds[Sense(i+1)];
    }

  for ( int i = 68+stay; i < 84; i++) {
      
    leds[i]=leds[i+1];
    }

  leds[16] = col1;
  leds[Sense(33)] = col2;
  leds[50] = col3;
  leds[Sense(67)] = col4;
  leds[84] = col5; 
  
  if (Update == 0) {
  FastLED.show(); delay(250);}

}

void ScrollV(long Col,int Hpos, int Dir) {
//scrolls, but vertically
//Col is the color of the new led, Hpos is the position of the bottommost (or topmost, if going up) light in the column of choice
//Dir is the direction, up or down. 1 or -1
// ex. ScrollV(CRGB::Red,1); Will move all lights in the second-to-the-right column and make the top light of that column red
  for (int i = 0; i<4; i++) {
    leds[Sense(Hpos + (Dir*17*i))] = leds[Sense(Hpos + (17*Dir*(i+1)))];
    }
  leds[Sense(Hpos + Dir*68)] = Col;

}

void SetupBlink() {
//stores the current set of lights that are on in another variable
//recalled during the blink() function
//only needs to be done once if blink() is used multiple times without changing the light configuration
  for ( int i = 0; i < 85; i++) {
    blinkBackup[i] = leds[i];
  }
}


void Blink() {
//flashes black for half a second. Use SetupBlink() first or else it will not work
  for ( int i = 0; i < 85; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show(); delay(500);
    for ( int i = 0; i < 85; i++) {
    leds[i] = blinkBackup[i];
  }
 FastLED.show(); delay(500);  


}

void loop() {
  // put your main code here, to run repeatedly:
/*
leds[3] = CRGB::Red; leds[5] = CRGB::Red; leds[6] = CRGB::Red; leds[7] = CRGB::Red; leds[9] = CRGB::Red; leds[10] = CRGB::Red; leds[11] = CRGB::Red;
leds[13] = CRGB::Red; leds[15] = CRGB::Red; leds[Sense(20)] = CRGB::Red; leds[Sense(24)] = CRGB::Red; leds[Sense(28)] = CRGB::Red; leds[Sense(30)] = CRGB::Red;
leds[Sense(32)] = CRGB::Red; leds[35] = CRGB::Red; leds[36] = CRGB::Red; leds[37] = CRGB::Red; leds[41] = CRGB::Red; leds[43] = CRGB::Red; leds[44] = CRGB::Red;
leds[45] = CRGB::Red; leds[47] = CRGB::Red; leds[48] = CRGB::Red; leds[49] = CRGB::Red; leds[Sense(52)] = CRGB::Red; leds[Sense(54)] = CRGB::Red;
leds[Sense(58)] = CRGB::Red; leds[Sense(62)] = CRGB::Red; leds[Sense(64)] = CRGB::Red; leds[Sense(66)] = CRGB::Red; leds[69] = CRGB::Red; leds[70] = CRGB::Red;
leds[71] = CRGB::Red; leds[75] = CRGB::Red; leds[77] = CRGB::Red; leds[78] = CRGB::Red; leds[79] = CRGB::Red; leds[81] = CRGB::Red; leds[83] = CRGB::Red;

FastLED.show(); delay(10000);
/*leds[0] = CRGB::Red; leds[2] = CRGB::Red; leds[4] = CRGB::Red; leds[5] = CRGB::Red; leds[8] = CRGB::Red; leds[10] = CRGB::Red; leds[12] = CRGB::Red;
leds[14] = CRGB::Red; leds[16] = CRGB::Red; leds[Sense(17)] = CRGB::Red; leds[Sense(19)] = CRGB::Red; leds[Sense(23)] = CRGB::Red; leds[Sense(25)] = CRGB::Red;
leds[Sense(27)] = CRGB::Red; leds[Sense(29)] = CRGB::Red; leds[Sense(31)] = CRGB::Red; leds[Sense(33)] = CRGB::Red; leds[34] = CRGB::Red; leds[35] = CRGB::Red;
leds[36] = CRGB::Red; leds[40] = CRGB::Red; leds[42] = CRGB::Red; leds[44] = CRGB::Red; leds[45] = CRGB::Red; leds[46] = CRGB::Red; leds[48] = CRGB::Red;
leds[49] = CRGB::Red; leds[50] = CRGB::Red; leds[Sense(51)] = CRGB::Red; leds[Sense(53)] = CRGB::Red; leds[Sense(57)] = CRGB::Red; leds[Sense(59)] = CRGB::Red;
leds[Sense(61)] = CRGB::Red; leds[Sense(63)] = CRGB::Red; leds[Sense(65)] = CRGB::Red; leds[Sense(67)] = CRGB::Red; leds[68] = CRGB::Red; leds[70] = CRGB::Red;
leds[72] = CRGB::Red; leds[73] = CRGB::Red; leds[75] = CRGB::Red; leds[76] = CRGB::Red; leds[77] = CRGB::Red; leds[79] = CRGB::Red;  leds[82] = CRGB::Red;
 leds[84] = CRGB::Red;
FastLED.show(); delay(10000);


*/
ScrollV(CRGB::Black,74,-1); ScrollV(CRGB::Black,78,-1);
ScrollV(CRGB::Black,75,-1); ScrollV(CRGB::Black,77,-1);
ScrollV(CRGB::Red,76,-1);
FastLED.show(); delay(100);
ScrollV(CRGB::Black,73,-1); ScrollV(CRGB::Black,79,-1);
ScrollV(CRGB::Black,74,-1); ScrollV(CRGB::Black,78,-1);
ScrollV(CRGB::Red,75,-1); ScrollV(CRGB::Red,77,-1);
ScrollV(0x990000,76,-1);
FastLED.show(); delay(100);
ScrollV(CRGB::Black,73,-1); ScrollV(CRGB::Black,79,-1);
ScrollV(CRGB::Red,74,-1); ScrollV(CRGB::Red,78,-1);
ScrollV(0x990000,75,-1); ScrollV(0x990000,77,-1);
ScrollV(0x440000,76,-1);
FastLED.show(); delay(100);
ScrollV(CRGB::Red,73,-1); ScrollV(CRGB::Red,79,-1);
ScrollV(0x990000,74,-1); ScrollV(0x990000,78,-1);
ScrollV(0x440000,75,-1); ScrollV(0x440000,77,-1);
ScrollV(0x110000,76,-1);
FastLED.show(); delay(100);
ScrollV(0x990000,73,-1); ScrollV(0x990000,79,-1);
ScrollV(0x440000,74,-1); ScrollV(0x440000,78,-1);
ScrollV(0x110000,75,-1); ScrollV(0x110000,77,-1);
ScrollV(0x000000,76,-1);
FastLED.show(); delay(100);
ScrollV(0x440000,73,-1); ScrollV(0x440000,79,-1);
ScrollV(0x110000,74,-1); ScrollV(0x110000,78,-1);
ScrollV(0x000000,75,-1); ScrollV(0x000000,77,-1);
ScrollV(0x000000,76,-1);
FastLED.show(); delay(100);
ScrollV(0x110000,73,-1); ScrollV(0x110000,79,-1); 
}
