#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal_I2C.h>
//#include "Adafruit_VL53L0X.h"
#include <Wire.h>
#include <Servo.h>

#define red_on2 digitalWrite(9,HIGH);  //횡단보도 신호등     9, 10
#define red_off2 digitalWrite(9,LOW);
#define green_on2 digitalWrite(10,HIGH);
#define green_off2 digitalWrite(10,LOW); 
#define DHTTYPE DHT11 
#define red_on digitalWrite(6,HIGH);   //차 신호등 6, 7, 8
#define green_on digitalWrite(8,HIGH);
#define yellow_on digitalWrite(7,HIGH);
#define yellow_off digitalWrite(7,LOW);
#define red_off digitalWrite(6,LOW);
#define green_off digitalWrite(8,LOW);
#define LEDOFF digitalWrite(6, LOW);digitalWrite(7, LOW);digitalWrite(8,LOW);

DHT_Unified dht(12, DHTTYPE);

uint32_t delayMS;
LiquidCrystal_I2C lcd(0x27, 16, 2);         //LCD
//Adafruit_VL53L0X lox = Adafruit_VL53L0X();  //레이저
Servo my; //서보

unsigned long past=0;      //이전시간
unsigned long now=0;      //현재시간
int order = 0; 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(7, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(12, 4, NEO_GRB + NEO_KHZ800);

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
  strip2.begin();
  strip2.show();

  //모터
  my.attach(11);
  my.write(0);
  
  pinMode(2, INPUT); // 인도 터치
  pinMode(23,OUTPUT); // 스피커
  pinMode(6, OUTPUT); //전구
  pinMode(7, OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(12,INPUT);  // dht
  pinMode(24,INPUT);  // 차도 터치
}

void loop() {
  lcd_on();
  tone1();
  touch();
  sinho();
  }
  
void sinho(){ //신호등
      now = millis();
    if (order == 0) {
        colorWipe(strip.Color(255, 0, 0),50);
        colorWipe2(strip2.Color(255, 0, 0),50);
        LEDOFF;
        green_on;
        red_on2;
        green_off2;
        my.write(0);
        if(now - past > 10000){
            order = 1;
            if(now > past){
                past = now;
            }
        }
    }  else if(order == 1){
        strip.begin();
        strip2.begin();
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
        strip2.begin();
        colorWipe(strip.Color(0, 255, 0),50);
        colorWipe2(strip.Color(0, 255, 0),50);
        red_off2;
        green_on2;
        LEDOFF;
        red_on;
        green_on2;
        my.write(90);
        if(now - past > 5000){
            strip.begin();
            strip2.begin();
            colorWipe(strip.Color(63,0,153),50);
            colorWipe2(strip2.Color(63,0,153),50);
       }if(now - past > 10000){
            order = 3;
            if(now > past){
                past = now;
            }
        }
        
    }  else if(order == 3){
        strip.begin();
        strip2.begin();
        green_off2;
        LEDOFF;
        order = 0;
    }
    else if(order == 4){
        strip.begin();
        strip2.begin();
        colorWipe(strip.Color(0, 125, 125),50);
        colorWipe2(strip2.Color(0,125,125),50);
        if(now - past > 15000){
            order = 0;
            if(now > past){
                past = now;
            }
        }
      }
    

}


void tone1(){ //터치 소리
  if(digitalRead(10) == 1){
    if (digitalRead(2) == 1)
        tone(23,260);
    else
        noTone(23);
    }
  else if(digitalRead(9) == 1){
      if(digitalRead(24) == 1)
          tone(23,300);
       else
          noTone(23);
    }
    else
      noTone(23);
    }

void colorWipe(uint32_t c, uint8_t wait) { //lcd strip
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
    }
  }
  
void colorWipe2(uint32_t c, uint8_t wait) { //lcd strip
  for(uint16_t i=0; i<strip2.numPixels(); i++) {
      strip2.setPixelColor(i, c);
      strip2.show();
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

void touch(){
  if(now - past > 5000){
  if(digitalRead(9)==0 && digitalRead(24)==1){
    order = 4;
    if(now > past){
                past = now;
            }
}
}
}
