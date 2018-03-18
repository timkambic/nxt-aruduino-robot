// TRANSMITTER
#include <VirtualWire.h>

void setup()
{ 
  //Serial.begin(9600);
  vw_setup(2000);
  vw_set_tx_pin(7);
}

void loop()
{
  int x = analogRead(A0);
  int y = analogRead(A1);
  char msgX;
  char msgY;
  //direction
  if(500 < x < 535) // stop
  {
    msgX = '1';
  } 

  if(x > 540) //forward
  {
    msgX = '2';
  }

  if(x < 500) //backward
  {
    msgX = '3';
  }
  //steering
  if(500 < y < 535) // non
  {
    msgY = 'n';
  } 

  if(y > 540) //right
  {
    msgY = 'r';
  }
  if(y < 500) //left
  {
    msgY = 'l';
  }

  char c[] = {msgX, msgY  };
  vw_send((uint8_t *)c, 2);

  delay(100);
}

