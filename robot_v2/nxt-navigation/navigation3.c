// GLOBAL VARIABLES
const int startingAngle = 90;
int angleToTurn;
int previousAngle;
bool startTurn;
bool readyTurn;
float startY;
float startX;
float pathY;
float pathX;

////////////////////////////////////////////////////////////////
void robotFwdDeg(int degrees, int power)
{
	int degreesStart = nMotorEncoder[motorA];
	while(nMotorEncoder[motorA] < degrees + degreesStart - 10)
	{
		motor[motorA] = power;
		motor[motorC] = power;
	}
	while(nMotorEncoder[motorA] < degrees + degreesStart)
	{
		motor[motorA] = power - power*0.3;
		motor[motorC] = power - power*0.3;
	}
	motor[motorA] = 0;
	motor[motorC] = 0;
}

/////////////////////////////////////////////////////////////////
void robotTurn(float angle) // turn to specific angle
{
	float wheel2R = 78; // in mm
	float robot2R = 157.3; // in mm

	angleToTurn = angle;
	readyTurn = true;
	while(startTurn == false){}

	float turnDegreesF = robot2R / wheel2R * angle ;
	int  turnDegrees = turnDegreesF;
	wait1Msec(10);
	nMotorEncoder[motorA] = 0;
	while(nMotorEncoder[motorA] < turnDegrees - turnDegrees*0.2)
	{
		motor[motorA] = 25;
		motor[motorC] = -25;
	}
	while(nMotorEncoder[motorA] < turnDegrees)
	{
		motor[motorA] = 10;
		motor[motorC] = -10;
	}
	motor[motorA] = 0;
	motor[motorC] = 0;
	nMotorEncoder[motorA] = 0;

	startTurn = false;
	previousAngle = angleToTurn + previousAngle;
}

///////////////////////////////////////////////////////

task tracking()
{
	while(true)
	{
  	if(readyTurn == true )
  	{
  		float pathA = nMotorEncoder[motorA];
  		float dY = pathA / 360 * sinDegrees(previousAngle);
  		float dX = pathA / 360 * cosDegrees(previousAngle) * (-1);

  		float coY = pathY + dY;
  		float coX = pathX + dX;

  		pathY = coY;
  		pathX = coX;

  		readyTurn = false;
  		startTurn = true;

  		nxtDisplayCenteredTextLine(2, "%f", pathY);
			nxtDisplayCenteredTextLine(3, "%f", pathX);
 	 }
	}
}
///////////////////////////////////////////////////////



task main()
{
	// setup
	bMotorReflected[motorA] = true;
	bMotorReflected[motorC] = true;
	nMotorEncoder[motorA] = 0;
	nMotorEncoder[motorC] = 0;
	previousAngle = startingAngle;
	startY = 0;
	startX = 0;
	pathY = startY;
	pathX = startX;
	StartTask(tracking);
	wait1Msec(500);
	// end of setup


}
