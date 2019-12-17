#include "LedControl.h"
#include <avr/pgmspace.h>
LedControl m2 = LedControl(13, 12, 11, 0);
LedControl m1 = LedControl(10, 9, 8, 0);
LedControl m3 = LedControl(7, 6, 5, 0);
LedControl m4 = LedControl(4, 3, 2, 0);

int pin_x = A0;
int pin_y = A1;
int i = 0;
int t1 = 0;
int t2 = 0;
int t3 = 0;
int xNava, y, x;
int minThreshold = 400;
int maxThreshold = 600;
unsigned long time_now = 0;
unsigned long time_now2 = 0;
int cazStanga = 0;
const int pinsw = 52;

  const byte mob0[8] = { // X X
    // X X
    B01000100,
    B11101110,
    B10101010,
    B00000000,
    B01000100,
    B11101110,
    B10101010,
    B00000000,
  };
  const byte mob1[8] = { //X X
    //- X
    B01000100,
    B11101110,
    B10101010,
    B00000000,
    B00000100,
    B00001110,
    B00001010,
    B00000000,
  };
  const byte mob2[8] = {//X X
    //X -
    B01000100,
    B11101110,
    B10101010,
    B00000000,
    B01000000,
    B11100000,
    B10100000,
    B00000000,
  };
  const byte mob3[8] = { // X X
    // - -
    B01000100,
    B11101110,
    B10101010,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
  };
  const byte mob4[8] = { // X -
    // - -
    B01000000,
    B11100000,
    B10100000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
  };
  const byte mob5[8] = {// - X
    // - -
    B00000100,
    B00001110,
    B00001010,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
  };
  const byte mob6[8] = {// - X
    // - X
    B00000100,
    B00001110,
    B00001010,
    B00000000,
    B00000100,
    B00001110,
    B00001010,
    B00000000,
  };
  const byte mob7[8] = {// X -
    // X -
    B01000000,
    B11100000,
    B10100000,
    B00000000,
    B00000000,
    B01000000,
    B11100000,
    B10100000,
  };
  const byte mob8[8] = { // - -
    // - -
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
  };


byte incercare[][8] = {
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00100000,
    B01110000,
    B10101000
  }, {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00010000,
    B00111000,
    B01010100
  }, {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00001000,
    B00011100,
    B00101010
  }, {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000100,
    B00001110,
    B00010101
  }, {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000010,
    B00000111,
    B00001010
  }, {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000001,
    B00000011,
    B00000101
  }, {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000001,
    B00000010
  }, {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000001
  }, {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B10000000
  }, {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B10000000,
    B01000000
  }, {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B10000000,
    B11000000,
    B10100000
  }, {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B01000000,
    B11100000,
    B01010000
  }
};
const byte poz0[8] =
{ B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00100000,
  B01110000,
  B10101000
};
const byte poz1[8] =
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00010000,
  B00111000,
  B01010100,
};
const byte poz2[8] =
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00001000,
  B00011100,
  B00101010
};
const byte poz3[8] = {

  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000100,
  B00001110,
  B00010101
};
const byte poz4[8] = {

  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000010,
  B00000111,
  B00001010
};
const byte poz5[8] = {

  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000001,
  B00000011,
  B00000101,
};
const byte poz6[8] = {

  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000001,
  B00000010
};
const byte poz7[8] = {

  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000001
};
const byte poz0_bis[8] = {

  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B10000000
};
const byte poz1_bis[8] = {

  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B10000000,
  B01000000
};
const byte poz2_bis[8] = {

  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B10000000,
  B11000000,
  B10100000
};

const byte poz3_bis[8] = {

  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01000000,
  B11100000,
  B01010000
};

