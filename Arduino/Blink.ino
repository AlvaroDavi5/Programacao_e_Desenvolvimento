int pinLigaLED = 7;

void setup()
{
	pinMode(13, OUTPUT);
	pinMode(pinLigaLED, INPUT_PULLUP);
}

void loop()
{
	int freq = 500;
	
	digitalWrite(13, HIGH);

	if(digitalRead(pinLigaLED) == LOW)
	{
		flash(freq);
	}
	else
	{
		flash(5*freq);
	}
}

void flash(int freq)
{
	digitalWrite(13, HIGH);
	delay(freq);
	digitalWrite(13, LOW);
	delay(freq);
}
