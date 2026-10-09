#include <Arduino.h>      
#include <FastLED.h>      
#include <SoftwareSerial.h>
#include "definitions.h"  

CRGB change_color(int i); 

// Memory allocation for LEDs
// CRGB ledsTop[NUM_LEDS_TOP];
// CRGB ledsA[NUM_LEDS_SHORT];
// CRGB ledsB[NUM_LEDS_SHORT];
// CRGB ledsC[NUM_LEDS_SHORT];
// CRGB ledsD[NUM_LEDS_SHORT];

CRGB* shortStrips[] = { ledsA, ledsB, ledsC, ledsD };
const int numShortStrips = 4;

// Set up Software Serial and the DYPlayer instance
// SoftwareSerial audioSerial(AUDIO_RX_PIN, AUDIO_TX_PIN);
// DY::Player player(&audioSerial);

void my_setup() {
  pinMode(builtin_led, OUTPUT);     
  Serial.begin(115200);
  while (!Serial) { ; } // Wait for serial port to connect (needed for some Arduinos)
  Serial.println(F("--- DEBUG SYSTEM ONLINE ---"));

  // Initialize Audio Module
  // audioSerial.begin(9600); // DY-HV20T communicates at 9600 baud rate
  // player.begin();
  // player.setVolume(20);    // Set volume (0 to 30)

  // Initialize LEDs
  FastLED.addLeds<WS2815, PIN_TOP,     GRB>(ledsTop, NUM_LEDS_TOP);
  FastLED.addLeds<WS2815, PIN_STRIP_A, GRB>(ledsA,   NUM_LEDS_SHORT);
  FastLED.addLeds<WS2815, PIN_STRIP_B, GRB>(ledsB,   NUM_LEDS_SHORT);
  FastLED.addLeds<WS2815, PIN_STRIP_C, GRB>(ledsC,   NUM_LEDS_SHORT);
  FastLED.addLeds<WS2815, PIN_STRIP_D, GRB>(ledsD,   NUM_LEDS_SHORT);
  
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();

  // Play the first track on boot up! (00001.mp3)
  // player.playSpecified(1); 
}

void my_loop() {
  int period = 1000;
  digitalWrite(builtin_led, HIGH);  
  Serial.println(F("\n>>> Starting Top Strip Animation..."));
  

  // Top Strip Animation
  for(int i = 0; i < NUM_LEDS_TOP; i++) {
    Serial.print(F("Lighting pixel: "));
    Serial.println(i);
    ledsTop[i] = change_color(i);     
    FastLED.show();           
    delay(30);              
    ledsTop[i] = CRGB::Black;    
  }

  // // Short Strips Animation
  // for(int i = 0; i < NUM_LEDS_SHORT; i++) {
  //   for(int s = 0; s < numShortStrips; s++) {
  //       shortStrips[s][i] = change_color(i);
  //   }
  //   FastLED.show();           
  //   delay(50);                
  //   for(int s = 0; s < numShortStrips; s++) {
  //       shortStrips[s][i] = CRGB::Black;
  //   }
  // }

  delay(period);                
  digitalWrite(builtin_led, LOW);   
}

CRGB change_color(int i) {
    if (i % 2 == 0) {
        return CRGB::Red;
    } else {
        return CRGB::Blue;
    }
} 
