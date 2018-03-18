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
  size(displayWidth, displayHeight);
  background(220,220,220);
  font = loadFont("Corbel-Bold-30.vlw");
  textFont(font);
  port = new Serial(this, "COM8", 9600);
  port.bufferUntil(lf); 
}

void draw()
{
  int textLine = displayWidth*13/18; // used to align text in right rectangle
  //draw coord. system & display place
  for(int i= 0;i<displayHeight ; i=i+20)
  {
    line(0,i,910,i);
  }
  for(int i= 0;i<(displayWidth*2/3); i=i+20)
  {
    line(i,0,i,768);
  }
  fill(10,10,10);
  rect(910,0, 1366,768);
  
 
  int x = int(data1) /100;
  int y = int(data2)/100;

 
  //define starting point 
  int coHomeX = 910/2;
  int coHomeY = 768 /2;
  fill(255,0,0);
  ellipse(coHomeX,coHomeY,7,7);
  // display robot position on screen
  int xPoint = x*50 + coHomeX; 
  int yPoint = -y*50 + coHomeY;
  fill(100,100,255);
  noStroke();
  ellipse(xPoint, yPoint, 5, 5);
  // display angle of robot
  fill(0,150,150);
  ellipse(textLine+70, 360, 130,130);
  int angle123 = int(data3) +180;
  fill(255,0,0);
  stroke(255,0,0);
  strokeWeight(7);
  line(textLine+70, 360, cos(radians(angle123))*65 +textLine+70 ,sin(radians(angle123))*65 +360); 
  noStroke();
  
  
  
   
  
  // DISPLAY X,Y,ANGLE,USS/IR SENSOR/connection
  String connection="";
  if(int(data6) == 1)
  {
    connection = "connected";
  }
  else
  {
    connection ="not connected";
  }
  fill(250,250,250);
  text("Status: ", textLine, 40);
  text(connection, textLine+100, 40);
  text("POSITION:", textLine-20, 75);
  text("x= ", textLine, 110);
  text(x, textLine+40, 110);
  text("y= ", textLine, 150);
  text(y, textLine+40, 150);
  text("angle= ", textLine, 190);
  text(data3, textLine+95, 190); 
  text("US sensor:", textLine, 230);
  text(data4, textLine+145, 230);
  text("IR sensor:", textLine, 270);
  text(data5, textLine+145, 270);
  
  
  
  
  

  
  
  
}
void serialEvent(Serial port)
{
  data = port.readStringUntil(10);
  data1 =data.substring(0, data.indexOf('a')); // position of X
  data2 =data.substring(data.indexOf('a')+1, data.indexOf('b'));  // position of Y
  data3 =data.substring(data.indexOf('b')+1, data.indexOf('c')); //angle 
  data4 =data.substring(data.indexOf('c')+1, data.indexOf('d')); //USS
  data5 =data.substring(data.indexOf('d')+1, data.indexOf('e')); //ir sensor
  data6 =data.substring(data.indexOf('e')+1, data.indexOf('f')); //connection
  
  
  
  
}
  
