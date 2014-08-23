
//////////////////////////////////////////////////////////////////////////
//
// Current mode the program is in. Change mode to different constant.
//
//////////////////////////////////////////////////////////////////////////

#define MODE_SERVO 1
const byte mode = MODE_SERVO;
const bool debugMode = true;

//////////////////////////////////////////////////////////////////////////
//
// Required setup function to setup devices attached.
//
//////////////////////////////////////////////////////////////////////////

void setup()
{
	Serial.begin(9600);
	if (mode == MODE_SERVO)
	{
  	setupServos();
	}
	if (debugMode)
	{
  	Serial.println("Ready to party!");
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
		case MODE_SERVO:
			manualServos();
			break;
	}
}
