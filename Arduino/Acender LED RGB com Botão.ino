// definicao de variaveis
int botao = 8;
int red = 7, green = 4, blue = 2;
bool estadoLED = 0;

// preparacao de ambiente para entradas e saidas
void setup()
{
	pinMode(botao, INPUT_PULLUP); // pino do botao sera lido como entrada (solto ou apertado)
	pinMode(red, OUTPUT); // outros pinos serao saidas para as luzes em cores
	pinMode(green, OUTPUT);
	pinMode(blue, OUTPUT);
}

void loop()
{
	// comando para ler entrada digital
	if (digitalRead(botao) == LOW) // se o botao for pressionado
	{
	estadoLED = !estadoLED; // troca de LIGADO para DESLIGADO

	// acende e apaga LED vermelho com delay
	digitalWrite(red, HIGH);
	delay(1000); // espera por 1000 milisegundos
	digitalWrite(red, LOW);
	delay(1000); // espera por 1000 milisegundos


	// acende e apaga LED verde com delay
	digitalWrite(green, HIGH);
	delay(1000); // espera por 1000 milisegundos
	digitalWrite(green, LOW);
	delay(1000); // espera por 1000 milisegundos


	// acende e apaga LED azul com delay
	digitalWrite(blue, HIGH);
	delay(1000); // espera por 1000 milisegundos
	digitalWrite(blue, LOW);
	delay(1000); // espera por 1000 milisegundos
	}
}
