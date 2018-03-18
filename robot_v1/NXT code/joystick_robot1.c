// NXT(master) to Arduino Uno(slave) I2C communication - joystick via rf
task main()
{
	int data1;
	int data2;
	int mPower;
	int direction;
	wait10Msec(1);
	bMotorReflected[motorA] = true;
	bMotorReflected[motorC] = true;
	SensorType(S3) = sensorI2CCustom;
	while(true){
		data1 = 0;
		data2 = 0;
		char msg[]={3, 10, data1, data2};
		sendI2CMsg(S3, msg, 2);
		wait1Msec(20);

		char reply[2];
		readI2CReply(S3, reply, 2);

		switch (reply[0])
		{
			case 49:
				mPower = 0;
				break;
			case 50:
				mPower = 100;
				break;
			case 51:
				mPower = -100;
				break;
		default:
			mPower = 0;
		}
		switch(reply[1])
		{
			case 108:
				direction = 1;
				break;
			case 110:
				direction =0;
				break;
			case 114:
				direction = -1;
				break;
		}


		if(mPower == 100 && direction ==0)
		{
			motor[motorA] = 100;
			motor[motorC] = 100;
		}
		else if(mPower == 0 && direction ==0)
		{
			motor[motorA] = 0;
			motor[motorC] = 0;
		}
		else if(mPower == -100 && direction ==0)
		{
			motor[motorA] = -100;
			motor[motorC] = -100;
		}
		else if(mPower == 0 && direction ==1)
		{
			motor[motorA] = -50;
			motor[motorC] = 50;
		}
		else if(mPower == 0 && direction ==-1)
		{
			motor[motorA] = 50;
			motor[motorC] = -50;
		}
		else if(mPower == 100 && direction ==1)
		{
			motor[motorA] = 50;
			motor[motorC] = 100;
		}
		else if(mPower == 100 && direction ==-1)
		{
			motor[motorA] = 100;
			motor[motorC] = 50;
		}
		else if(mPower == -100 && direction ==1)
		{
			motor[motorA] = -50;
			motor[motorC] = -100;
		}
		else if(mPower == -100 && direction ==-1)
		{
			motor[motorA] =-100;
			motor[motorC] =-50;
		}





		nxtDisplayCenteredTextLine(4, "%d, %d",mPower);
		nxtDisplayCenteredTextLine(5, "%d, %d",direction);

		wait10Msec(10);
	}
}
