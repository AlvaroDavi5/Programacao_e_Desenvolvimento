#define BUZZER 9

int notas[] = { 524, 588, 660, 699, 785, 881, 989 };

void setup()
{
	pinMode(BUZZER, OUTPUT);
}


void loop()
{
	for (int i = 0; i < 7; i++)
	{
		tone(BUZZER, notas[i], 1000);
		delay(1000);
	}
	delay(1000);
}
