#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(A0, A1); // CE, CSN
const byte address[6] = "00001";


// Motor Pins
const int FL1 = 3; const int FL2 = 4;
const int BL1 = 5; const int BL2 = 6;
const int FR1 = 7; const int FR2 = 8;
const int BR1 = 9; const int BR2 = 10;


void setup() {
 radio.begin();
 radio.openReadingPipe(0, address);
 radio.setPALevel(RF24_PA_MIN);
 radio.startListening();
  for(int i=3; i<=10; i++) pinMode(i, OUTPUT);
}


void loop() {
 if (radio.available()) {
   char cmd;
   radio.read(&cmd, sizeof(cmd));
  
   switch(cmd) {
     case 'F': move(1,0, 1,0, 1,0, 1,0); break;
     case 'B': move(0,1, 0,1, 0,1, 0,1); break;
     case 'L': move(0,1, 1,0, 1,0, 0,1); break;
     case 'R': move(1,0, 0,1, 0,1, 1,0); break;
     case 'S': move(0,0, 0,0, 0,0, 0,0); break;
   }
 }
}


void move(int f1, int f2, int b1, int b2, int fr1, int fr2, int br1, int br2) {
 digitalWrite(FL1, f1); digitalWrite(FL2, f2);
 digitalWrite(BL1, b1); digitalWrite(BL2, b2);
 digitalWrite(FR1, fr1); digitalWrite(FR2, fr2);
 digitalWrite(BR1, br1); digitalWrite(BR2, br2);
}
