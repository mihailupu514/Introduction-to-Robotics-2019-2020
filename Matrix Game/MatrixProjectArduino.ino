#include <Arduino.h>
#include "LedControl.h"
#include <avr/pgmspace.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
LedControl m2 = LedControl(13, 12, 11, 0);
LedControl m1 = LedControl(10, 9, 8, 0);
LedControl m3 = LedControl(7, 6, 5, 0);
LedControl m4 = LedControl(4, 3, 2, 0);



const byte animatie1[][8] = {
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00010000,
  B10111010,
  B01111100,
  B10010010
},{
  B00000000,
  B00000000,
  B00000000,
  B00010000,
  B10111010,
  B01111100,
  B10010010,
  B00000000
},{
  B00000000,
  B00000000,
  B00010000,
  B10111010,
  B01111100,
  B10010010,
  B00000000,
  B00000000
},{
  B00000000,
  B00010000,
  B10111010,
  B01111100,
  B10010010,
  B00000000,
  B00000000,
  B00000000
},{
  B00010000,
  B10111010,
  B01111100,
  B10010010,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},{
  B00001010,
  B00000100,
  B00000110,
  B00001111,
  B00000110,
  B00000100,
  B00001010,
  B00000000
},{
  B01001001,
  B00111110,
  B01011101,
  B00001000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B01001001,
  B00111110,
  B01011101,
  B00001000,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B01001001,
  B00111110,
  B01011101,
  B00001000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00000000,
  B01001001,
  B00111110,
  B01011101,
  B00001000,
  B00000000
},{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01001001,
  B00111110,
  B01011101,
  B00001000
},{
  B00000000,
  B01010000,
  B00100000,
  B01100000,
  B11110000,
  B01100000,
  B00100000,
  B01010000
}};
const int animatie1_LEN = sizeof(animatie1)/8;

const byte animatie2[][8] = {
{
  B00000000,
  B01111100,
  B01100110,
  B01100110,
  B01111100,
  B01100110,
  B01100110,
  B01111100
},{
  B00000000,
  B00111100,
  B01100110,
  B01100110,
  B01111110,
  B01100110,
  B01100110,
  B01100110
},{
  B00000000,
  B01111110,
  B01011010,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000
},{
  B00000000,
  B01111110,
  B01011010,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000
},{
  B00000000,
  B01100000,
  B01100000,
  B01100000,
  B01100000,
  B01100000,
  B01100000,
  B01111110
},{
  B00000000,
  B01111110,
  B01100000,
  B01100000,
  B01111100,
  B01100000,
  B01100000,
  B01111110
},{
  B00000000,
  B00111100,
  B01100110,
  B01100000,
  B00111100,
  B00000110,
  B01100110,
  B00111100
},{
  B00000000,
  B01111110,
  B01011010,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000
},{
  B00000000,
  B00111100,
  B01100110,
  B01100110,
  B01111110,
  B01100110,
  B01100110,
  B01100110
},{
  B00000000,
  B01111100,
  B01100110,
  B01100110,
  B01111100,
  B01111000,
  B01101100,
  B01100110
}};
const int animatie2_LEN = sizeof(animatie2)/8;

void displayanimatie1(const byte* animatie1) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      {
        m1.setLed(0, i, j, bitRead(animatie1[i], 7 - j));
        m2.setLed(0, i, j, bitRead(animatie1[i], 7 - j));
        m3.setLed(0, i, j, bitRead(animatie1[i], 7 - j));
        m4.setLed(0, i, j, bitRead(animatie1[i], 7 - j));
      }
    }
  }
}
void displayanimatie2(const byte* animatie2) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      {
        m1.setLed(0, j, 7-i, bitRead(animatie2[i], 7 - j));
        m2.setLed(0, j, 7-i, bitRead(animatie2[i], 7 - j));
        m3.setLed(0, j, 7-i, bitRead(animatie2[i], 7 - j));
        m4.setLed(0, j, 7-i, bitRead(animatie2[i], 7 - j));
      }
    }
  }
}

int iteratoranimatie1=0;
int iteratoranimatie2=0;

