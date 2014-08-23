#if INCLUDE_MOTOR_CODE

//////////////////////////////////////////////////////////////////////////
//
// This is for the Adafruit Motor Shield
//
//////////////////////////////////////////////////////////////////////////

#include <AFMotor.h>

//////////////////////////////////////////////////////////////////////////
//
//  The following are to control the quantity of motors attached, and which
//  pins they are attached to.
//
//////////////////////////////////////////////////////////////////////////

const int MOTOR_PIN_FRONT_RIGHT = 1;
const bool MOTOR_ATTACHED_FRONT_RIGHT = true;

const int MOTOR_PIN_BACK_RIGHT = 2;
const bool MOTOR_ATTACHED_BACK_RIGHT = true;

const int MOTOR_PIN_FRONT_LEFT = 3;
const bool MOTOR_ATTACHED_FRONT_LEFT = true;

const int MOTOR_PIN_BACK_LEFT = 4;
const bool MOTOR_ATTACHED_BACK_LEFT = true;

//////////////////////////////////////////////////////////////////////////
//
// Constants used by the motors (time delay and speed)
//
//////////////////////////////////////////////////////////////////////////

#define MOTOR_MAX_SPEED 255
#define MOTOR_DELAY_STEP 100

//////////////////////////////////////////////////////////////////////////
//
// Characters used for manual control
//
//////////////////////////////////////////////////////////////////////////

const char CHAR_LEFT_HARD = '1';
const char CHAR_BACKWARD = '2';
const char CHAR_RIGHT_HARD = '3';
const char CHAR_LEFT = '4';
const char CHAR_STOP = '5';
const char CHAR_RIGHT = '6';
const char CHAR_LEFT_FORWARD = '7';
const char CHAR_FORWARD = '8';
const char CHAR_RIGHT_FORWARD = '9';
const char CHAR_DELAY = ' ';
const char CHAR_NEW_LINE = '\n';

//////////////////////////////////////////////////////////////////////////
//
// State variables for the motors
//
//////////////////////////////////////////////////////////////////////////

AF_DCMotor FrontRightMotor(MOTOR_PIN_FRONT_RIGHT);
AF_DCMotor BackRightMotor(MOTOR_PIN_BACK_RIGHT);
AF_DCMotor FrontLeftMotor(MOTOR_PIN_FRONT_LEFT);
AF_DCMotor BackLeftMotor(MOTOR_PIN_BACK_LEFT);
String motorInputString = "";

//////////////////////////////////////////////////////////////////////////
//
// Setup motors initially
//
//////////////////////////////////////////////////////////////////////////

void setupMotors()
{
	if (MOTOR_ATTACHED_FRONT_RIGHT)
	{
		FrontRightMotor.setSpeed(MOTOR_MAX_SPEED);
		FrontRightMotor.run(RELEASE);
	}

	if (MOTOR_ATTACHED_FRONT_LEFT)
	{
		FrontLeftMotor.setSpeed(MOTOR_MAX_SPEED);
		FrontLeftMotor.run(RELEASE);
	}

	if (MOTOR_ATTACHED_BACK_LEFT)
	{
		BackLeftMotor.setSpeed(MOTOR_MAX_SPEED);
		BackLeftMotor.run(RELEASE);
	}

	if (MOTOR_ATTACHED_BACK_RIGHT)
	{
		BackRightMotor.setSpeed(MOTOR_MAX_SPEED);
		BackRightMotor.run(RELEASE);
	}

	if (debugMode)
	{
		Serial.println("To control motor(s), use numeric keypad:");
		Serial.println();
		Serial.println("7 = Forward Left  8 = Forward        9 = Forward Right");
		Serial.println("4 = Left          5 = Stop Movement  6 = Right");
		Serial.println("1 = Hard Left     2 = Backwards      3 = Hard Right");
		Serial.println();
		Serial.println("To add delay between commands, enter a space before your next command.");
		Serial.println("NOTE: Make sure serial passes new line character to accept commands.");
	}
}

//////////////////////////////////////////////////////////////////////////
//
// Move forward for all attached motors
//
//////////////////////////////////////////////////////////////////////////

void forward()
{
#if INCLUDE_ULTRASONIC_CODE
	if (isItSafeToGoForward()) {
#endif

	if (MOTOR_ATTACHED_FRONT_RIGHT)
	{
		FrontRightMotor.run(FORWARD);
	}

	if (MOTOR_ATTACHED_FRONT_LEFT)
	{
		FrontLeftMotor.run(FORWARD);
	}

	if (MOTOR_ATTACHED_BACK_LEFT)
	{
		BackLeftMotor.run(FORWARD);
	}

	if (MOTOR_ATTACHED_BACK_RIGHT)
	{
		BackRightMotor.run(FORWARD);
	}
	delay(MOTOR_DELAY_STEP);

#if INCLUDE_ULTRASONIC_CODE
  }
#endif
}

