Here we shall post the homeworks.If only we did them when required :)


RGBPotentiometer
1 RGB Led
3 potentiometers
Connection cable
Arduino Uno
Jumper Wires
220 ohm resistors

We use the 3 potentiometers to change the value of each coler . Based on the values we can recreate colors like violet , yellow ,white etc. , besides the standard Red , Green , Blue


Knock Buzzer
Passive Buzzer
Active Buzzer
1 5.1 V Diode
1Mega ohm resistor
1 Button
Jumper Wires
Red Led


We use the passive buzzer to detect the knock . When the knock was registered , the led lights up and after 5 seconds , the active buzzer plays a note . 



4 Digit 7 Segment Display 
Requirements : 
Connection Cable
Jumper wires
Joystick
4 Digits 7 Segment Display 
Arduino Uno

Purpose :  We use the joystick to switch the values displayed . While the dp is blinking , swipe left/right to select the digit . To lock on the specific digit , press the sw button . While the dp state is high , swipe up/down to cycle between 0-9. To save the change , press sw once again .


LCD Menu with joystick control
Requirements : 
Connection Cable
Jumper wires
Joystick
Arduino Uno
Potentiometer
330 Ohm Resistor
Breadboard
Auxiliar Breadboard

Purpose: We created a menu which included Start Game , Settings and Highscore . In the settings we can change the starting level (0-9) . Based on the level , the score increases . Once every 5s the level is incremented and the score is equal to level * 3 . After 10 seconds the game ends and the score is saved in the programmable read-only memory of the arduino (aka eeprom) . Even after resetting the setup , the highscore remains saved .
Video Proof : https://drive.google.com/open?id=14Yqe1oIkHhEX2aH_3A1rkcjQ5RPyTsXn
