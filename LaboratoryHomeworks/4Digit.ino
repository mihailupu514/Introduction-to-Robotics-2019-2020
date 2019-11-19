//joystick pins
const int pinSW = 4;
const int pinX = A1;
const int pinY = A0;


//Segment pins
const int pinA = 12;
const int pinB = 8;
const int pinC = 5;
const int pinD = 3;
const int pinE = 2;
const int pinF = 11;
const int pinG = 6;
const int pinDP = A2;

//digit pins
const int pinD1 = 7;
const int pinD2 = 9;
const int pinD3 = 10;
const int pinD4 = 13;

const int noOfDisplays = 4;
const int noOfDigits = 10;
const int segSize = 8;

const int IntervalDpBlinks = 250;
const int IntervalSwitches = 50;

unsigned long lastDpTime = 0;
unsigned long lastSwTime = 0;
unsigned long currentTime = 0;


int currentDisplay = 0;
int currentDpState = LOW;
int digitIsLocked = 0;


int swValue;
int xValue = 0;
int yValue = 0;

//joystick thresholds and state
bool joyCanMove = false;
int minThreshold = 400;
int maxThreshold = 600;

// segments array
int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

// digits array
int digits[noOfDisplays] = {
  pinD1, pinD2, pinD3, pinD4
};


int currentNumber[noOfDisplays] {
  0, 0, 0, 0
};


byte dpState[noOfDisplays] {
  LOW, LOW, LOW, LOW
};

byte digitMatrix[noOfDigits][segSize - 1] = {
  // a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, 
  {0, 1, 1, 0, 0, 0, 0}, 
  {1, 1, 0, 1, 1, 0, 1}, 
  {1, 1, 1, 1, 0, 0, 1}, 
  {0, 1, 1, 0, 0, 1, 1}, 
  {1, 0, 1, 1, 0, 1, 1}, 
  {1, 0, 1, 1, 1, 1, 1}, 
  {1, 1, 1, 0, 0, 0, 0}, 
  {1, 1, 1, 1, 1, 1, 1}, 
  {1, 1, 1, 1, 0, 1, 1} 
};

void displayNumber(byte digit, byte decimalPointState) {
  for (int i = 0; i < segSize - 1; i++) {
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }
  digitalWrite(segments[segSize - 1], decimalPointState);
}

void showDigit(int num) {
  for (int i = 0; i < noOfDisplays; i++) {
    digitalWrite(digits[i], HIGH);
  }
  digitalWrite(digits[num], LOW);
}

void moveOneDigitLeft() {
  dpState[currentDisplay] = 0;
  if (currentDisplay < 3) {
    currentDisplay++;
  } else {
    currentDisplay = 0;
  }
  joyCanMove = false;
}

void moveOneDigitRight() {
  dpState[currentDisplay] = 0;
  if (currentDisplay > 0) {
    currentDisplay--;
  } else {
    currentDisplay = 3;
  }
  joyCanMove = false;
}

void checkDpState() {
  if (currentTime - lastDpTime  >= IntervalDpBlinks) {
    dpState[currentDisplay] = !dpState[currentDisplay];
    lastDpTime = currentTime;
  }
}

void increaseDigitValue() {
  if (currentNumber[currentDisplay] > 0) {
    currentNumber[currentDisplay]--;
  } else {
    currentNumber[currentDisplay] = 9;
  }
  joyCanMove = false;
}

void decreaseDigitValue() {
  if (currentNumber[currentDisplay] < 9) {
    currentNumber[currentDisplay]++;
  } else {
    currentNumber[currentDisplay] = 0;
  }
  joyCanMove = false;
}

void displayAllNumbers() {
  for (int digit = 0; digit < noOfDisplays; digit++) {
    showDigit(digit);
    displayNumber(currentNumber[digit], dpState[digit]);
    delay(5);
  }
}


void checkLockUnlock() {
  if (swValue == 0 && currentTime - lastSwTime >= IntervalSwitches) {
    if (digitIsLocked == 0) {
      digitIsLocked = 1;
      dpState[currentDisplay] = 1;
    }
    else {
      digitIsLocked = 0;
    }
    lastSwTime = currentTime;
  }
}

void setup() {
  pinMode(pinSW, INPUT_PULLUP); 

  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  for (int i = 0; i < noOfDisplays; i++) {
    pinMode(digits[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  int digit;
  currentTime = millis();

  swValue = digitalRead(pinSW);
  checkLockUnlock();

  if (digitIsLocked == 0) {
    xValue = analogRead(pinX);
    if (xValue < minThreshold && joyCanMove == true)
      moveOneDigitLeft();
    if (xValue > maxThreshold && joyCanMove == true)
      moveOneDigitRight();
    if (xValue >= minThreshold && xValue <= maxThreshold) {
      joyCanMove = true;
    }
    checkDpState();
  }
  else {
    yValue = analogRead(pinY);
    if (yValue < minThreshold && joyCanMove == true)
      increaseDigitValue();
    if (yValue > maxThreshold && joyCanMove == true)
      decreaseDigitValue();
    if (yValue >= minThreshold && yValue <= maxThreshold) {
      joyCanMove = true;
    }
  }
  displayAllNumbers();
}
