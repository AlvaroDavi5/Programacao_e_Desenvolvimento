// Link para o esquemático do ThinkerCad feito por Álvaro Davi com base no primeiro modelo:
// https://www.tinkercad.com/things/ls7rwvZyjYI


/*

TEMPERATURE SENSOR

	Vamos usar "serial monitor" para ler a temperatura do sensor.
	O ThinkerCad oferece o sensor TMP36. 
	Um sensor de temperatura cuja a voltagem da saída é proporcional a tempertatura ambiente.

	Datasheet:
	https://www.analog.com/media/en/technical-documentation/data-sheets/TMP35_36_37.pdf

Conexões que devem ser feitas:

	Sempre faça com o Arduino desligado, da esquerda para direita:
	5V, SIGNAL, and GND.

	Conectar o pino 5V em 5 Volts (5V) do Arduino.
	Conectar o pino SIGNAL (Vout) em sensorTemp (Analogico 0).
	Conectar o pino GND em ground (GND).
	Conectar os terminais (RED, BLUE, GREEN) do LED RGB nos pinos Digitais 4, 5 e 6 respectivamente.
	Conectar o terminal GND no pino ground (GND).

*/

/*

no mundo real, é comum os fabricantes proverem uma bibliotecas que permitem usar os sensores sem precisar entrar nos detalhes de eletronica

#include <TMP36.h>  inclusão de biblioteca

TMP36 myTMP36(sensorTemp, 5.0);  define o pino analógico utilizado pelo sensor e define a tensão de referência (5v ou 3.3v) caso utilizado a biblioteca

*/


#define pinAzul 4
#define pinVerde 5
#define pinVermelho 7
#define sensorTemp A0

void readTemp(float temp);
void serCor(int r, int g, int b);

void setup()
{
	pinMode(sensorTemp, INPUT);

	pinMode(pinAzul, OUTPUT);
	pinMode(pinVerde, OUTPUT);
	pinMode(pinVermelho, OUTPUT);

	Serial.begin(9600); // comunicacao com o monitor serial a 9600 baunds
}

void loop()
{
	serCor(0, 0, 0); // inicia o led apagado

	//float celsius = myTMP36.getTempC(); //OBTIDA ATRAVÉS DA FUNÇÃO myTMP36.getTempC() da biblioteca

	/*
	A porta analogica tem precisao de 10 bits, isto eh, vai de 0 a 1023 (2^10)
	AnalogRead retorna um valor entre 0 e 1023
	Para saber a voltagem basta multiplicar por (5/1023):
	*/
	float voltagem = analogRead(sensorTemp) * 0.004882814;

	/*
	Essa formula vem do datasheet do sensor
	https://www.analog.com/media/en/technical-documentation/data-sheets/TMP35_36_37.pdf
	ver pagina 8
	*/
	float celsius = (voltagem - 0.5) * 100.0;

	readTemp(celsius);

	/*
	A função map permite fazer o mapeamento direto entre faixas de valores
	Formula comumente encontrad em fóruns para conversão - vamos ver os erros que ela introduz.
	*/

	//float celsius = map(((analogRead(sensorTemp) - 20 ) * 3.04), 0, 1023, -40, 125);

	Serial.print("Voltagem: "); // IMPRIME O TEXTO NO MONITOR SERIAL
	Serial.println(voltagem); // IMPRIME NO MONITOR SERIAL A a voltagem
	Serial.print("Celsius: "); // IMPRIME O TEXTO NO MONITOR SERIAL
	Serial.println(celsius); // IMPRIME NO MONITOR SERIAL A TEMPERATURA MEDIDA
	delay(1000); // INTERVALO DE 1 SEGUNDO
}

void readTemp(float temp)
{
	if (temp < 10)
	{
		serCor(0, 0, 1); // AZUL
	}
	else if (temp >= 10 && temp < 20)
	{
		serCor(0, 1, 0); // VERDE
	}
	else if (temp >= 20 && temp < 30)
	{
		serCor(1, 1, 0); // AMARELO
	}
	else /* temp > 30 */
	{
		serCor(1, 0, 0); // VERMELHO
	}
}

void serCor(int r, int g, int b)
{
	digitalWrite(pinVermelho, r);
	digitalWrite(pinVerde, g);
	digitalWrite(pinAzul, b);
}
