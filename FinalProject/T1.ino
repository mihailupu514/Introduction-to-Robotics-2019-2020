#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Wire.h" // Aceasta librarie permite comunicarea cu device uri I2C
const int MPU_ADDR = 0x68; // Adresa I2C a lui MPU-6050. Daca pinul AD0 este setat ca si HIGH, adresa I2C va fi 0x69.
int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variable accelerometor
char tmp_str[7]; // variable temporara pentru conversie
char* convert_int16_to_str(int16_t i) { // converteaza int16 la string. 
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "71993";
struct data{
  int xAxis;
  int yAxis;

};
data send_data;
void setup() {
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Incepe transmisia cu I2C slave (GY-521)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (porneste MPU-6050)
  Wire.endTransmission(true);
}
void loop() {

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // porneste 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 
  Wire.endTransmission(false); 
  Wire.requestFrom(MPU_ADDR, 7*2, true); // necesita 7*2=14 registrii
  
  accelerometer_x = Wire.read()<<8 | Wire.read();
  accelerometer_y = Wire.read()<<8 | Wire.read(); 

   send_data.xAxis = accelerometer_x/1000;
send_data.yAxis = accelerometer_y/1000;
  // print out data
  Serial.print("aX = "); Serial.print(send_data.xAxis);
  Serial.print(" | aY = "); Serial.print(send_data.yAxis);
  Serial.println();
  radio.write(&send_data,sizeof(data));
  delay(10);

}
