//////////////////////////////////////////////////////////////////////////
//
// Current mode the program is in. Change mode to different constant.
//
//////////////////////////////////////////////////////////////////////////

#define INCLUDE_SERVO_CODE 1
#define INCLUDE_MOTOR_CODE 1
#define INCLUDE_ULTRASONIC_CODE 1
#define INCLUDE_LIGHT_CODE 1

#define MODE_SERVO 1
#define MODE_MOTOR 2
#define MODE_ULTRASONIC 3
#define MODE_LIGHT 4

const byte mode = MODE_SERVO;
const bool debugMode = true;

#define SERIAL_SPEED 9600

//////////////////////////////////////////////////////////////////////////
//
// Required setup function to setup devices attached.
//
//////////////////////////////////////////////////////////////////////////

void setup()
{
  if (debugMode)
	{
		Serial.begin(SERIAL_SPEED);
	}
	switch (mode)
	{
#if INCLUDE_SERVO_CODE
		case MODE_SERVO:
			setupServos();
			break;
#endif
#if INCLUDE_MOTOR_CODE
		case MODE_MOTOR:
			setupMotors();
			break;
#endif
#if INCLUDE_ULTRASONIC_CODE
		case MODE_ULTRASONIC:
			setupUltrasonic();
			break;
#endif
#if INCLUDE_LIGHT_CODE
		case MODE_LIGHT:
			setupLightSensors();
			break;
#endif
	}
}

//////////////////////////////////////////////////////////////////////////
//
// Required loop function to handle different modes
//
//////////////////////////////////////////////////////////////////////////

void loop()
{
	switch (mode)
	{
#if INCLUDE_SERVO_CODE
		case MODE_SERVO:
			manualServos();
			break;
#endif
#if INCLUDE_MOTOR_CODE
		case MODE_MOTOR:
			manualMotors();
			break;
#endif
#if INCLUDE_ULTRASONIC_CODE
		case MODE_ULTRASONIC:
			automaticUltrasonicReading();
			break;
#endif
#if INCLUDE_LIGHT_CODE
		case MODE_LIGHT:
			automaticLightReading();
			break;
#endif
	}
}
