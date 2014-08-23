#if INCLUDE_SERVO_CODE

#include <Servo.h>

//////////////////////////////////////////////////////////////////////////
//
// Constants used by the servos (time delay and angle defaults)
//
//////////////////////////////////////////////////////////////////////////

#define SERVO_DELAY_STEP 100
#define SERVO_ANGLE_MINIMUM 30
#define SERVO_ANGLE_MIDDLE 87
#define SERVO_ANGLE_MAXIMUM 145

//////////////////////////////////////////////////////////////////////////
//
//  The following are to control the quantity of servos attached, which
//  pins they are attached to, and preset position.
//
//////////////////////////////////////////////////////////////////////////

#define SERVOS 1
const byte SERVO_PINS[SERVOS] = {13};
byte SERVO_POSITION_START[SERVOS] = { SERVO_ANGLE_MIDDLE };
byte SERVO_POSITION_MINIMUM[SERVOS] = { SERVO_ANGLE_MINIMUM };
byte SERVO_POSITION_MAXIMUM[SERVOS] = { SERVO_ANGLE_MAXIMUM };

//////////////////////////////////////////////////////////////////////////
//
// State variables for the servos
//
//////////////////////////////////////////////////////////////////////////

byte servoTargetPosition[SERVOS];
byte servoCurrentPosition[SERVOS];
Servo servoObjects[SERVOS];

//////////////////////////////////////////////////////////////////////////
//
// Wrapper to set single target position
//
//////////////////////////////////////////////////////////////////////////

void setTargetPosition(byte servo, byte position)
{
	servoTargetPosition[servo] = position;
}

//////////////////////////////////////////////////////////////////////////
//
// Wrapper to set all target positions
//
//////////////////////////////////////////////////////////////////////////

void setTargetPosition(byte listOfPositions[])
{
	memcpy(listOfPositions, servoTargetPosition, SERVOS);
}

//////////////////////////////////////////////////////////////////////////
//
// Sets starting position of servos
//
//////////////////////////////////////////////////////////////////////////

void setupServos()
{
  setTargetPosition(SERVO_POSITION_START);

	for (int i=0; i < SERVOS; i++) {
		servoObjects[i].attach(SERVO_PINS[i]);
		delay(SERVO_DELAY_STEP);
		servoObjects[i].write(servoTargetPosition[i]);
		delay(SERVO_DELAY_STEP);
		servoCurrentPosition[i] = servoTargetPosition[i];
	}
	servoObjects[0].write(100);

	if (debugMode)
	{
		Serial.println("To control servo(s), enter angle and letter starting with a for the first servo (eg: 100a).");
		Serial.println("To add delay between commands, enter a space before your next command.");
		Serial.println("Angle of motion restricted from " + String(SERVO_ANGLE_MINIMUM) + " to " + String(SERVO_ANGLE_MAXIMUM) + " degrees inclusive.");
	}
}


//////////////////////////////////////////////////////////////////////////
//
// Move in steps to target position for all servos
//
//////////////////////////////////////////////////////////////////////////

void moveToTarget(int numberOfSteps)
{
	for (int step = 0; step < numberOfSteps; step++)
	{
		for (int s = 0; s < SERVOS; s++) {
			servoCurrentPosition[s] = servoCurrentPosition[s] + ((servoTargetPosition[s] - servoCurrentPosition[s]) / numberOfSteps);
			servoObjects[s].write(servoCurrentPosition[s]);
			delay(SERVO_DELAY_STEP);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//
// Reads the serial port converting characters into either a position,
// a delay, or writing the position to the servo desired.
//
//////////////////////////////////////////////////////////////////////////

void manualServos()
{
	static int pos = 0;
  if (Serial.available()) {
    char ch = Serial.read();
    
    if (isDigit(ch)) {
      pos = pos * 10 + ch - '0';
		} else if (ch == '$') {
			Serial.println("Moving home");
			setTargetPosition(SERVO_POSITION_START);
			moveToTarget(12);
			Serial.println("Moving minimum");
			setTargetPosition(SERVO_POSITION_MINIMUM);
			moveToTarget(6);
			Serial.println("Moving maximum");
			setTargetPosition(SERVO_POSITION_MAXIMUM);
			moveToTarget(12);
			pos = 0;
    } else if (ch == ' ') {
      delay(SERVO_DELAY_STEP);
    } else if (ch >= 'a' && ch <= 'a' + SERVOS) {
		  if (pos >= SERVO_ANGLE_MINIMUM && pos <= SERVO_ANGLE_MAXIMUM)
			{
        servoObjects[ch - 'a'].write(pos);
  			servoCurrentPosition[ch - 'a'] = pos;
				if (debugMode)
				{
					Serial.println("Received " + String(pos) + ch);
				}
			}
      pos = 0;
    }
  }
}
#endif // INCLUDE_SERVO_CODE