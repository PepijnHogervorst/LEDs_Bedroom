/************************************************************************/
/*                               INCLUDES                               */
/************************************************************************/
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                             DEFINITIONS                              */
/************************************************************************/
// If DEBUG is defined (uncommented)the arduino will do a RGB loop through every LED_GROUP
#define DEBUG

#define LEDSTRIP_PIN          5
#define NUMPIXELS             225       
#define BRIGHTNESS            230               
/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                               GLOBAL VARIABLES                       */
/************************************************************************/
Adafruit_NeoPixel led_strip;
//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDSTRIP_PIN, NEO_GRB + NEO_KHZ800);

char inChar = 0;
const int led = 2;
String inputString = "";         // a String to hold incoming data from serial terminal
boolean stringComplete = false;  // whether the string is complete


bool ledState = false;

uint8_t brightness = BRIGHTNESS;
char cBrightness[4];
uint32_t color = led_strip.Color(255, 240, 0);
char cColor[14];
/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                             PROTOTYPES                               */
/************************************************************************/
void ClearLEDstrips(void);
void setColor(uint32_t _color);
void ColorWipe(uint32_t color, int delayTime);
uint32_t Wheel(byte WheelPos);
/************************************************************************/
/*                                                                      */
/************************************************************************/

void setup() 
{
  // Serial communication setup
  Serial.begin(115200);

  // Startup delay to let power supply stabilize
  delay(3000);

  //Setup of the LED strip 
  led_strip = Adafruit_NeoPixel(NUMPIXELS, LEDSTRIP_PIN, NEO_RGB  + NEO_KHZ800);
  led_strip.setBrightness(BRIGHTNESS);
  // Clear 
  led_strip.begin();
  led_strip.show();

  #ifdef DEBUG 
  Serial.println("Debug mode active!");
  #endif

  Serial.println("Initialization done!");
}

void loop() {
#ifndef DEBUG

#else
  // Debug loop for testing RGBW
  ColorWipe(led_strip.Color(255, 0, 0), 50); // Red
  ColorWipe(led_strip.Color(0, 255, 0), 50); // Green
  ColorWipe(led_strip.Color(0, 0, 255), 50); // Blue
  ColorWipe(led_strip.Color(0, 0, 0, 255), 50); // White
#endif
}


void ClearLEDstrips()
{
  led_strip.clear();
  led_strip.show();
}

void setColor(uint32_t _color)
{
  for(uint16_t i = 0; i < led_strip.numPixels(); i++) 
  {
    led_strip.setPixelColor(i, _color);
  }
  led_strip.show();
}

void ColorWipe(uint32_t c, int wait) 
{
  for (uint16_t i = 0; i < led_strip.numPixels(); i++) 
  {
    led_strip.setPixelColor(i, c);
    led_strip.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) 
{
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return led_strip.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return led_strip.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return led_strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}