const int pinSW = 52;
const int pinX = A0;
const int pinY = A1;
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
bool joyMoved = false;
int nrmobs=0;



int swState = LOW;
int lastSwState = LOW;
int switchValue;
int xValue = 0;
int yValue = 0;
int Option = 1;
int openOp = 0;
int startingWave = 0;
int nrwave=startingWave;
int laststartingWave = 0;
int level = 0;
int highScore = 0;
int highScoreAddress = 0;
int Score = 0;
int count = 0;
int lastOption = 0;

unsigned long previousMillis = 0;

const int RS = 22;
const int enable = 23;
const int d4 = 27;
const int d5 = 25;
const int d6 = 26;
const int d7 = 24;
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

void Menu() {
 
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Start Game");
  lcd.setCursor(1, 1);
  lcd.print("Settings");
  lcd.setCursor(11, 1);
  lcd.print("Score");
}
int chosen;
void ScoreMenu() {
  lcd.clear();
  for (int i = 1; i == openOption();) {
    lcd.setCursor(2, 0);
    lcd.print("High Score");
    lcd.setCursor(7, 1);
    lcd.print(highScore);
  }
  Menu();
}

void Optiuni2()
{
  
}

void goToSettings() {
  lcd.clear();
  for (int i = 1; i == openOption();) {
    yValue = analogRead(pinY);

    if (yValue < minThreshold && joyMoved == false) {
      if (startingWave > 0) {
        startingWave--;
      } else {
        startingWave = 9;
      }
      joyMoved = true;
    }

    if (yValue > maxThreshold && joyMoved == false) {
      if (startingWave < 9) {
        startingWave++;
      } else {
        startingWave = 0;
      }
      joyMoved = true;
    }

    if (yValue >= minThreshold && yValue <= maxThreshold) {
      joyMoved = false;
    }

    lcd.setCursor(0, 0);
    lcd.print("Starting Wave");
    lcd.setCursor(15, 0);
    lcd.print(startingWave);
    if (startingWave > laststartingWave) {
      laststartingWave = startingWave;
      highScore = 0;
      EEPROM.put(highScoreAddress, highScore);
    }
    lcd.setCursor(0, 1);
    lcd.print("Time per Game");
    lcd.setCursor(15, 1);
    lcd.print(chosen);
  }
  Menu();
}

