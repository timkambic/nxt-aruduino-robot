#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
 
int dataRfReceived[6]; //num 5 not used
 
RF24 radio(8,7);
const uint64_t pipes[2] = {0xE8E8F0F0E1LL, 0xF0F0F0F0D2LL};
 
void setup()
{
  Serial.begin(9600);
  radio.begin();
  
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  
  radio.startListening();
}
 
int counter =0;
 
void loop()
{
  long time2;
  int connection;
  int connectionTry;
  
  if ( radio.available() )
  {
    // Dump the payloads until we've gotten everything
    bool done = false;
    while (!done)
    {
      // Fetch the payload, and see if this was the last one.
      done = radio.read( dataRfReceived, sizeof(dataRfReceived) );
    }
    time2 = millis();
  }
  int Xaxis = dataRfReceived[0];
  int Yaxis = dataRfReceived[1];
  int angle = dataRfReceived[2];
  int USSsensor = dataRfReceived[3];
  int IRsensor = dataRfReceived[4];

  if(millis() - time2 > 500)
  {
    //timeout
    connectionTry = 0;
  }
  else
  {
    connectionTry = 1;
  }
  connection = 1;
  if(connectionTry==0) // if 3 windows are missed -->Connection lost
  {
    counter++;
    if(counter > 2)
    {
      connection = 0;
    }
  }
  else
  {
    counter =0;
  }
  
  //send to pc via serial to display
  Serial.print(Xaxis);
  Serial.print('a');
  Serial.print(Yaxis);
  Serial.print('b');
  Serial.print(angle);
  Serial.print('c');
  Serial.print(USSsensor);
  Serial.print('d');
  Serial.print(IRsensor);
  Serial.print('e');
  Serial.print(connection);
  Serial.print('f');  
  Serial.println();
  
  delay(100);
  
}
