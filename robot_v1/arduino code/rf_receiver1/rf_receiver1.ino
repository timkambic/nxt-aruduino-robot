// RECEIVER
// receives joystick data from arduino via rf link(VirtualWire) and sends data to NXT connected via I2C
#include <VirtualWire.h>
#include <Wire.h>

void setup()
{
  //VirtualWire
  vw_setup(2000);
  vw_set_rx_pin(7);
  vw_rx_start();
  //i2c
  Wire.begin(5);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  
  pinMode(13, OUTPUT);
  
}

int dataX;
int dataY;

void loop()
{
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  uint8_t buf[buflen];
  
  if(vw_get_message(buf, &buflen))
  {
    for(int i = 0;i < buflen;i++)
    {
      if(i ==0 ){
        dataX = buf[i];
      }
      else if(i ==1){
        dataY = buf[i];
      }
      
    }
    dataX = buf[0];
    dataY = buf[1];
    
    delay(10);
    
  }
}

void requestEvent()
{
  digitalWrite(13,HIGH);
  uint8_t bufferI2C[2];
  bufferI2C[0] = dataX;
  bufferI2C[1] = dataY;
  
  Wire.write(bufferI2C, 2);
  digitalWrite(13,LOW);
}





void receiveEvent(int HowMany){
  int msg[3];
  int i = 0;
  
  while(Wire.available())
  {
    msg[i] = Wire.read();
    i++;
  }  
}
