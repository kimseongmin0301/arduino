#include <Adafruit_NeoPixel.h>

#define PIN 6


Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  strip.begin(); //네오픽셀을 초기화하기 위해 모든LED를 off시킨다
  strip.show(); 

}

void loop() {
  
  colorWipe(strip.Color(255,0,0),50);
  strip.show();
  for(int i=8 ; i >=0; i--){
  strip.setPixelColor(i, 0, 0, 0);
  strip.show();
  delay(1000);
  }
}
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
