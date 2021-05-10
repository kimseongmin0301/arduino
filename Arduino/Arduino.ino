#include "LedControl.h"

LedControl lc = LedControl(7,5,6,1);
byte digits[7][8] = {
  {
    B00111000,
    B01000100,
    B01000100,
    B01000100,
    B01000100,
    B01000100,
    B01000100,
    B00111000
  },
  {
    B00010000,
    B00110000,
    B00010000,
    B00010000,
    B00010000,
    B00010000,
    B00010000,
    B00111000
  },
  {
    B00111000,
    B01000100,
    B00000100,
    B00000100,
    B00001000,
    B00010000,
    B00100000,
    B01111100
  },
  {
    B00111000,
    B01000100,
    B00000100,
    B00011000,
    B00000100,
    B00000100,
    B01000100,
    B00111000
  },
  {
    B00000100,
    B00001100,
    B00010100,
    B00100100,
    B01000100,
    B01111110,
    B00000100,
    B00000100
  },
  {
    B01111100,
    B01000000,
    B01000000,
    B01111000,
    B00000100,
    B00000100,
    B01000100,
    B00111000
  },
  {
    B01111110,
    B00010010,
    B00010010,
    B11111111,
    B00000000,
    B01111110,
    B01000000,
    B01111110
  }
};

void setup() {
  // put your setup code here, to run once:
  lc.shutdown(0, false);
  lc.setIntensity(0, 5);
  lc.clearDisplay(0);

}

void loop() {
  // put your main code here, to run repeatedly:
  int i, j;
  for (int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      lc.setLed(0,col,row,true);      // LED가 켜지면서 밑에서부터 올라갑니다.
      delay(25);                      // 25만큼 지연
    }
  }
  for (int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      lc.setLed(0,col,row,false);       // LED가 꺼지면서 밑에서부터 올라갑니다
      delay(25);                        //25만큼 지연
    }
  }
  for(i=0;i<7;i++){
    for(j=0;j<8;j++){
      lc.setRow(0,j,digits[i][j]);
    }
    delay(1000);
  }
}
