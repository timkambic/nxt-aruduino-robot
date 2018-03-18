
// global variables
int positionX;
int positionY;
bool turnStart =0;
bool turnEnded =0;
int turnAngle;
///////////////////


void robotFwd(int motorPower)
{
	motor[motorA] = motorPower;
	motor[motorC] = motorPower;
}




task turnRobot()
{
	positionX =0;
	positionY =0;
	while(true)
	{
		while(turnStart == false){}
		robotFwd(0);
		int angleToTurn = turnAngle;
		int angleStart = compassRead();
		int wheelA = nMotorEncoder[motorA] /360 * 23.87; //gets centimeters traveled before turning
  	int wheelC = nMotorEncoder[motorC] /360 * 23.87;
  	int distance = (wheelA + wheelC) /2;
  	//start turning
  	if(angleToTurn > 0)
		{
			while(compassRead() < angleStart + angleToTurn)
			{
				motor[motorA]= 30;
				motor[motorA]= -30;
			}
			robotFwd(0);
		}
		else
		{
			while(compassRead() > angleStart + angleToTurn)
			{
				motor[motorA]= -30;
				motor[motorA]= 30;
			}
			robotFwd(0);
		}

		int changeInPositionX = sinDegrees(angleToTurn)*distance;
  	int changeInPositionY = cosDegrees(angleToTurn)*distance;
  	positionX = positionX + changeInPositionX;
  	positionY = positionY + changeInPositionY;

  	turnEnded = true; // tell task main that turn is ended
  }
}

task main()
{
	StartTask(turnRobot);
	wait1Msec(500);
	robotFwd(50);
	wait1Msec(2000);
	robotFwd(0);
	// turn
	turnAngle = 45;
	turnStart = true;
	while(turnEnded != true){}
	//turn ended
}
