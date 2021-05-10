//도트 8*8
#include "LedControl.h"

LedControl lc = LedControl(12, 11, 10, 1);

byte five[] =
{
  B01111110,
  B01000000,
  B01000000,
  B01111111,
  B00000001,
  B00000001,
  B01111111,
  B00000000
};
byte four[] =
{
  B01000100,
  B01000100,
  B01000100,
  B01111111,
  B00000100,
  B00000100,
  B00000100,
  B00000000
};
byte three[] =
{
  B01111110,
  B00000010,
  B00000010,
  B01111110,
  B00000010,
  B00000010,
  B01111110,
  B00000000
};
byte two[] =
{
  B01111110,
  B00000010,
  B00000010,
  B01111110,
  B01000000,
  B01000000,
  B01111110,
  B00000000
};
byte one[] =
{
  B00001000,
  B00011000,
  B00101000,
  B00001000,
  B00001000,
  B00001000,
  B00111110,
  B00000000
};
void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 5);
  lc.clearDisplay(0);
}

void loop() {
  display_five(1);
  delay(1000);
  display_four(1);
  delay(1000);
  display_three(1);
  delay(1000);
  display_two(1);
  delay(1000);
  display_one(1);
  delay(1000);
}

void display_five(int a)
{
  if (a == 1) {
    for (int i = 0; i < 8; i++){
      lc.setRow(0, i, five[i]);
    }
  }
}
void display_four(int a)
{
  if (a == 1) {
    for (int i = 0; i < 8; i++){
      lc.setRow(0, i, four[i]);
    }
  }
}
  void display_three(int a)
{
  if (a == 1) {
    for (int i = 0; i < 8; i++){
      lc.setRow(0, i, three[i]);
    }
  }
}
  void display_two(int a)
{
  if (a == 1) {
    for (int i = 0; i < 8; i++){
      lc.setRow(0, i, two[i]);
    }
  }
}  
    void display_one(int a)
{
  if (a == 1) {
    for (int i = 0; i < 8; i++){
      lc.setRow(0, i, one[i]);
    }
  } 
}
