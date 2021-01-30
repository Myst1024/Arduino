#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 3

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 7

#define BUTTON_PIN 2

// Define the array of leds
CRGB leds[NUM_LEDS];

// Vars
int minBrightness = 50;
int maxBrightness = 250;
int currentBrightness = minBrightness;
int brightnessIncrement = 2;
int nextDelay = 20;
int delayModifier = 7;
int currentMode = 4;
int lastButtonVal = LOW;
bool listenForButton = true;
bool dimming = true;

void setup() { 
  Serial.begin(9600);

  // Initialize LED array
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);

  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

void loop() { 
  if (listenForButton) {
    int buttonVal = digitalRead(BUTTON_PIN);
    if (buttonVal != lastButtonVal) {
      lastButtonVal = buttonVal;
      if (buttonVal == HIGH) {
        digitalWrite(13, LOW);
      } else {
        nextMode();
        digitalWrite(13, HIGH);
    }
    }
   
  }
  
  switch (currentMode) {
    case 0:
      fixedBrightness(0);
      break;
    case 1:
      fixedBrightness(35);
      break;
    case 2:
      fixedBrightness(100);
      break;
    case 3:
      fixedBrightness(240);
      break;
    case 4: 
      breathe();
      break;
  }

  
  setColors();
  delay(nextDelay);
}

void breathe() {
    if (dimming) {
    currentBrightness = currentBrightness - brightnessIncrement;
  } else {
    currentBrightness = currentBrightness + brightnessIncrement;
  }
  if (currentBrightness < minBrightness){
    dimming = false;
  } else if (currentBrightness > maxBrightness) {
    dimming = true;
  }
  nextDelay = (255 - currentBrightness) / delayModifier;
}

void fixedBrightness(int brightness) {
  dimming = true;
  nextDelay = 20;
  currentBrightness = brightness;
}

void setColors() {
  
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(10,255,currentBrightness);
    
  }
  FastLED.show();
}

void nextMode() {
  if (currentMode > 3) {
    currentMode = 0;
  } else {
    currentMode++;
  }
}
