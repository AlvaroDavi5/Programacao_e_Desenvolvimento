int pinLigaLED = 3;
int pinLED = 7;
int pinBUZZER = 2;

void setup()
{
	pinMode(13, OUTPUT);
	pinMode(pinLED, OUTPUT);
	pinMode(pinBUZZER, OUTPUT);
	pinMode(pinLigaLED, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(pinLigaLED), tocabuzzer, FALLING);
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
	digitalWrite(pinLED, HIGH);
	delay(freq);
	digitalWrite(pinLED, LOW);
	delay(freq);
}

void tocabuzzer()
{
	tone(pinBUZZER, 660, 1000);
	delay(1000);
}