void Cursor() {
  lcd.setCursor(2, 0);
  lcd.print(" ");
  lcd.setCursor(10, 1);
  lcd.print(" ");
  lcd.setCursor(0, 1);
  lcd.print(" ");
}
void setGame() {
  level = startingWave;
  previousMillis = millis();
  Score = 0;
  count = 0;
  lcd.setCursor(0, 0);
  lcd.print("Lives:3");
  lcd.setCursor(9, 0);
  lcd.print("Wave:");
  if(startingWave<10)
  {lcd.setCursor(15, 0);
  lcd.print(startingWave);}
  if(startingWave>=10)
  {
    lcd.setCursor(14, 0);
  lcd.print(startingWave);
  }
  lcd.setCursor(5, 1);
  lcd.print("Score: ");
  lcd.setCursor(12, 1);
  lcd.print(Score);

}
int gameActive=0;
void startGame() {
  lcd.clear();
  setGame();
  for (int i = 1; i == openOption();) {
    startingGame();
    gameActive=1;;
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 5000) {
      previousMillis = currentMillis;
      lcd.setCursor(12, 1);
      Score = Score + (nrmobs*nrwave)+3;
      lcd.print(Score);
      lcd.setCursor(15, 0);
      lcd.print(nrwave);
      count++;
    }
    if (count == 6) {

      if (Score > highScore) {
        highScore = Score;
        EEPROM.put(highScoreAddress, highScore);
      }
      if (currentMillis - previousMillis >= 2000) {
        previousMillis = currentMillis;
        lcd.clear();

        // here I will show the Congrats message
        for (int i = 1; i == openOption();) {
          lcd.setCursor(0, 0);
          lcd.print("Game Over!");
          unsigned long currentMillis = millis();

          if (currentMillis - previousMillis >= 3000) {
            previousMillis = currentMillis;
            lcd.clear();

            for (int i = 1; i == openOption();) {
              lcd.setCursor(2, 0);
              lcd.print("Your time");
              lcd.setCursor(4, 1);
              lcd.print("expired!");
              while(millis()<currentMillis+2000)
              {lcd.clear();
                lcd.setCursor(0, 0);
              lcd.print("Creator:Mihai L.");
              lcd.setCursor(0, 1);
              lcd.print("@UnibucRobotics");
              }
              while(millis()<currentMillis+5000)
              {lcd.clear();
                lcd.setCursor(0, 0);
              lcd.print("github.com/");
              lcd.setCursor(4, 1);
              lcd.print("mihailupu514");
              }
              unsigned long currentMillis = millis();
              if (currentMillis - previousMillis >= 2000) {
                previousMillis = currentMillis;
                lcd.clear();

                for (int i = 1; i == openOption();) {
                  lcd.setCursor(2, 0);
                  lcd.print("Press button");
                  lcd.setCursor(5, 1);
                  lcd.print("to exit");
gameActive=0;
                }
              }
            }
          }
        }
      }
    }
  }

  Menu();
}
int openOption() {
  swState = digitalRead(pinSW);
  if (swState !=  lastSwState && gameActive!=1) {
    if (swState == LOW) {
      openOp = !openOp;
    }
  }
  lastSwState = swState;
  return openOp;
}
void chooseOption() {
  
  xValue = analogRead(pinX);
  if (xValue < minThreshold && joyMoved == false) {
    if (Option > 1) {
      Option--;
    } else {
      Option = 3;
    }
    joyMoved = true;
  }

  if (xValue > maxThreshold && joyMoved == false) {
    if (Option < 3) {
      Option++;
    } else {
      Option = 1;
    }
    joyMoved = true;
  }

  if (xValue >= minThreshold && xValue <= maxThreshold) {
    joyMoved = false;
  }

  if (Option == 1) {
    if (Option != lastOption) {
      Cursor();
      lastOption = Option;
    }
    lcd.setCursor(2, 0);
    lcd.print(">");
    Serial.println(openOp);
    if (openOption() == 1) {
      startGame();
    }
  }
  if (Option == 2) {
    if (Option != lastOption) {
      Cursor();
      lastOption = Option;
    }
    lcd.setCursor(0, 1);
    lcd.print(">");
    Serial.println(openOp);
    if (openOption() == 1) {
      goToSettings();
    }
  }
  if (Option == 3) {
    if (Option != lastOption) {
      Cursor();
      lastOption = Option;
    }
    lcd.setCursor(10, 1);
    lcd.print(">");
    if (openOption() == 1) {

      ScoreMenu();
    }
  }
}

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

bool buttonPressed = false;
bool lastbuttonPressed;
int tras1;
int tras2;
int tras3;
int tras4;
int pozitiecurenta1;
int pozitiecurenta2;