//////////////////////////////////////////////////////////////////////////
//
// Move backward for all attached motors
//
//////////////////////////////////////////////////////////////////////////

void backward()
{
#if INCLUDE_ULTRASONIC_CODE
	if (isItSafeToGoBack()) {
#endif

	if (MOTOR_ATTACHED_FRONT_RIGHT)
	{
		FrontRightMotor.run(BACKWARD);
	}

	if (MOTOR_ATTACHED_FRONT_LEFT)
	{
		FrontLeftMotor.run(BACKWARD);
	}

	if (MOTOR_ATTACHED_BACK_LEFT)
	{
		BackLeftMotor.run(BACKWARD);
	}

	if (MOTOR_ATTACHED_BACK_RIGHT)
	{
		BackRightMotor.run(BACKWARD);
	}
	delay(MOTOR_DELAY_STEP);
	
#if INCLUDE_ULTRASONIC_CODE
  }
#endif
}

//////////////////////////////////////////////////////////////////////////
//
// Move right for attached motors, left side goes forward and right side 
// goes backward
//
//////////////////////////////////////////////////////////////////////////

void right()
{
#if INCLUDE_ULTRASONIC_CODE
	if (isItSafeToTheRight()) {
#endif

	if (MOTOR_ATTACHED_FRONT_RIGHT && MOTOR_ATTACHED_FRONT_LEFT && 
	    MOTOR_ATTACHED_BACK_LEFT && MOTOR_ATTACHED_BACK_RIGHT) // 4WD
	{
		FrontRightMotor.run(BACKWARD);
		FrontLeftMotor.run(FORWARD);
		BackLeftMotor.run(FORWARD);
		BackRightMotor.run(BACKWARD);
	}
	else if (MOTOR_ATTACHED_FRONT_RIGHT && MOTOR_ATTACHED_FRONT_LEFT)  // 2WD FRONT
	{
		FrontRightMotor.run(BACKWARD);
		FrontLeftMotor.run(FORWARD);
	}
	else if (MOTOR_ATTACHED_BACK_LEFT && MOTOR_ATTACHED_BACK_RIGHT) // 2WD BACK
	{
		BackLeftMotor.run(FORWARD);
		BackRightMotor.run(BACKWARD);
	}
	else if (MOTOR_ATTACHED_BACK_LEFT && MOTOR_ATTACHED_FRONT_RIGHT) // 2WD Opposite
	{
		BackLeftMotor.run(FORWARD);
		FrontRightMotor.run(BACKWARD);
	}
	else if (MOTOR_ATTACHED_FRONT_LEFT && MOTOR_ATTACHED_BACK_RIGHT) // 2WD Opposite
	{
		FrontLeftMotor.run(FORWARD);
		BackRightMotor.run(BACKWARD);
	}
	else if (MOTOR_ATTACHED_BACK_RIGHT) // 1WD
	{
		BackRightMotor.run(BACKWARD);
	}
	else if (MOTOR_ATTACHED_BACK_LEFT) // 1WD
	{
		BackLeftMotor.run(FORWARD);
	}
	else if (MOTOR_ATTACHED_FRONT_RIGHT) // 1WD
	{
		FrontRightMotor.run(BACKWARD);
	}
	else if (MOTOR_ATTACHED_FRONT_LEFT) // 1WD
	{
		FrontLeftMotor.run(FORWARD);
	}
	delay(MOTOR_DELAY_STEP);

#if INCLUDE_ULTRASONIC_CODE
  }
#endif
}

//////////////////////////////////////////////////////////////////////////
//
// Move left for attached motors, left side goes backward and right side goes forward
//
//////////////////////////////////////////////////////////////////////////

