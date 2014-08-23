#if INCLUDE_LIGHT_CODE

//////////////////////////////////////////////////////////////////////////
//
// Settings to define which photo resistors are attached and rounding
//
// Dividing factor depends on photo resistor and resistor attached to ground
// Value = 1/2 = 10k resistor
// Value = 1/4 = 100k resistor
//
//////////////////////////////////////////////////////////////////////////

const bool LIGHT_ATTACHED_LEFT = false;
const int LIGHT_PIN_LEFT = 10;
const double LIGHT_DIVIDING_FACTOR_LEFT = 1/2;

const bool LIGHT_ATTACHED_RIGHT = false;
const int LIGHT_PIN_RIGHT = 11;
const double LIGHT_DIVIDING_FACTOR_RIGHT = 1/2;

const bool LIGHT_ATTACHED_FRONT = false;
const int LIGHT_PIN_FRONT = 12;
const double LIGHT_DIVIDING_FACTOR_FRONT = 1/2;

const bool LIGHT_ATTACHED_BACK = false;
const int LIGHT_PIN_BACK = 13;
const double LIGHT_DIVIDING_FACTOR_BACK = 1/2;

const int LIGHT_TOLERANCE_AMOUNT = 10;
const int LIGHT_AUTOMATIC_DELAY = 1000;

//////////////////////////////////////////////////////////////////////////
//
// Setup light sensors
//
//////////////////////////////////////////////////////////////////////////

void setupLightSensors()
{
	// No setup needed to read photo resistors

	if (debugMode)
	{
		Serial.println("Light sensor data:");
	}
}

//////////////////////////////////////////////////////////////////////////
//
// Read generic light level
//
//////////////////////////////////////////////////////////////////////////

int lightLevel(int pin)
{
	return analogRead(pin);
}

//////////////////////////////////////////////////////////////////////////
//
// Read left light level
//
//////////////////////////////////////////////////////////////////////////

int leftLightLevel()
{
  if (LIGHT_ATTACHED_LEFT)
	{
		return lightLevel(LIGHT_PIN_LEFT) * LIGHT_DIVIDING_FACTOR_LEFT;
	}
  return 0;
}

//////////////////////////////////////////////////////////////////////////
//
// Read right light level
//
//////////////////////////////////////////////////////////////////////////