void shoot()
{

  //unsigned long currentMillis = 0;
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

  buttonPressed = !digitalRead(pinSW);
  if (buttonPressed == true && xNava < 6)
  { for (int row = 2; row < 8; row++)
    {
      m3.setLed(0, xNava + 2, row, true);
      tempMatrix[xNava + 2][row] = 1;
      if (tempMatrix[xNava + 2][row - 1] == 1)
      {
        tempMatrix[xNava + 2][row - 1] = 0;
        m3.setLed(0, xNava + 2, row - 1, false);

      }
    }
    if (xNava == 0)
      tras1++;
    if (xNava >= 2 && xNava <= 4)
      tras2++;
  }

   if (tras1 == 1 && tras2 == 0)
    { for (int col = 0; col < 8; col++)
        m1.setColumn(0, 7 - col, mob1[col]);
      pozitiecurenta1 = 1;
      nrmobs++;
    }
    if (tras2 == 1 && tras1==0)
    { for (int col = 0; col < 8; col++)
        m1.setColumn(0, 7 - col, mob2[col]);
      pozitiecurenta1 = 2;
      nrmobs++;
    }
    if(tras1 == 1 && tras2 ==1)
    { for (int col = 0; col < 8; col++)
        m1.setColumn(0, 7 - col, mob3[col]);
      pozitiecurenta1 = 3;
      nrmobs++;
    }
    if (tras1==1 && tras2>=2)
    {
      { for (int col = 0; col < 8; col++)
        m1.setColumn(0, 7 - col, mob4[col]);
      pozitiecurenta1 = 4;
      nrmobs++;
    }
    }
    if (tras1>=2 && tras2==1)
    {
      { for (int col = 0; col < 8; col++)
        m1.setColumn(0, 7 - col, mob5[col]);
      pozitiecurenta1 = 5;
      nrmobs++;
    }
    }
    if (tras1>=2 && tras2==0)
    {
      { for (int col = 0; col < 8; col++)
        m1.setColumn(0, 7 - col, mob6[col]);
      pozitiecurenta1 = 6;
      nrmobs++;
    }
    }
    if (tras1==0 && tras2>=2)
    {
      { for (int col = 0; col < 8; col++)
        m1.setColumn(0, 7 - col, mob7[col]);
      pozitiecurenta1 = 7;
      nrmobs++;
    }
    }
    if (tras1>=2 && tras2>=2)
    {
      { for (int col = 0; col < 8; col++)
        m1.setColumn(0, 7 - col, mob8[col]);
      pozitiecurenta1 = 8;
      nrmobs++;
    }
    }





  if (buttonPressed == true && xNava == 6)
  { for (int row = 2; row < 8; row++)
    {
      m4.setLed(0, 0, row, true);
      tempMatrix[0][row] = 1;
      if (tempMatrix[0][row - 1] == 1)
      {
        tempMatrix[0][row - 1] = 0;
        m4.setLed(0, 0, row - 1, false);
      }
    }
    if(xNava==6)
    tras3++;
  }
  if (buttonPressed == true && xNava == 7)
  { for (int row = 2; row < 8; row++)
    {
      m4.setLed(0, 1, row, true);
      tempMatrix[1][row] = 1;
      if (tempMatrix[1][row - 1] == 1)
      {
        tempMatrix[1][row - 1] = 0;
        m4.setLed(0, 1, row - 1, false);
      }
    }
     if(xNava==7)
    tras3++;
  }
  if (buttonPressed == true && xNava > 7)
  { for (int row = 2; row < 8; row++)
    {
      m4.setLed(0, xNava + 2 - 8, row, true);
      tempMatrix[xNava + 2 - 8][row] = 1;
      if (tempMatrix[xNava + 2 - 8][row - 1] == 1)
      {
        tempMatrix[xNava + 2 - 7][row - 1] = 0;
        m4.setLed(0, xNava + 2 - 8, row - 1, false);
      }
    }
if(xNava==8)
tras3++;

if(xNava>=10 && xNava<=12)
{tras4++;
  }
}


   if (tras3 == 1 && tras4 == 0)
    { for (int col = 0; col < 8; col++)
        m2.setColumn(0, 7 - col, mob1[col]);
      pozitiecurenta2 = 1;
    }
    if (tras4 == 1 && tras3==0)
    { for (int col = 0; col < 8; col++)
        m2.setColumn(0, 7 - col, mob2[col]);
      pozitiecurenta2 = 2;
    }
    if(tras3 == 1 && tras4 ==1)
    { for (int col = 0; col < 8; col++)
        m2.setColumn(0, 7 - col, mob3[col]);
      pozitiecurenta2 = 3;
    }
    if (tras3==1 && tras4>=2)
    {
      { for (int col = 0; col < 8; col++)
        m2.setColumn(0, 7 - col, mob4[col]);
      pozitiecurenta2 = 4;
    }
    }
    if (tras3>=2 && tras4==1)
    {
      { for (int col = 0; col < 8; col++)
        m2.setColumn(0, 7 - col, mob5[col]);
      pozitiecurenta2 = 5;
    }
    }
    if (tras3>=2 && tras4==0)
    {
      { for (int col = 0; col < 8; col++)
        m2.setColumn(0, 7 - col, mob6[col]);
      pozitiecurenta2 = 6;
    }
    }
    if (tras3==0 && tras4>=2)
    {
      { for (int col = 0; col < 8; col++)
        m2.setColumn(0, 7 - col, mob7[col]);
      pozitiecurenta2 = 7;
    }
    }
    if (tras3>=2 && tras4>=2)
    {
      { for (int col = 0; col < 8; col++)
        m2.setColumn(0, 7 - col, mob8[col]);
      pozitiecurenta2 = 8;
    }
    }

if(pozitiecurenta1==8 && pozitiecurenta2==8)
{
  pozitiecurenta1=0;tras1=0;tras2=0;tras3=0;tras4=0;
  pozitiecurenta2=0;
  for (int col = 0; col < 8; col++)
        m1.setColumn(0, 7 - col, mob0[col]);
  for (int col = 0; col < 8; col++)
        m2.setColumn(0, 7 - col, mob0[col]);
        
nrwave++;}
}

