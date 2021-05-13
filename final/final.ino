#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2 
#define DHTTYPE    DHT11 
#define red_on digitalWrite(6,HIGH);
#define green_on digitalWrite(8,HIGH);
#define yellow_on digitalWrite(7,HIGH);
#define yellow_off digitalWrite(7,LOW);
#define red_off digitalWrite(6,LOW);
#define green_off digitalWrite(8,LOW);
#define LEDOFF digitalWrite(6, LOW);digitalWrite(7, LOW);digitalWrite(8,LOW);


DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long past=0;      //이전시간
unsigned long now=0;      //현재시간
int order = 0; 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, 5, NEO_GRB + NEO_KHZ800);

void setup() {
  // lcd
  lcd.init();
  lcd.backlight();
  
  // dht
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;

  //led strip
  strip.begin(); //네오픽셀을 초기화하기 위해 모든LED를 off시킨다
  strip.show(); 
  
  pinMode(2, INPUT);
  pinMode(3,OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8,OUTPUT);
}

void loop() {
  lcd_on();
  tone1(); 
  sinho();
  }
  
void sinho(){ //신호등
      now = millis();

    if (order == 0) {
        colorWipe(strip.Color(255, 0, 0),1);
        green_on;
        if(now - past > 5000){
            order = 1;
            if(now > past){
                past = now;
            }
        }
    }  else if(order == 1){
        strip.begin();
        LEDOFF;
        yellow_on;
        // 노란불
        if(now - past > 3000){
            order = 2;
            if(now > past){
                past = now;
            }
        }

    } else if(order == 2){
        strip.begin();
        colorWipe(strip.Color(0, 255, 0),1);
        LEDOFF;
        red_on;
        if(now - past > 5000){
            order = 3;
            if(now > past){
                past = now;
            }
        }
    }  else if(order == 3){
        strip.begin();
        order = 0;
    }
}


void tone1(){ //터치 소리
  if(order == 2){
    int a = digitalRead(2);
    if (a == 1)
        tone(3,260);
    else
        noTone(3);
  }
  else
    noTone(3);
  } 

void colorWipe(uint32_t c, uint8_t wait) { //lcd strip
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
    }
  }
  
void lcd_on(){ //dht + lcd
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
