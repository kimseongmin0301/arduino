#include <Adafruit_NeoPixel.h>
unsigned long past=0;      //이전시간
unsigned long now=0;      //현재시간
int order = 0; 
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2 
#define DHTTYPE    DHT11 

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;
LiquidCrystal_I2C lcd(0x27, 16, 2);




#define PIN 5
#define red_on digitalWrite(6,HIGH);
#define green_on digitalWrite(7,HIGH);
#define yellow_on digitalWrite(8,HIGH);
#define yellow_off digitalWrite(8,LOW);
#define red_off digitalWrite(6,LOW);
#define green_off digitalWrite(7,LOW);
#define LEDOFF digitalWrite(6, LOW);digitalWrite(7, LOW);digitalWrite(8,LOW);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  lcd.init();
  lcd.backlight();
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
 
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;



 
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8,OUTPUT);// 출력핀으로 설정합니다
  strip.begin(); //네오픽셀을 초기화하기 위해 모든LED를 off시킨다
  strip.show(); 

}

void loop() {
   asdf();
  now = millis();
 Serial.println(now);
   if (order == 0) {        // 첫 순서 (order = 0)
         if(now > past) past = now;       // past에 현재 시간을 '저장'합니다. 이 값은 고정입니다.
          colorWipe(strip.Color(255, 0, 0),100);
          green_on;
         order=1;               // 다음 순서를 위해 order가 1 증가합니다.
      } 
   if (((now-past) > 5000) && (order == 1)){  // 두번째 순서 (order = 1)
        LEDOFF;
       yellow_on;                      
       if(now > past) past = now;                  // past를 갱신합니다.
        order=2;
       }
        
   if (((now-past) > 3000) && (order == 2)){
       LEDOFF;
       red_on;
       strip.begin();
       colorWipe(strip.Color(0, 255, 0),100);
       if(now > past) past = now;
       order = 3;                           // 마지막 순서이므로 order를 0으로 두어 순서를 초기화시킵니다.
     }
     if(((now-past > 5000) && order == 3)){
    LEDOFF;
    green_on;
    strip.begin();
    colorWipe(strip.Color(255, 0, 0),100);
    if(now > past) past = now;
    order=4;
  }
  if(order == 4){
   LEDOFF;
   strip.begin();
   order = 0; 
  }
}



void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void asdf(){
   delay(delayMS);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  lcd.setCursor(0,0);
  if (isnan(event.temperature)) {
    lcd.print(F("Error reading temperature!"));
  }
  else {
    lcd.print(F("Temp: "));
    lcd.print(event.temperature);
    lcd.print(F("C"));
  }
  dht.humidity().getEvent(&event);
  lcd.setCursor(0,1);
  if (isnan(event.relative_humidity)) {
    lcd.print(F("Error reading humidity!"));
  }
  else {
    lcd.print(F("Humi: "));
    lcd.print(event.relative_humidity);
    lcd.print(F("%"));
  }
}
