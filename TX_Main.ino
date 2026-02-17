#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <MPU6050_tockn.h>


RF24 radio(9, 10); // CE, CSN
MPU6050 mpu6050(Wire);
const byte address[6] = "00001";


void setup() {
 Serial.begin(9600);
 Wire.begin();
 mpu6050.begin();
 mpu6050.calcGyroOffsets(true);
  radio.begin();
 radio.openWritingPipe(address);
 radio.setPALevel(RF24_PA_MIN); // Use MIN for indoor testing
 radio.stopListening();
}


void loop() {
 mpu6050.update();
 char command = 'S';
  float x = mpu6050.getAngleX();
 float y = mpu6050.getAngleY();


 if (x > 25) command = 'F';      // Tilt Forward
 else if (x < -25) command = 'B'; // Tilt Backward
 else if (y > 25) command = 'R';  // Tilt Right (Strafe)
 else if (y < -25) command = 'L'; // Tilt Left (Strafe)
 else command = 'S';              // Level (Stop)


 radio.write(&command, sizeof(command));
 delay(50);
}
