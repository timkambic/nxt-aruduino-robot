void robotFwd(int motorPower)
{
	motor[motorA] = motorPower;
	motor[motorC] = motorPower;
}


void robotTurn(int angle)
{
	// angle can be from -90 to 90 degrees !!
	robotFwd(0);
	int compassAtStart = compassRead();
	int wheelA = nMotorEncoder[motorA] /360 * 23.87; //gets centimeters traveled
  int wheelC = nMotorEncoder[motorC] /360 * 23.87;
  int distance = (wheelA + wheelC) /2;

  int changeInPositionX = sinDegrees(angle)*distance;
  int changeInPositionY = cosDegrees(angle)*distance;
  positionX = positionX + changeInPositionX;
  positionY = positionY + changeInPositionY;

	if(angle > 0)
	{
		while(compassRead() < compassAtStart + angle)
		{
			motor[motorA]= 30;
			motor[motorA]= -30;
		}
		robotFwd(0);
	}
	else
	{
		while(compassRead() > compassAtStart + angle)
		{
			motor[motorA]= -30;
			motor[motorA]= 30;
		}
		robotFwd(0);
	}
}

void compassRead()
{
	//read compass value over i2c
	wait1Msec(1);
}


// global variables
int positionX;
int positionY;
///////////////////

task main()
{
	positionX =0;
	positionY =0;
	wait1Msec(500);
	robotFwd(50);
	wait1Msec(2000);
	robotFwd(0);
	robotTurn(45);
}