int rightLightLevel()
{
  if (LIGHT_ATTACHED_RIGHT)
	{
		return lightLevel(LIGHT_PIN_RIGHT) * LIGHT_DIVIDING_FACTOR_RIGHT;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
// Read front light level
//
//////////////////////////////////////////////////////////////////////////

int frontLightLevel()
{
	if (LIGHT_ATTACHED_FRONT)
	{
		return lightLevel(LIGHT_PIN_FRONT) * LIGHT_DIVIDING_FACTOR_FRONT;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
// Read back light level
//
//////////////////////////////////////////////////////////////////////////

int backLightLevel()
{
	if (LIGHT_ATTACHED_BACK)
	{
		return lightLevel(LIGHT_PIN_BACK) * LIGHT_DIVIDING_FACTOR_BACK;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
// Automatically monitor light sensors
//
//////////////////////////////////////////////////////////////////////////

void automaticLightReading()
{
  if (debugMode)
	{
		if (LIGHT_ATTACHED_BACK)
		{
			Serial.print("Back: " + String(backLightLevel()) + " ");
		}

		if (LIGHT_ATTACHED_FRONT)
		{
			Serial.print("Front: " + String(frontLightLevel()) + " ");
		}

		if (LIGHT_ATTACHED_LEFT)
		{
			Serial.print("Left: " + String(leftLightLevel()) + " ");
		}

		if (LIGHT_ATTACHED_RIGHT)
		{
			Serial.print("Right: " + String(rightLightLevel()) + " ");
		}

		Serial.print("Source #: " + String(lightSourceKeypad()) + " ");
		Serial.print("Sink #: " + String(lightSinkKeypad()) + " ");

		Serial.println();
	}
	delay(LIGHT_AUTOMATIC_DELAY);
}

//////////////////////////////////////////////////////////////////////////
//
// Based upon sensors attached, returns # from keypad with most light
//
//////////////////////////////////////////////////////////////////////////

char lightSourceKeypad()
{
	int frontLight = frontLightLevel();
	int backLight = backLightLevel();
	int rightLight = rightLightLevel();
	int leftLight = leftLightLevel();
	if (backLight >= LIGHT_TOLERANCE_AMOUNT) // Back light sensor returning data
	{
		if (frontLight + LIGHT_TOLERANCE_AMOUNT > backLight) // Front has more light than back
		{
			if (leftLight + LIGHT_TOLERANCE_AMOUNT > rightLight) // Left has some light
			{
				return CHAR_LEFT_FORWARD;
			}
			else if (rightLight >= LIGHT_TOLERANCE_AMOUNT) // Right has some light
			{
				return CHAR_RIGHT_FORWARD;
			}
			else
			{
				return CHAR_FORWARD;
			}
		}
		else // Back has more light than front
		{
			if (leftLight + LIGHT_TOLERANCE_AMOUNT > rightLight) // Left has some light
			{
				return CHAR_LEFT_HARD;
			}
			else if (rightLight >= LIGHT_TOLERANCE_AMOUNT) // Right has some light
			{
				return CHAR_RIGHT_HARD;
			}
			else
			{
				return CHAR_BACKWARD;
			}
		}
	}
	else if (frontLight >= LIGHT_TOLERANCE_AMOUNT) // Front light sensor returning data
	{
		if (leftLight + LIGHT_TOLERANCE_AMOUNT > rightLight) // Left has some light
		{
			return CHAR_LEFT_FORWARD;
		}
		else if (rightLight >= LIGHT_TOLERANCE_AMOUNT) // Right has some light
		{
			return CHAR_RIGHT_FORWARD;
		}
		else
		{
			return CHAR_FORWARD;
		}
	}
	else if (rightLight >= LIGHT_TOLERANCE_AMOUNT) // Right light sensor returning data
	{
		if (leftLight + LIGHT_TOLERANCE_AMOUNT > rightLight)
		{
			return CHAR_LEFT;
		}
		else
		{
			return CHAR_RIGHT;
		}
	}
	else if (leftLight >= LIGHT_TOLERANCE_AMOUNT) // Left light sensor returning data
	{
		return CHAR_LEFT;
	}
	else // No data, so we stop
	{
		return CHAR_STOP;
	}
}

//////////////////////////////////////////////////////////////////////////
//
// Based upon sensors attached, returns # from keypad with least light
//
//////////////////////////////////////////////////////////////////////////

char lightSinkKeypad()
{
	int frontLight = frontLightLevel();
	int backLight = backLightLevel();
	int rightLight = rightLightLevel();
	int leftLight = leftLightLevel();
	if (backLight >= LIGHT_TOLERANCE_AMOUNT) // Back light sensor returning data
	{
		if (frontLight + LIGHT_TOLERANCE_AMOUNT > backLight) // Front has more light than back
		{
			if (leftLight + LIGHT_TOLERANCE_AMOUNT > rightLight) // Left has some light
			{
				return CHAR_RIGHT_HARD;
			}
			else if (rightLight >= LIGHT_TOLERANCE_AMOUNT) // Right has some light
			{
				return CHAR_LEFT_HARD;
			}
			else
			{
				return CHAR_BACKWARD;
			}
		}
		else // Back has more light than front
		{
			if (leftLight + LIGHT_TOLERANCE_AMOUNT > rightLight) // Left has some light
			{
				return CHAR_RIGHT_FORWARD;
			}
			else if (rightLight >= LIGHT_TOLERANCE_AMOUNT) // Right has some light
			{
				return CHAR_LEFT_FORWARD;
			}
			else
			{
				return CHAR_FORWARD;
			}
		}
	}
	else if (frontLight >= LIGHT_TOLERANCE_AMOUNT) // Front light sensor returning data
	{
		if (leftLight + LIGHT_TOLERANCE_AMOUNT > rightLight) // Left has some light
		{
			return CHAR_RIGHT_HARD;
		}
		else if (rightLight >= LIGHT_TOLERANCE_AMOUNT) // Right has some light
		{
			return CHAR_LEFT_HARD;
		}
		else
		{
			return CHAR_BACKWARD;
		}
	}
	else if (rightLight >= LIGHT_TOLERANCE_AMOUNT) // Right light sensor returning data
	{
		if (leftLight + LIGHT_TOLERANCE_AMOUNT > rightLight)
		{
			return CHAR_RIGHT;
		}
		else
		{
			return CHAR_LEFT;
		}
	}
	else if (leftLight >= LIGHT_TOLERANCE_AMOUNT) // Left light sensor returning data
	{
		return CHAR_RIGHT;
	}
	else // No data, so we stop
	{
		return CHAR_STOP;
	}
}

#endif // INCLUDE_LIGHT_CODE