void lovire_monstrii()
{
  if (xNava >= 0 && xNava <= 2)
  {
    for (int col = 0; col < 8; col++)
      m1.setColumn(0, 7 - col, mob1[col]);
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
  pinMode(pinSW, INPUT_PULLUP);
  lcd.begin(16, 2);
  Menu();
  EEPROM.get(highScoreAddress, highScore);

  for (int col = 0; col < 8; col++)
    m1.setColumn(0, 7 - col, mob0[col]);
  for (int col = 0; col < 8; col++)
    m2.setColumn(0, 7 - col, mob0[col]);

}
void wave0()
{

  for (int col = 0; col < 8; col++)
    m1.setColumn(0, 7 - col, mob0[col]);
  for (int col = 0; col < 8; col++)
    m2.setColumn(0, 7 - col, mob0[col]);

}
void startingGame()
{

  x = analogRead(pin_x);
  y = analogRead(pin_y);
  xNava = map(x, 1023, 0, 11, 0 );


  switch (xNava) {
    case 0: {
        for (int col = 0; col < 8; col++)
          m3.setColumn(0, 7 - col, incercare[0][col]);
        m4.clearDisplay(0);
        shoot();
        break;
      }
    case 1: {
        for (int col = 0; col < 8; col++)
          m3.setColumn(0, 7 - col, incercare[1][col]);
        m4.clearDisplay(0);
        shoot();
        break;
      }
    case 2: {
        for (int col = 0; col < 8; col++)
          m3.setColumn(0, 7 - col, incercare[2][col]);
        m4.clearDisplay(0);
        shoot();
        break;
      }
    case 3: {
        for (int col = 0; col < 8; col++)
          m3.setColumn(0, 7 - col, incercare[3][col]);
        m4.clearDisplay(0);
        shoot();
        break;
      }
    case 4: {
        for (int col = 0; col < 8; col++)
        { m3.setColumn(0, 7 - col, incercare[4][col]);
          m4.setColumn(0, 7 - col, incercare[8][col]);
        }
        shoot();
        break;
      }
    case 5: {
        for (int col = 0; col < 8; col++)
        { m3.setColumn(0, 7 - col, incercare[5][col]);
          m4.setColumn(0, 7 - col, incercare[9][col]);
        }
        shoot();
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
        shoot();
        break;
      }
    case 8: {
        for (int col = 0; col < 8; col++)
          m4.setColumn(0, 7 - col, incercare[0][col]);
        m3.clearDisplay(0);
        shoot();
        break;
      }
    case 9: {
        for (int col = 0; col < 8; col++)
          m4.setColumn(0, 7 - col, incercare[1][col]);
        m3.clearDisplay(0);
        shoot();
        break;
      }
    case 10: {
        for (int col = 0; col < 8; col++)
          m4.setColumn(0, 7 - col, incercare[2][col]);
        m3.clearDisplay(0);
        shoot();
        break;
      }
    case 11: {
        for (int col = 0; col < 8; col++)
          m4.setColumn(0, 7 - col, incercare[3][col]);
        m3.clearDisplay(0);
        shoot();
        break;
      }
  }
}
void loop()
{ chooseOption();
  

}