void left()
{
#if INCLUDE_ULTRASONIC_CODE
	if (isItSafeToTheLeft()) {
#endif

	if (MOTOR_ATTACHED_FRONT_RIGHT && MOTOR_ATTACHED_FRONT_LEFT && 
	    MOTOR_ATTACHED_BACK_LEFT && MOTOR_ATTACHED_BACK_RIGHT) // 4WD
	{
		FrontRightMotor.run(FORWARD);
		FrontLeftMotor.run(BACKWARD);
		BackLeftMotor.run(BACKWARD);
		BackRightMotor.run(FORWARD);
	}
	else if (MOTOR_ATTACHED_FRONT_RIGHT && MOTOR_ATTACHED_FRONT_LEFT)  // 2WD FRONT
	{
		FrontRightMotor.run(FORWARD);
		FrontLeftMotor.run(BACKWARD);
	}
	else if (MOTOR_ATTACHED_BACK_LEFT && MOTOR_ATTACHED_BACK_RIGHT) // 2WD BACK
	{
		BackLeftMotor.run(BACKWARD);
		BackRightMotor.run(FORWARD);
	}
	else if (MOTOR_ATTACHED_BACK_LEFT && MOTOR_ATTACHED_FRONT_RIGHT) // 2WD Opposite
	{
		BackLeftMotor.run(BACKWARD);
		FrontRightMotor.run(FORWARD);
	}
	else if (MOTOR_ATTACHED_FRONT_LEFT && MOTOR_ATTACHED_BACK_RIGHT) // 2WD Opposite
	{
		FrontLeftMotor.run(BACKWARD);
		BackRightMotor.run(FORWARD);
	}
	else if (MOTOR_ATTACHED_BACK_RIGHT) // 1WD
	{
		BackRightMotor.run(FORWARD);
	}
	else if (MOTOR_ATTACHED_BACK_LEFT) // 1WD
	{
		BackLeftMotor.run(BACKWARD);
	}
	else if (MOTOR_ATTACHED_FRONT_RIGHT) // 1WD
	{
		FrontRightMotor.run(FORWARD);
	}
	else if (MOTOR_ATTACHED_FRONT_LEFT) // 1WD
	{
		FrontLeftMotor.run(BACKWARD);
	}

	delay(MOTOR_DELAY_STEP);

#if INCLUDE_ULTRASONIC_CODE
  }
#endif
}

//////////////////////////////////////////////////////////////////////////
//
// Move hard right for attached motors, left side goes forward and right 
// side goes backward or stops movement
//
//////////////////////////////////////////////////////////////////////////

void hardRight()
{
#if INCLUDE_ULTRASONIC_CODE
	if (isItSafeToTheRight()) {
#endif

	if (MOTOR_ATTACHED_FRONT_RIGHT && MOTOR_ATTACHED_FRONT_LEFT && 
	    MOTOR_ATTACHED_BACK_LEFT && MOTOR_ATTACHED_BACK_RIGHT) // 4WD
	{
    FrontRightMotor.run(BACKWARD);
    FrontLeftMotor.run(FORWARD);
    BackRightMotor.run(RELEASE);
    BackLeftMotor.run(FORWARD);
	}
	else if (MOTOR_ATTACHED_FRONT_RIGHT && MOTOR_ATTACHED_FRONT_LEFT)  // 2WD FRONT
	{
		FrontRightMotor.run(BACKWARD);
		FrontLeftMotor.run(RELEASE);
	}
	else if (MOTOR_ATTACHED_BACK_LEFT && MOTOR_ATTACHED_BACK_RIGHT) // 2WD BACK
	{
		BackLeftMotor.run(RELEASE);
		BackRightMotor.run(BACKWARD);
	}
	else if (MOTOR_ATTACHED_BACK_LEFT && MOTOR_ATTACHED_FRONT_RIGHT) // 2WD Opposite
	{
		FrontRightMotor.run(BACKWARD);
		BackLeftMotor.run(RELEASE);
	}
	else if (MOTOR_ATTACHED_FRONT_LEFT && MOTOR_ATTACHED_BACK_RIGHT) // 2WD Opposite
	{
		FrontLeftMotor.run(RELEASE);
		BackRightMotor.run(BACKWARD);
	}
	else if (MOTOR_ATTACHED_BACK_RIGHT) // 1WD
	{
		BackRightMotor.run(BACKWARD);
	}
	else if (MOTOR_ATTACHED_BACK_LEFT) // 1WD
	{
		BackLeftMotor.run(FORWARD);
	}
	else if (MOTOR_ATTACHED_FRONT_RIGHT) // 1WD
	{
		FrontRightMotor.run(BACKWARD);
	}
	else if (MOTOR_ATTACHED_FRONT_LEFT) // 1WD
	{
		FrontLeftMotor.run(FORWARD);
	}
	delay(MOTOR_DELAY_STEP);

#if INCLUDE_ULTRASONIC_CODE
  }
#endif
}

//////////////////////////////////////////////////////////////////////////
//
// Move hard left for attached motors, left side goes backward or stops
// movement and right side goes forward
//
//////////////////////////////////////////////////////////////////////////

