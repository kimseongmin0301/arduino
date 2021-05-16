#include "Adafruit_VL53L0X.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

Servo my;

void setup() {
  Serial.begin(9600);
  my.attach(7);
  my.write(60);
  if (!lox.begin()) {
    while(1);
  }
 
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print(measure.RangeMilliMeter);
    Serial.println("mm");
    if(measure.RangeMilliMeter<100){
      my.write(160);
    }
    else
      my.write(60); 
    }
  } 
