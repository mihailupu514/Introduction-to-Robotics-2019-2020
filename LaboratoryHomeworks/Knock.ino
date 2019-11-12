/* Knock Sensor

 * ----------------

 *

 * Program using a Piezo element as if it was a knock sensor.

 *

 * We have to basically listen to an analog pin and detect 

 * if the signal goes over a certain threshold. It writes

 * "knock" to the serial port if the Threshold is crossed,

 * and toggles the LED on pin 13.

 *

 * (cleft) 2005 D. Cuartielles for K3

 * edited by Scott Fitzgerald 14 April 2013

 */
#include "pitches.h"
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

int ledPin = 13;

int knockSensor = 0;               

byte val = 0;

int statePin = LOW;

int THRESHOLD = 100;

int currentTime=0;
int buzzer = 12;

void setup() {

 pinMode(ledPin, OUTPUT); 

 Serial.begin(9600);
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }

}



void loop() {
int i;
  val = analogRead(knockSensor);     

  if (val >= THRESHOLD) {

    statePin = !statePin;

    digitalWrite(ledPin, statePin);

    Serial.println(val);
  
delay(5000);
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }


  }
  delay(100);  // we have to make a delay to avoid overloading the serial port

}
