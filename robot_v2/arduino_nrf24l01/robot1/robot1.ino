// code to run on robot side


#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <Wire.h>
 
int dataRFsend[6];
int msg[4]; // data from I2C NXT
 
RF24 radio(8,7);
 
const uint64_t pipes[2] = {0xE8E8F0F0E1LL, 0xF0F0F0F0D2LL};
 
void setup(void)
{
  //nrf24l01 setup
  radio.begin();
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);
  radio.startListening();
  //i2c setup
  Wire.begin(5);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}
 
void loop(void)
{
  //send 
  radio.stopListening();
  dataRFsend[0] = msg[0];
  dataRFsend[1] = msg[1];
  dataRFsend[2] = msg[2];
  dataRFsend[3] = msg[3];
  dataRFsend[4] = 1; //IR sensor goes here
  dataRFsend[5] = 0; //<-- not used
  radio.write( dataRFsend, sizeof(dataRFsend) );
  delay(5);
  radio.startListening();
  
  delay(100);
}


// i2c functions
void requestEvent() //not used
{
  uint8_t bufferI2C[5];
  
  bufferI2C[0] = 0;
  bufferI2C[1] = 0;
  bufferI2C[2] = 0;
  bufferI2C[3] = 0;
  
  Wire.write(bufferI2C, 5);
}

void receiveEvent(int HowMany)
{ 
  int i = 0;  
  while(Wire.available())
  {
    msg[i] = Wire.read();
    i++;
  }  
}
