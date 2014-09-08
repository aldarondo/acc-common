#if INCLUDE_SERVO_CODE

#include <Servo.h>

//////////////////////////////////////////////////////////////////////////
//
// Constants used by the servos (time delay and angle defaults)
//
//////////////////////////////////////////////////////////////////////////

#define SERVO_DELAY_STEP 15
#define SERVO_ANGLE_MINIMUM 35
#define SERVO_ANGLE_MIDDLE 90
#define SERVO_ANGLE_MAXIMUM 145
byte SERVO_MOVE_CONSISTENT = 0;
byte SERVO_MOVE_HALVES = 1;

//////////////////////////////////////////////////////////////////////////
//
//  The following are to control the quantity of servos attached, which
//  pins they are attached to, and preset position.
//
//////////////////////////////////////////////////////////////////////////

#define SERVOS 1
const byte SERVO_PINS[SERVOS] = {9};
byte SERVO_POSITION_START[SERVOS] = { SERVO_ANGLE_MIDDLE};
byte SERVO_POSITION_MINIMUM[SERVOS] = { SERVO_ANGLE_MINIMUM};
byte SERVO_POSITION_MAXIMUM[SERVOS] = { SERVO_ANGLE_MAXIMUM};

//////////////////////////////////////////////////////////////////////////
//
// State variables for the servos
//
//////////////////////////////////////////////////////////////////////////

byte servoTargetPosition[SERVOS];
byte servoStepSize[SERVOS];
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
	memcpy(servoTargetPosition, listOfPositions, SERVOS);
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

	if (debugMode)
	{
		Serial.println("To control servo(s), enter angle and letter starting with a for the first servo (eg: 100a).");
		Serial.println("To add delay between commands, enter a space before your next command.");
		Serial.println("To scan between minimum and maximum, enter a $ by itself.");
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
	// Determine size of steps based upon target and current position of servos
	for (int s = 0; s < SERVOS; s++) {
		servoStepSize[s] = (servoTargetPosition[s] - servoCurrentPosition[s]) / numberOfSteps;
	}

	// Does all steps except the final step
	for (int step = 0; step < numberOfSteps - 1; step++)
	{
		// Moves each servo closer to the target position
		for (int s = 0; s < SERVOS; s++) {
			servoCurrentPosition[s] = servoCurrentPosition[s] + servoStepSize[s];
			servoObjects[s].write(servoCurrentPosition[s]);
			delay(SERVO_DELAY_STEP);
			if (debugMode)
			{
				Serial.println("s = " + String(s) + " pos = " + String(servoCurrentPosition[s]));
			}
		}
	}

	// Corrects any division rounding for the final step so target is reached always
	for (int s = 0; s < SERVOS; s++) {
		servoCurrentPosition[s] = servoTargetPosition[s];
		servoObjects[s].write(servoCurrentPosition[s]);
		if (debugMode)
		{
			Serial.println("s = " + String(s) + " pos = " + String(servoCurrentPosition[s]));
		}
		delay(SERVO_DELAY_STEP);
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
			setTargetPosition(SERVO_POSITION_START);
			moveToTarget(12);
			setTargetPosition(SERVO_POSITION_MINIMUM);
			moveToTarget(12);
			setTargetPosition(SERVO_POSITION_START);
			moveToTarget(12);
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
					Serial.println("Moved to " + String(pos) + ch);
				}
			}
      pos = 0;
    }
  }
}
#endif // INCLUDE_SERVO_CODE