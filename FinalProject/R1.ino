
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <AFMotor.h>
RF24 radio(22, 23); // CE, CSN
struct data{  //data structure to store the X,Y sent by the Gyroscope
  int xAxis;
  int yAxis;

};
data send_data;

AF_DCMotor motor1(1); //declaration of the motor variables according to the screw terminals
AF_DCMotor motor2(2); // that i connected the jumper wires to
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

const byte address[6] = "71993"; // address for the radio com
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
    motor1.setSpeed(200);
  motor1.run(RELEASE);
  motor2.setSpeed(200);
  motor2.run(RELEASE);
  motor3.setSpeed(200);
  motor3.run(RELEASE);
  motor4.setSpeed(200);
  motor4.run(RELEASE);
}
void loop() {
  if (radio.available()) {
      
  radio.read(&send_data, sizeof(send_data));
  Serial.print("aX = "); Serial.print(send_data.xAxis);
  Serial.print(" | aY = "); Serial.print(send_data.yAxis);
  Serial.println();
  
  }
  

  if(send_data.yAxis > 10) { //Backward movement
  motor1.run(BACKWARD);
  motor1.setSpeed(255);
  motor2.run(BACKWARD);
  motor2.setSpeed(255);
  motor3.run(BACKWARD);
  motor3.setSpeed(255);
  motor4.run(BACKWARD);
  motor4.setSpeed(255);

}
else if(send_data.yAxis < 0) { //Forward movement
  motor1.run(FORWARD);
  motor1.setSpeed(255);
  motor2.run(FORWARD);
  motor2.setSpeed(255);
  motor3.run(FORWARD);
  motor3.setSpeed(255);
  motor4.run(FORWARD);
  motor4.setSpeed(255);
}
if(send_data.xAxis < 0 ){ //turn right
 
  motor3.run(FORWARD);
  motor3.setSpeed(255);
  motor2.run(BACKWARD);
  motor2.setSpeed(255);

   motor4.run(FORWARD);
  motor4.setSpeed(255);

}
else if(send_data.xAxis > 10){ //turn left
  motor3.run(BACKWARD);
  motor3.setSpeed(255);
  motor2.run(FORWARD);
  motor2.setSpeed(255);


  motor4.run(FORWARD);
  motor4.setSpeed(255);
  
} 
else  //stop
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  }
 
 }
