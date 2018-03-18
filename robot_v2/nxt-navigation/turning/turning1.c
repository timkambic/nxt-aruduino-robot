
task main()
{
	// turning
	float turnAngle = 360; // in degrees
	float wheel2R = 75; // in mm
	float robot2R = 153; // in mm
	float turnDegreesF = robot2R / wheel2R * turnAngle ;
	int  turnDegrees = turnDegreesF;
	nxtDisplayCenteredTextLine(4, "%d",turnDegrees);
	wait1Msec(100);

	nMotorEncoder[motorA] = 0;
	while(nMotorEncoder[motorA] - 10 < turnDegrees)
	{
		motor[motorA] = 50;
		motor[motorC] = -50;
	}
	while(nMotorEncoder[motorA] != turnDegrees)
	{
		if(nMotorEncoder[motorA] < turnDegrees)
		{
			motor[motorA] = 10;
			motor[motorC] = -10;
		}
		else
		{
			motor[motorA] = -10;
			motor[motorC] = 10;
		}
	}


}
