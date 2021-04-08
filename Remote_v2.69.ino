#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24Network.h>
#include <RF24_config.h>
#include <SPI.h>

RF24 radio(5, 6);
RF24Network network(radio);

const uint16_t this_node = 00;
const uint16_t node01 = 01;
const uint16_t node02 = 02;

int xPin = A2;
int yPin = A4;
int firePin = A1;
int flashPin = A0;

int xRead;
int yRead;
int fireRead;
int flashRead;


int fireVal=0;
int flashVal=0;

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);

  SPI.begin();
  radio.begin();
  //radio.setRetries(15, 15);
  //radio.setPALevel(RF24_PA_LOW);
  network.begin(108, this_node);
  
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(firePin, INPUT);
  pinMode(flashPin, INPUT);
  
  digitalWrite(firePin, HIGH);
  digitalWrite(flashPin, HIGH);
  

}

void loop() {
  network.update();
  
  xRead=analogRead(xPin);
  yRead=analogRead(yPin);
  fireRead=digitalRead(firePin);
  flashRead=digitalRead(flashPin);


  if (flashRead == 0 && flashVal == 0) {
    flashVal = 1;
    delay(500);
  }
  else if (flashRead == 0 && flashVal == 1) {
    flashVal = 0;
    delay(500);
  }
  
  int dataArray[4] = {xRead, yRead, fireRead, flashVal};
  
  RF24NetworkHeader header(node01);
  bool ok = network.write(header, &dataArray, sizeof(dataArray));
  
  RF24NetworkHeader header2(node02);
  bool ok2 = network.write(header2, &dataArray, sizeof(dataArray));

  
  Serial.print(xRead);
  Serial.print("   ");
  Serial.print(yRead);
  Serial.print("   ");
  Serial.print(fireRead);
  Serial.print("   ");
  Serial.println(flashVal);





  
// Read Tests
//  Serial.print(xRead);
//  Serial.print("   ");
//  Serial.print(yRead);
//  Serial.print("   ");
//  Serial.println(pushRead);
}
