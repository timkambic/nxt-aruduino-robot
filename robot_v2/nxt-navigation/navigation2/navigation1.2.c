#pragma config(Sensor, S4,     USS,            sensorSONAR)

//global variables
float positionX; //accurate X position updated before turning
float positionY; //accurate Y position updated before turning
float positionXb; // X position between turns
float positionYb; // Y position between turns
int previousAngle; // store the angle that was last used when turning --mathematical angle
bool turningQ; // is robot turning ?

///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
void robotFwdDeg(int degrees, int power)
{
	int degreesStart = nMotorEncoder[motorA];
	while(nMotorEncoder[motorA] < degrees + degreesStart - 20)
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

/////////////////////////////////////////////////////////////////////////////////////////////////////
void updatePosition() //inaccurate position when driving -- update in displayAndSend()
{
	float distance = (nMotorEncoder[motorA]+ nMotorEncoder[motorC])/2;

	float dY = distance / 360 * sinDegrees(previousAngle);
  float dX = distance / 360 * cosDegrees(previousAngle)*(-1);

  positionXb = positionX + dX;
  positionYb = positionY + dY;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void updatePositionBeforeTurn() //accurate position is updated every time tobot turns --update befor each turn!!
{
	float distance = (nMotorEncoder[motorA]+ nMotorEncoder[motorC])/2;

	float dY = distance / 360 * sinDegrees(previousAngle);
  float dX = distance / 360 * cosDegrees(previousAngle)*(-1);

  positionX = positionX +dX;
  positionY = positionY +dY;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////
void robotTurn(float angle) // turn for angle (if angle>0 turn clockwise if angle<0 turn counterclockwise)
{
	turningQ = true;
	float wheel2R = 78; // in mm
	float robot2R = 157.3; // in mm

	float turnDegreesF = robot2R / wheel2R * angle ;
	int  turnDegrees = turnDegreesF;
	nxtDisplayCenteredTextLine(1, "%f", turnDegreesF);
	//updatePositionBeforeTurn();
	nMotorEncoder[motorC] = 0;
	nMotorEncoder[motorA] = 0;
	wait1Msec(40);
	if(angle < 0) //counterclockwise turn
	{
		while(nMotorEncoder[motorC] < -turnDegrees - 40)
		{
			motor[motorC] = 25;
			motor[motorA] = -25;
		}
		while(nMotorEncoder[motorC] < -turnDegrees)
		{
			motor[motorC] = 15;
			motor[motorA] = -15;
		}
		motor[motorA] = 0;
		motor[motorC] = 0;
	}
	else //clockwise turn
	{
		while(nMotorEncoder[motorA] < turnDegrees - 40)
		{
			motor[motorA] = 25;
			motor[motorC] = -25;
			nxtDisplayCenteredTextLine(2, "%i", nMotorEncoder[motorA]);
		}
		while(nMotorEncoder[motorA] < turnDegrees)
		{
			motor[motorA] = 8;
			motor[motorC] = -8;
			nxtDisplayCenteredTextLine(2, "%i", nMotorEncoder[motorA]);
		}
		motor[motorA] = 0;
		motor[motorC] = 0;
	}
	nxtDisplayCenteredTextLine(2, "%i", nMotorEncoder[motorA]);
	nMotorEncoder[motorA] = 0;
	nMotorEncoder[motorC] = 0;

	previousAngle = angle + previousAngle;
	while(previousAngle > 360)
	{
		previousAngle = previousAngle -360;
	}
	turningQ = false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
task displayAndSend()
{
	while(true)
	{
		//update position if robot is not turning
		if(turningQ == false)
		{
			updatePosition();
		}

		//i2c to arduino
		int dataI2Csend1 =positionXb* 100; // resolution of 0.01 rotations
		int dataI2Csend2 =positionYb* 100;
		int dataI2Csend3 =previousAngle;
		int dataI2Csend4 =SensorValue[USS];
		char msg[6]= {5,10,dataI2Csend1,dataI2Csend2,dataI2Csend3,dataI2Csend4};
		sendI2CMsg(S3, msg, 0);
		//displaying on NXT lcd
		nxtDisplayCenteredTextLine(1, "%f", positionXb);
		nxtDisplayCenteredTextLine(2, "%f", positionYb);
		nxtDisplayCenteredTextLine(3, "N/A");
		nxtDisplayCenteredTextLine(4, "N/A");
		wait1Msec(100);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
task main()
{
	//setup
	bMotorReflected[motorA] = true;
	bMotorReflected[motorC] = true;
	nMotorEncoder[motorA] = 0;
	nMotorEncoder[motorC] = 0;
	positionX =0; //set starting x,y,angle
	positionY =0;
	previousAngle =90; //mathematical angle - robots start facing up(along y axis)
	SensorType(S3) = sensorI2CCustom;
	//StartTask(displayAndSend);
	wait1Msec(500);
	//end of setup
/*
	robotFwdDeg(360, 30);
	updatePositionBeforeTurn();
	robotTurn(90);
	PlaySound(soundBlip);
	wait1Msec(500);

	robotFwdDeg(360, 30);
	updatePositionBeforeTurn();
	robotTurn(-90);
	PlaySound(soundBlip);
	wait1Msec(500);

	robotFwdDeg(360, 30);
	updatePositionBeforeTurn();
	robotTurn(90);
	PlaySound(soundBlip);
	wait1Msec(500);

	robotFwdDeg(360, 30);
	updatePositionBeforeTurn();
	robotTurn(-90);
	PlaySound(soundBlip);
*/
/*
	while(true)
	{
		if(SensorValue[USS] > 35)
		{
			motor[motorA] = 60;
			motor[motorC] = 60;
		}
		else
		{
			motor[motorA] = 0;
			motor[motorC] = 0;

			robotTurn(90);
			wait1Msec(100);
		}
	}
	*/
	/*
	wait1Msec(1000);
	robotTurn(90);
	wait1Msec(3000);
	robotTurn(90);
	wait1Msec(3000);
	robotTurn(90);
	wait1Msec(3000);
	robotTurn(90);
	*/
	wait1Msec(1000);
	robotTurn(360);
	wait1Msec(3000);


}
