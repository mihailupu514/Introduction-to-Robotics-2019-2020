#include <LiquidCrystal.h>
#include <EEPROM.h>
const int pinSW = 10;
const int pinX = A1;
const int pinY = A0;

int swState = LOW;
int lastSwState = LOW;
int switchValue;
int xValue = 0;
int yValue = 0;
bool joyMoved = false;
int minThreshold = 400;
int maxThreshold = 600;

int Option = 1;
int openOp = 0;
int startingLevelValue = 0;
int lastStartingLevelValue = 0;
int level = 0;
int highScore = 0;
int highScoreAddress = 0;
int Score = 0;
int count = 0;
int lastOption = 0;

unsigned long previousMillis = 0;

const int RS = 12;
const int enable = 11;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
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

void goToSettings() {
  lcd.clear();
  for (int i = 1; i == openOption();) {
    yValue = analogRead(pinY);

    if (yValue < minThreshold && joyMoved == false) {
      if (startingLevelValue > 0) {
        startingLevelValue--;
      } else {
        startingLevelValue = 9;
      }
      joyMoved = true;
    }

    if (yValue > maxThreshold && joyMoved == false) {
      if (startingLevelValue < 9) {
        startingLevelValue++;
      } else {
        startingLevelValue = 0;
      }
      joyMoved = true;
    }

    if (yValue >= minThreshold && yValue <= maxThreshold) {
      joyMoved = false;
    }

    lcd.setCursor(0, 0);
    lcd.print("Starting Level");
    lcd.setCursor(6, 1);
    lcd.print(startingLevelValue);
    if (startingLevelValue > lastStartingLevelValue) {
      lastStartingLevelValue = startingLevelValue;
      highScore = 0;
      EEPROM.put(highScoreAddress, highScore);
    }
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
  level = startingLevelValue;
  previousMillis = millis();
  Score = 0;
  count = 0;
  lcd.setCursor(0, 0);
  lcd.print("Lives:3");
  lcd.setCursor(9, 0);
  lcd.print("Level:");
  lcd.setCursor(15, 0);
  lcd.print(startingLevelValue);
  lcd.setCursor(5, 1);
  lcd.print("Score: ");
  lcd.setCursor(12, 1);
  lcd.print(level);

}
void startGame() {
  lcd.clear();
  setGame();
  for (int i = 1; i == openOption();) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 5000) {
      previousMillis = currentMillis;
      level += 1;
      lcd.setCursor(12, 1);
      Score = level * 3;
      lcd.print(Score);
      lcd.setCursor(15, 0);
      lcd.print(level);
      count++;
    }
    if (count == 2) {

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
          lcd.print("Congratulations!");
          unsigned long currentMillis = millis();

          if (currentMillis - previousMillis >= 3000) {
            previousMillis = currentMillis;
            lcd.clear();

            for (int i = 1; i == openOption();) {
              lcd.setCursor(2, 0);
              lcd.print("You finished");
              lcd.setCursor(4, 1);
              lcd.print("the game");
              unsigned long currentMillis = millis();
              if (currentMillis - previousMillis >= 2000) {
                previousMillis = currentMillis;
                lcd.clear();

                for (int i = 1; i == openOption();) {
                  lcd.setCursor(2, 0);
                  lcd.print("Press button");
                  lcd.setCursor(5, 1);
                  lcd.print("to exit");

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
  if (swState !=  lastSwState) {
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
void setup() {
  pinMode(pinSW, INPUT_PULLUP);
  lcd.begin(16, 2);
  Serial.begin(9600);
  Menu();
  EEPROM.get(highScoreAddress, highScore); 
}
void loop() {
  chooseOption();
}