void hardLeft()
{
#if INCLUDE_ULTRASONIC_CODE
	if (isItSafeToTheLeft()) {
#endif

	if (MOTOR_ATTACHED_FRONT_RIGHT && MOTOR_ATTACHED_FRONT_LEFT && MOTOR_ATTACHED_BACK_LEFT && MOTOR_ATTACHED_BACK_RIGHT) // 4WD
	{
		FrontRightMotor.run(FORWARD);
		FrontLeftMotor.run(BACKWARD);
		BackLeftMotor.run(RELEASE);
		BackRightMotor.run(FORWARD);
	}
	else if (MOTOR_ATTACHED_FRONT_RIGHT && MOTOR_ATTACHED_FRONT_LEFT)  // 2WD FRONT
	{
		FrontRightMotor.run(FORWARD);
		FrontLeftMotor.run(RELEASE);
	}
	else if (MOTOR_ATTACHED_BACK_LEFT && MOTOR_ATTACHED_BACK_RIGHT) // 2WD BACK
	{
		BackLeftMotor.run(RELEASE);
		BackRightMotor.run(FORWARD);
	}
	else if (MOTOR_ATTACHED_BACK_LEFT && MOTOR_ATTACHED_FRONT_RIGHT) // 2WD Opposite
	{
		FrontRightMotor.run(FORWARD);
		BackLeftMotor.run(RELEASE);
	}
	else if (MOTOR_ATTACHED_FRONT_LEFT && MOTOR_ATTACHED_BACK_RIGHT) // 2WD Opposite
	{
		FrontLeftMotor.run(RELEASE);
		BackRightMotor.run(FORWARD);
	}
	else if (MOTOR_ATTACHED_BACK_RIGHT) // 1WD
	{
		BackRightMotor.run(FORWARD);
	}
	else if (MOTOR_ATTACHED_BACK_LEFT) // 1WD
	{
		BackLeftMotor.run(BACKWARD);
	}
	else if (MOTOR_ATTACHED_FRONT_RIGHT) // 1WD
	{
		FrontRightMotor.run(FORWARD);
	}
	else if (MOTOR_ATTACHED_FRONT_LEFT) // 1WD
	{
		FrontLeftMotor.run(BACKWARD);
	}
	delay(MOTOR_DELAY_STEP);

#if INCLUDE_ULTRASONIC_CODE
  }
#endif
}

//////////////////////////////////////////////////////////////////////////
//
// Forward left movement
//
//////////////////////////////////////////////////////////////////////////

void forwardLeft()
{
	forward();
	left();
}

//////////////////////////////////////////////////////////////////////////
//
// Forward right movement
//
//////////////////////////////////////////////////////////////////////////

void forwardRight()
{
	forward();
	right();
}

//////////////////////////////////////////////////////////////////////////
//
// Stop movement on all attached motors
//
//////////////////////////////////////////////////////////////////////////

void stopMovement()
{
	if (MOTOR_ATTACHED_FRONT_RIGHT)
	{
		FrontRightMotor.run(RELEASE);
	}

	if (MOTOR_ATTACHED_FRONT_LEFT)
	{
		FrontLeftMotor.run(RELEASE);
	}

	if (MOTOR_ATTACHED_BACK_LEFT)
	{
		BackLeftMotor.run(RELEASE);
	}

	if (MOTOR_ATTACHED_BACK_RIGHT)
	{
		BackRightMotor.run(RELEASE);
	}
	delay(MOTOR_DELAY_STEP);
}

//////////////////////////////////////////////////////////////////////////
//
// Manual control of motors
//
//////////////////////////////////////////////////////////////////////////

char determineNextMotorCommand()
{
	char nextCommand = CHAR_NEW_LINE;
  if (motorInputString.length() > 0)
	{
    nextCommand = motorInputString[0];
    motorInputString = motorInputString.substring(1);
  }
	return nextCommand;
}

void processMotorCommands()
{
	char nextCommand = determineNextMotorCommand();
	while (nextCommand != CHAR_NEW_LINE)
	{
		processMotorCommand(nextCommand);
		nextCommand = determineNextMotorCommand();
	}
}

void processMotorCommand(char command)
{
	switch(command)
	{
		case CHAR_DELAY:
			delay(MOTOR_DELAY_STEP * 4);
			break;
		case CHAR_LEFT_HARD:
			hardLeft();
			break;
		case CHAR_BACKWARD:
			backward();
			break;
		case CHAR_RIGHT_HARD:
			hardRight();
			break;
		case CHAR_LEFT:
			left();
			break;
		case CHAR_STOP:
			stopMovement();
			break;
		case CHAR_RIGHT:
			right();
			break;
		case CHAR_LEFT_FORWARD:
			forwardLeft();
			break;
		case CHAR_FORWARD:
			forward();
			break;
		case CHAR_RIGHT_FORWARD:
			forwardRight();
			break;
		default:
			stopMovement();
			break;
	}
}

void manualMotors()
{
  while (Serial.available()) {
    char newChar = (char)Serial.read(); 
    if (newChar == CHAR_NEW_LINE) {
      motorInputString += CHAR_DELAY;
			processMotorCommands();
    } else {
      motorInputString += newChar;
    }
  }
}
#endif //INCLUDE_MOTOR_CODE