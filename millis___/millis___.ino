#include <Adafruit_NeoPixel.h>
unsigned long past=0;      //이전시간
unsigned long now=0;      //현재시간
int order = 0; 

#define PIN 6


Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  
  Serial.begin(9600);
  strip.begin(); //네오픽셀을 초기화하기 위해 모든LED를 off시킨다
  strip.show(); 

}

void loop() {
  now = millis();
 Serial.println(now);
   if (order == 0) {        // 첫 순서 (order = 0)
         if(now > past) past = now;       // past에 현재 시간을 '저장'합니다. 이 값은 고정입니다.
          colorWipe(strip.Color(255, 0, 0),100);
         order=1;               // 다음 순서를 위해 order가 1 증가합니다.
      } 
   if (((now-past) > 5000) && (order == 1)){  // 두번째 순서 (order = 1)
       strip.begin();
        colorWipe(strip.Color(0, 255, 0),100);                      
       if(now > past) past = now;                  // past를 갱신합니다.
        order=2;
       }
        
   if (((now-past) > 5000) && (order == 2)){
       strip.begin();
       order = 0;                           // 마지막 순서이므로 order를 0으로 두어 순서를 초기화시킵니다.
     }
}



void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
