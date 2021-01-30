#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 8

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
#define BUTTON_PIN 13

int buttonState = 0; 

// Define the array of leds
CRGB leds[NUM_LEDS];

// Define initial portal index
int portalIndex = 0;

// Determines next index after shooting portal
int nextPortal[] = {1,0};

// Define portal colors
CHSV portalColors[] = {CHSV(180,255,255),CHSV(78,220,255)};

void setup() { 
  Serial.begin(9600);
  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Initialize LED array
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);

  // set the LED brightness
  // this is a global brightness, applied regardless of what color(s) are shown on the LEDs
  FastLED.setBrightness(255);

  shootPortal();

  
}

void loop() { 
  // read the state of the pushbutton value:
  buttonState = digitalRead(BUTTON_PIN);
  // Show the state of pushbutton on serial monitor
  Serial.println(buttonState);

  if (buttonState == 0) shootPortal();
  
  delay(10);
}

void shootPortal() {
  CHSV newColor = portalColors[portalIndex];

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = newColor;
    FastLED.show();
    delay(30);
  }

  portalIndex = nextPortal[portalIndex];
}
