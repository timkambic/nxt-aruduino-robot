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
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  
}

int dataX;
int dataY;
int dataSwitch;
int dataConnection;
unsigned long lastConnTime;

void loop()
{
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  uint8_t buf[buflen];
  
  if(vw_get_message(buf, &buflen))
  {
    dataX = buf[0];
    dataY = buf[1];
    dataSwitch = buf[2];
    dataConnection = 1;
    delay(1);
    lastConnTime = millis();
  }
  if(millis() - lastConnTime > 1000)
  {
    // lost rf connection 
    dataConnection = 0;
    delay(1);
  }

}


// i2c functions
void requestEvent()
{
  digitalWrite(13,HIGH);
  uint8_t bufferI2C[4];
  bufferI2C[0] = dataX;
  bufferI2C[1] = dataY;
  bufferI2C[2] = dataSwitch;
  bufferI2C[3] = dataConnection;
  
  Wire.write(bufferI2C, 4);
  digitalWrite(13,LOW);
}

void receiveEvent(int HowMany){ // not used
  int msg[3];
  int i = 0;
  
  while(Wire.available())
  {
    msg[i] = Wire.read();
    i++;
  }  
}
