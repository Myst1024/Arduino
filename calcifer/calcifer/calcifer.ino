#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 4

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 7
#define BUTTON_PIN 13

int buttonState = 0; 
int hueMin = 20;
int hueMax = 55;
int hueDiff = 0;
int currentHue = 40;
int currentBrightness = 127;

int lowerWeight = 0;
int upperWeight = 0;
int weightCalc = 0;

// Define the array of leds
CRGB leds[NUM_LEDS];


// Define portal colors
CHSV newColor = CHSV(65,255,255);

void setup() { 
  Serial.begin(9600);

  // Initialize LED array
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  // set the LED brightness
  // this is a global brightness, applied regardless of what color(s) are shown on the LEDs
  FastLED.setBrightness(255);
  leds[1] = CHSV(40,255,255);
  
}

void loop() { 
  lowerWeight = hueMin - currentHue;
  upperWeight = hueMax - currentHue;
  weightCalc = random(lowerWeight, upperWeight);
  if (weightCalc > 0) {
    currentHue += 1;
    currentBrightness += 3;
  } else {
    currentHue -= 1;
    currentBrightness -= 3;
  }
  leds[random(4)] = CHSV(currentHue,255,currentBrightness);
  // setColors();
      FastLED.show();

  delay(70);
}

void setColors() {
  
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[0, 2] = CHSV(currentHue,255,255);
    FastLED.show();
  }
}
