// TRANSMITTER
#include <VirtualWire.h>

void setup()
{ 
  //Serial.begin(9600);
  vw_setup(2000);
  vw_set_tx_pin(7);
  pinMode(5, INPUT); // toggle switch 
}

void loop()
{
  int x = analogRead(A0);
  int y = analogRead(A1);
  char msgX = map(x,0,1023,0,200);
  char msgY = map(y,0,1023,0,100);
  char msgSwitch = digitalRead(5);
  

  char c[] = {msgX, msgY, msgSwitch};
  vw_send((uint8_t *)c, 3);

  delay(50);
}
