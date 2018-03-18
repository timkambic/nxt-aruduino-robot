import processing.serial.*;
Serial port;
PFont font;
String data ="";
String data1 =""; // X coordinate
String data2 =""; // Y coordinate
String data3 =""; // angle
String data4 =""; // USSsensor
String data5 =""; // IRsensor
String data6 =""; //connection?
static char lf = 10;

boolean sketchFullScreen() {
  return true;
}

void setup()
{
  size(displayWidth, displayHeight); // 1350, 680
  background(220,220,220);
  font = loadFont("CordiaNew-Bold-25.vlw");
  textFont(font);
  port = new Serial(this, "COM8", 9600);
  port.bufferUntil(lf); 
  
}

void draw()
{
  //draw coord. system & display place
  for(int i= 0;i<620 ; i=i+20)
  {
    line(0, i, 600, i); 
    line(i, 0, i, 600);
  }
  fill(10,10,10);
  rect(600,0, 1000,600);
  
  /* position drawing ->
  (0,0)                  (0,600)
  
  (600,0)                (600,600)
  */
  int x = int(data1);
  int y = int(data2);
  ellipse(x, y, 5, 5);
  
  
  
  
  
  
  
  // DISPLAY X,Y,ANGLE,USS/IR SENSOR
  fill(250,250,250);
  text("Status: ", 650, 30);
  String connection ="";
  if(int(data6) == 1)
  {
    connection ="CONNECTED";
  }
  else
  {
    connection ="NOT CONNECTED";
  }
  text(connection, 700, 30);
  
  text("POSITION", 650, 70);
  text("x= ", 680, 90);
  text(data1, 700, 90);
  text("y= ", 680, 110);
  text(data2, 700, 110);
  text("angle= ", 680, 130);
  text(data3, 730, 130);
  
  text("US sensor:", 650, 170);
  text(data4, 735, 170);
  text("IR sensor:", 650, 190);
  text(data5, 730, 190);
  
  
  
  
}
void serialEvent(Serial port)
{
  data = port.readStringUntil(10);
  data1 =data.substring(0, data.indexOf('a')); // position of X
  data2 =data.substring(data.indexOf('a')+1, data.indexOf('b'));  // position of Y
  data3 =data.substring(data.indexOf('b')+1, data.indexOf('c'));
  data4 =data.substring(data.indexOf('c')+1, data.indexOf('d'));
  data5 =data.substring(data.indexOf('d')+1, data.indexOf('e'));
  data6 =data.substring(data.indexOf('e')+1, data.indexOf('f'));
  
  
  
  
}
  
