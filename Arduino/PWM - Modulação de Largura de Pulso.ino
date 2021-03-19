#define LEDazul 7 // porta digital
#define LEDverde A2 // porta analogica

/*
	portas Digitais PWM fornecem valores de tensao entre 0 e 225
	portas Analogicas fornecem valores de tensao entre 0 e 1023
*/

void setup()
{
	pinMode(LEDazul, OUTPUT);
	pinMode(LEDverde, OUTPUT);
}

void loop()
{
	int i, cont = 0;
	do
	{
		digitalWrite(LEDazul, HIGH);
		delay(1000);
		digitalWrite(LEDazul, LOW);
		delay(1000);
	
		for (i = 0; i < 255; i++)
		{
			analogWrite(LEDverde, i);
			delayMicroseconds(8000);
		}
		for (i = 255; i > 0; i--)
		{
			analogWrite(LEDverde, i);
			delayMicroseconds(8000);
		}

		delay(1000);
		digitalWrite(LEDazul, HIGH);
		delay(1000);
		digitalWrite(LEDazul, LOW);

		delay(2000);
	} while (cont < 10);
}
