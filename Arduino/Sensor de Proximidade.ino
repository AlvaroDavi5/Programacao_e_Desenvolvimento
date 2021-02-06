#define SIGNAL A0
#define RED 6
#define GREEN 5
#define BLUE 3

void setup()
{
	Serial.begin(9600); // iniciar troca de dados com o monitor serial a 9600 baunds
	pinMode(SIGNAL, INPUT);
	pinMode(RED, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(BLUE, OUTPUT);
}

void loop()
{
	long duracao = pulseIn(SIGNAL, HIGH); // calculo da duracao para o recebimento do ultrassom
	long proximidade = duracao / 29 / 2; // converter de milisegundos para centimetros

	Serial.print("Proximidade: ");
	Serial.print(proximidade);
	Serial.println("cm");
	delay(4);

	if (proximidade <= 85)
	{
		digitalWrite(RED, LOW);
		digitalWrite(GREEN, LOW);
		digitalWrite(BLUE, HIGH);
	}
	else if (proximidade > 85 && proximidade <= 170)
	{
		digitalWrite(RED, LOW);
		digitalWrite(BLUE, LOW);
		digitalWrite(GREEN, HIGH);
	}
	else // proximidade > 170
	{
		digitalWrite(GREEN, LOW);
		digitalWrite(BLUE, LOW);
		digitalWrite(RED, HIGH);
	}
}
