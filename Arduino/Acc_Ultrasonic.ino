#if INCLUDE_ULTRASONIC_CODE

//////////////////////////////////////////////////////////////////////////
//
// Minimum, maximum, and conversion factor for range
//
//////////////////////////////////////////////////////////////////////////

const int ULTRASONIC_MAXIMUM_RANGE = 15;
const int ULTRASONIC_MINIMUM_RANGE = 0;
const double ULTRASONIC_CONVERT_TO_MM = 1/58.2;

//////////////////////////////////////////////////////////////////////////
//
// These control what pins and what sides are active
//
//////////////////////////////////////////////////////////////////////////

const int PIN_ULTRASONIC_BACK_ECHO = 23;
const int PIN_ULTRASONIC_BACK_TRIGGER = 22;
const boolean ULTRASONIC_BACK_ATTACHED = true;

const int PIN_ULTRASONIC_FRONT_ECHO = 25;
const int PIN_ULTRASONIC_FRONT_TRIGGER = 24;
const boolean ULTRASONIC_FRONT_ATTACHED = true;

const int PIN_ULTRASONIC_LEFT_ECHO = 27;
const int PIN_ULTRASONIC_LEFT_TRIGGER = 26;
const boolean ULTRASONIC_LEFT_ATTACHED = false;

const int PIN_ULTRASONIC_RIGHT_ECHO = 29;
const int PIN_ULTRASONIC_RIGHT_TRIGGER = 28;
const boolean ULTRASONIC_RIGHT_ATTACHED = false;

//////////////////////////////////////////////////////////////////////////
//
// Set up ultrasonic sensors
//
//////////////////////////////////////////////////////////////////////////

void setupUltrasonic()
{
	if (ULTRASONIC_BACK_ATTACHED)
	{
		pinMode(PIN_ULTRASONIC_BACK_TRIGGER, OUTPUT);
		pinMode(PIN_ULTRASONIC_BACK_ECHO, INPUT);
	}
	if (ULTRASONIC_FRONT_ATTACHED)
	{
		pinMode(PIN_ULTRASONIC_FRONT_TRIGGER, OUTPUT);
		pinMode(PIN_ULTRASONIC_FRONT_ECHO, INPUT);
	}
	if (ULTRASONIC_RIGHT_ATTACHED)
	{
		pinMode(PIN_ULTRASONIC_RIGHT_TRIGGER, OUTPUT);
		pinMode(PIN_ULTRASONIC_RIGHT_ECHO, INPUT);
	}
	if (ULTRASONIC_LEFT_ATTACHED)
	{
		pinMode(PIN_ULTRASONIC_LEFT_TRIGGER, OUTPUT);
		pinMode(PIN_ULTRASONIC_LEFT_ECHO, INPUT);
	}
}

//////////////////////////////////////////////////////////////////////////
//
// Support function to convert signals to distance measurement
//
//////////////////////////////////////////////////////////////////////////

int calcDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW);
  
  return pulseIn(echoPin, HIGH) * ULTRASONIC_CONVERT_TO_MM;
}

//////////////////////////////////////////////////////////////////////////
//
// Distance check
//
//////////////////////////////////////////////////////////////////////////

boolean safeDistanceCheck(int distance)
{
	return (distance < ULTRASONIC_MAXIMUM_RANGE && distance >= ULTRASONIC_MINIMUM_RANGE);
}

//////////////////////////////////////////////////////////////////////////
//
// Checks if there is something behind
//
//////////////////////////////////////////////////////////////////////////

int UltrasonicBehindDistance()
{
  return calcDistance(PIN_ULTRASONIC_BACK_TRIGGER, PIN_ULTRASONIC_BACK_ECHO);
}

boolean isItSafeToGoBack()
{
	if (ULTRASONIC_BACK_ATTACHED)
	{
		return safeDistanceCheck(UltrasonicBehindDistance());
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
//
// Checks if there is something ahead
//
//////////////////////////////////////////////////////////////////////////

int UltrasonicFrontDistance()
{
  return calcDistance(PIN_ULTRASONIC_FRONT_TRIGGER, PIN_ULTRASONIC_FRONT_ECHO);
}

boolean isItSafeToGoForward()
{
	if (ULTRASONIC_FRONT_ATTACHED)
	{
		return safeDistanceCheck(UltrasonicFrontDistance());
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
//
// Checks if there is something to the left
//
//////////////////////////////////////////////////////////////////////////

int UltrasonicLeftDistance()
{
  return calcDistance(PIN_ULTRASONIC_LEFT_TRIGGER, PIN_ULTRASONIC_LEFT_ECHO);
}

boolean isItSafeToTheLeft()
{
	if (ULTRASONIC_LEFT_ATTACHED)
	{
		return safeDistanceCheck(UltrasonicLeftDistance());
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
//
// Checks if there is something to the right
//
//////////////////////////////////////////////////////////////////////////

int UltrasonicRightDistance()
{
	return calcDistance(PIN_ULTRASONIC_RIGHT_TRIGGER, PIN_ULTRASONIC_RIGHT_ECHO);
}

boolean isItSafeToTheRight()
{
	if (ULTRASONIC_RIGHT_ATTACHED)
	{
		return safeDistanceCheck(UltrasonicRightDistance());
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
//
// Automatic reading of ultrasonic sensors
//
//////////////////////////////////////////////////////////////////////////

void automaticUltrasonicReading()
{
	if (ULTRASONIC_BACK_ATTACHED)
	{
		Serial.print("Back: " + String(UltrasonicBehindDistance()) + " ");
	}

	if (ULTRASONIC_FRONT_ATTACHED)
	{
		Serial.print("Front: " + String(UltrasonicFrontDistance()) + " ");
	}

	if (ULTRASONIC_LEFT_ATTACHED)
	{
		Serial.print("Left: " + String(UltrasonicLeftDistance()) + " ");
	}

	if (ULTRASONIC_RIGHT_ATTACHED)
	{
		Serial.print("Right: " + String(UltrasonicRightDistance()) + " ");
	}
	Serial.println();
	delay(1000);
}
#endif // INCLUDE_ULTRASONIC_CODE