void moveDot()
{
  int x = analogRead(pin_x);
  int y = analogRead(pin_y);

  int x_translate = map(x, 1023, 0, 15, 0 ); //This maps the values//
  int y_translate = map(y, 1023, 0, 15, 0);

  if (x_translate >= 0 && x_translate < 8 && y_translate >= 0 && y_translate < 8)
  { m1.clearDisplay(0);
    m1.setLed(0, x_translate, 7 - y_translate, true);
  }
  else
    m1.clearDisplay(0);
  if (x_translate >= 8 && x_translate < 16 && y_translate >= 0 && y_translate < 8)
  { m2.clearDisplay(0);
    m2.setLed(0, x_translate - 8, 7 - y_translate, true);
  }
  else
    m2.clearDisplay(0);

  if (x_translate >= 0 && x_translate < 8 && y_translate >= 8 && y_translate < 16)
  { m3.clearDisplay(0);
    m3.setLed(0, x_translate, 15 - y_translate, true);
  }
  else
    m3.clearDisplay(0);

  if (x_translate >= 8 && x_translate < 16 && y_translate >= 8 && y_translate < 16)
  { m4.clearDisplay(0);
    m4.setLed(0, x_translate - 8, 15 - y_translate, true);
  }
  else
    m4.clearDisplay(0);
}
const long interval2 = 20000;
unsigned long previousMillis = 0;
void shoot()
{ unsigned long currentMillis = 0;
  byte tempMatrix[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  };
  for (int row = 2; row < 8; row++)
  {
    m3.setLed(0, xNava, row, true);
    tempMatrix[xNava][row] = 1;
    if (tempMatrix[xNava][row - 1] == 1)
    {
      tempMatrix[xNava][row - 1] = 0;
      m3.setLed(0, xNava, row - 1, false);
    }

  }
cazStanga=0;
  if (cazStanga == 0)
  {
    
for (int row = 0; row > 2; row++)
  {
    m1.setLed(0, row , xNava, true);
    tempMatrix[xNava][row] = 1;
    if (tempMatrix[xNava][row - 1] == 1)
    {
      tempMatrix[row][xNava-1] = 0;
      m1.setLed(0, row, xNava-1, false);
    }

  }
  cazStanga=2;
  for (int col = 0; col < 8; col++)
    m1.setColumn(0, 7 - col, mob2[col]);
  }

}


void setup()
{ Serial.begin(9600);
  m1.shutdown(0, false);
  m1.setIntensity(0, 15);
  m1.clearDisplay(0);
  m2.shutdown(0, false);
  m2.setIntensity(0, 15);
  m2.clearDisplay(0);
  m3.shutdown(0, false);
  m3.setIntensity(0, 0);
  m3.clearDisplay(0);
  m4.shutdown(0, false);
  m4.setIntensity(0, 0);
  m4.clearDisplay(0);
  for (int col = 0; col < 8; col++)
    m1.setColumn(0, 7 - col, mob0[col]);

}
void wave0()
{

  for (int col = 0; col < 8; col++)
    m1.setColumn(0, 7 - col, mob0[col]);
  for (int col = 0; col < 8; col++)
    m2.setColumn(0, 7 - col, mob0[col]);

}
void loop()
{
  x = analogRead(pin_x);
  y = analogRead(pin_y);
  xNava = map(x, 1023, 0, 11, 0 );


  switch (xNava) {
    case 0: {
        for (int col = 0; col < 8; col++)
          m3.setColumn(0, 7 - col, incercare[0][col]);
        m4.clearDisplay(0);
        break;
      }
    case 1: {
        for (int col = 0; col < 8; col++)
          m3.setColumn(0, 7 - col, incercare[1][col]);
        m4.clearDisplay(0);
        break;
      }
    case 2: {
        for (int col = 0; col < 8; col++)
          m3.setColumn(0, 7 - col, incercare[2][col]);
        m4.clearDisplay(0);
        break;
      }
    case 3: {
        for (int col = 0; col < 8; col++)
          m3.setColumn(0, 7 - col, incercare[3][col]);
        m4.clearDisplay(0);
        break;
      }
    case 4: {
        for (int col = 0; col < 8; col++)
        { m3.setColumn(0, 7 - col, incercare[4][col]);
          m4.setColumn(0, 7 - col, incercare[8][col]);
        }

        break;
      }
    case 5: {
        for (int col = 0; col < 8; col++)
        { m3.setColumn(0, 7 - col, incercare[5][col]);
          m4.setColumn(0, 7 - col, incercare[9][col]);
        }
        break;
      }
    case 6: {
        for (int col = 0; col < 8; col++)
        { m3.setColumn(0, 7 - col, incercare[6][col]);
          m4.setColumn(0, 7 - col, incercare[10][col]);
        }
        shoot();
        break;
      }
    case 7: {
        for (int col = 0; col < 8; col++)
        { m3.setColumn(0, 7 - col, incercare[7][col]);
          m4.setColumn(0, 7 - col, incercare[11][col]);
        }
        break;
      }
    case 8: {
        for (int col = 0; col < 8; col++)
          m4.setColumn(0, 7 - col, incercare[0][col]);
        m3.clearDisplay(0);
        break;
      }
    case 9: {
        for (int col = 0; col < 8; col++)
          m4.setColumn(0, 7 - col, incercare[1][col]);
        m3.clearDisplay(0);
        break;
      }
    case 10: {
        for (int col = 0; col < 8; col++)
          m4.setColumn(0, 7 - col, incercare[2][col]);
        m3.clearDisplay(0);
        break;
      }
    case 11: {
        for (int col = 0; col < 8; col++)
          m4.setColumn(0, 7 - col, incercare[3][col]);
        m3.clearDisplay(0);
        break;
      }


  }

}
