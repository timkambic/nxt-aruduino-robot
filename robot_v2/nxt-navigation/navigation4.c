/*  TO DO LIST
- change wheel rotations to actual cm grid
- object avoiding
- facing angle
- try goto(-1,-1)...
- turning in other direction (try motordecoderC)
*/

// GLOBAL VARIABLES
int angleToTurn;
int previousAngle;
bool startTurn;
bool readyTurn;
float pathY;
float pathX;
////////////////////////////////////////////////////////////////
/*
ALL FUNCTIONS:
-robotFwdDeg
-robotTurn
-robotTurnAtStartingAngle NOT WORKING !!
-robotGoTo

*/
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
	if(angle < 0)
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
void robotTurnAtStartingAngle() // NOT WORKING !!
{
	robotTurn(360 - previousAngle);
}

////////////////////////////////////////////////////////
void robotGoTo(float X , float Y)
{
	float distance = sqrt((X - pathX)*(X - pathX) + (Y - pathY)*(Y - pathY));
	float angleS;
	float angleEnd;
	if((X - pathX) > 0 && (Y - pathY) > 0) // 1.kvadrant
	{
		angleS = atan((Y-pathY)/(X-pathX)) *180/PI;
		angleEnd = 90 - angleS;
	}
	else if((X - pathX) < 0 && (Y - pathY) > 0) // 2.kvadrant
	{
		angleS = atan((Y-pathY)/(pathX-X)) *180 / PI;
		angleEnd = 270 + angleS;
	}
	else if((X - pathX) < 0 && (Y - pathY) < 0) // 3. kvadrant
	{
		angleS = atan((pathY-Y)/(pathX-X)) * 180;
		angleEnd = 270 - angleS;
	}
	else if((X - pathX) > 0 && (Y - pathY) < 0) // 4.kvadrant
	{
		angleS = atan((pathY-Y)/(X-pathX)) *180/PI;
		angleEnd = 90 + angleS;
	}

	robotTurn(angleEnd);
	robotFwdDeg(distance*360, 50);
}

//////////////////////////////////////////////////////
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
			nxtDisplayCenteredTextLine(4, "%f", previousAngle);
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
	const float startingAngle = 90;
	const float startY = 0;
	const float startX = 0;
	previousAngle = startingAngle;
	pathY = startY;
	pathX = startX;
	StartTask(tracking);
	wait1Msec(500);
	// end of setup
	robotGoTo(1,1);
	robotTurnAtStartingAngle();

}
