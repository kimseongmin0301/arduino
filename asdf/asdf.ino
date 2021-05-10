#include "Adafruit_VL53L0X.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(9600);
 lcd.init();
  lcd.backlight();
  // wait until serial port opens for native USB devices
 
  if (!lox.begin()) {
    while(1);
  }
 
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;
    
 
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  lcd.setCursor(0,0);
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    lcd.print("(mm): "); lcd.print(measure.RangeMilliMeter);

  } 

}
