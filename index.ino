// This #include statement was automatically added by the Particle IDE.
#include "neopixel/neopixel.h"

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D6
#define PIXEL_COUNT 24
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int index_0;
int index_1;
int index_2;
unsigned long t_end;
unsigned long timeForCircling = 10000;
unsigned long timeToEnd = 600000;

void setup() {
    strip.begin();
    strip.show();

    Spark.function("start", imageProcessing);
}

void loop() {
    snowFlake();
    threeSixty();
    circleProgression();
    redToGreen();
    rainbow(100);
    changeRedGreen();
    // imageProcessing("test");
}

void threeSixty() {
  int led;
  int startLeds[] = {0, 12, 6, 18};
  int startGreenLeds = 0;
  int startRedLeds = 12;
  t_end = millis() + timeToEnd;
  while (millis() < t_end) {
    for (int j=0; j<6; j++) {
      for (int i=0; i<(sizeof(startLeds)/sizeof(int)); i++) {
        if ((i+1)%2 > 0) { //if odd number
          strip.setPixelColor(startLeds[i]+j, strip.Color(0, 255, 0)); //set to green
        } else {
          strip.setPixelColor(startLeds[i]+j, strip.Color(255, 0, 0)); //set to red
        }
        strip.show();
        delay(150);
      }
    }
    for (int repeat=0; repeat<3; repeat++) {
      for (int i=0; i<strip.numPixels(); i++) { //makes it go 360
        for (int j=startGreenLeds; j<startRedLeds; j++) {
          if (i+j>(strip.numPixels()-1)) {
            led = (i+j)-(strip.numPixels());
          } else {
            led = i+j;
          }
          strip.setPixelColor(led, strip.Color(0, 255, 0)); //set to green
        }
        for (int j=startRedLeds; j<strip.numPixels(); j++) {
          if (i+j>(strip.numPixels()-1)) {
            led = (i+j)-(strip.numPixels());
          } else {
            led = i+j;
          }
          strip.setPixelColor(led, strip.Color(255, 0, 0)); //set to red
        }
        Serial.println("----");
        strip.show();
        delay(100);
      }
    }
    for (int i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
  }
}

int imageProcessing(String command) {
    t_end = millis() + timeForCircling;
    while (millis() < t_end) {
        for (int i=0; i<strip.numPixels(); i++){
            if (i==22) {
                index_0 = i;
                index_1 = i+1;
                index_2 = 0;
            } else if (i == 23) {
                index_0 = i;
                index_1 = 0;
                index_2 = 1;
            } else {
                index_0 = i;
                index_1 = i+1;
                index_2 = i+2;
            }
            strip.setPixelColor(index_0, strip.Color(0, 255, 0));
            strip.setPixelColor(index_1, strip.Color(255, 0, 0));
            strip.setPixelColor(index_2, strip.Color(0, 255, 0));
            strip.show();
            delay(50);
            strip.setPixelColor(index_0, strip.Color(0, 0, 0));
            strip.setPixelColor(index_1, strip.Color(0, 0, 0));
            strip.setPixelColor(index_2, strip.Color(0, 0, 0));
            strip.show();
        }
    }
    return 1;
}

void rainbow(uint8_t wait) {
    uint16_t i, j;
    t_end = millis() + timeToEnd;
    while(millis() < t_end) {
        for(j=0; j<256; j++) {
            for(i=0; i<strip.numPixels(); i++) {
              strip.setPixelColor(i, Wheel((i+j) & 255));
            }
            strip.show();
            delay(wait);
        }
    }
}

void circleProgression() {
    int counter = 1;
    t_end = millis() + timeToEnd;
    while(millis() < t_end) {
        for (int i=0; i<strip.numPixels(); i++) {
            if(counter%2>0) { // if odd
                strip.setPixelColor(i, strip.Color(255, 0, 0));
            } else { // if even
                strip.setPixelColor(i, strip.Color(0, 255, 0));
            }
            strip.show();
            delay(100);
        }
        counter+=1;
    }
}

void snowFlake() {
    int lowerBrightness = 10;
    for (int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(lowerBrightness,lowerBrightness,lowerBrightness));
    }
    strip.show();
    t_end = millis() + timeToEnd;
    while(millis() < t_end) {
        int numLeds = random(1,8);
        int leds[numLeds];
        for (int i=0; i<numLeds; i++) {
            leds[i] = random(24); //choose random LED to light up
        }
        for (int brightness=lowerBrightness; brightness<256; brightness+=5) {
            for (int i=0; i<(sizeof(leds)/sizeof(int)); i++) {
                strip.setPixelColor(leds[i], strip.Color(brightness, brightness, brightness));
            }
            strip.show();
            delay(20);
        }
        for (int brightness=255; brightness>=lowerBrightness; brightness-=5) {
            for (int i=0; i<(sizeof(leds)/sizeof(int)); i++) {
                strip.setPixelColor(leds[i], strip.Color(brightness, brightness, brightness));
            }
            strip.show();
            delay(20);
        }

    }
}

void redToGreen() {
    int counter = 1;
    t_end = millis() + timeToEnd;
    while(millis() < t_end) {
        for (int brightness=0; brightness<256; brightness++) {
            delay(5);
            for (int i=0; i<strip.numPixels(); i++) {
                if (counter%2 > 0) { //if odd number
                    strip.setPixelColor(i, strip.Color(brightness, 0, 0));
                } else { //if even number
                    strip.setPixelColor(i, strip.Color(0, brightness, 0));
                }
            }
            strip.show();
        }
        for (int brightness=255; brightness>=0; brightness--) {
            delay(5);
            for (int i=0; i<strip.numPixels(); i++) {
                if (counter%2 > 0) { //if odd number
                    strip.setPixelColor(i, strip.Color(brightness, 0, 0));
                } else { //if even number
                    strip.setPixelColor(i, strip.Color(0, brightness, 0));
                }
            }
            strip.show();
        }
        counter+=1;
    }
}

void changeRedGreen() {
    int counter = 1;
    t_end = millis() + timeToEnd;
    while(millis() < t_end) {
        for (int i=0; i<strip.numPixels(); i++) {
            if (counter%2 > 0) { //if odd number
                if (i%2 > 0) { //if odd number
                    strip.setPixelColor(i, strip.Color(255, 0, 0));
                } else {
                    strip.setPixelColor(i, strip.Color(0, 255, 0));
                }
            } else {
                if (i%2 > 0) { //if odd number
                    strip.setPixelColor(i, strip.Color(0, 255, 0));
                } else {
                    strip.setPixelColor(i, strip.Color(255, 0, 0));
                }
            }
        }
        strip.show();
        delay(500);
        counter+=1;
    }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
