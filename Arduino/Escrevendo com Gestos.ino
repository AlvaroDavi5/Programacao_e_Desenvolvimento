// ADICIONAR
  // verificador de posicao inicial
  // sinalizador de digito inserido e temporizador

/*

	Foram usadas as funcoes getAngle() pois tais combinam
	os dados do giroscopio e do acelerometro e retornam valores com maior tolerancia,
	resolvendo a questao da alta sensibilidade do multi-sensor.


	Em repouso (sensor na horiz.) ---> * sem letras *
	Levemente para a cima         --->  A
	Extremamente para a cima      --->  U
	Levemente para a esquerda     --->  E
	Extremamente para a esquerda  --->  L
	Levemente para a direita      --->  I
	Extremamente para a direita   --->  V
	Levemente para baixo          --->  O
	Extremamente para baixo       ---> \n


	Combinacoes:
		\n + L = C
		\n + E = F
		\n + I = G
		\n + V = S
		L  + U = D
		L  + A = B
		L  + O = R

								14 LETRAS E 1 CARACTERE ESPECIAL (QUEBRA DE LINHA), NO TOTAL

*/

#include <Wire.h>
#include <MPU6050_tockn.h>

#define PIN_LED 6

MPU6050 mpu6050(Wire); // definindo instancia para o tipo MPU6050
float anguloX = 0, anguloY = 0;
char letraX = '\0', letraY = '\0';
long time = millis();


char verificaLetra();
char obterLetraEixoX();
char obterLetraEixoY();


void setup()
{
	Serial.begin(9600); // monitor a 9600 bauds
	Wire.begin(); // inicializar Wire
	mpu6050.begin(); // inicializar MPU6050 usando funcoes do Wire para comunicacao (protocolo I2C)
	mpu6050.calcGyroOffsets(false); // visualizar informacoes de calibracao
}

void loop()
{
	mpu6050.update();

	char letra = ' ';

	if ((millis() - time) >= 700)
	{
		letraX = obterLetraEixoX();
		if (letraX != '\0')
		{
			digitalWrite(LED_BUILTIN, HIGH);
			delay(800);
			digitalWrite(LED_BUILTIN, LOW);
		}
		time = millis();

		letraY = obterLetraEixoY();
		if (letraY != '\0')
		{
			digitalWrite(LED_BUILTIN, HIGH);
			delay(800);
			digitalWrite(LED_BUILTIN, LOW);
		}
		time = millis();
	}


	if (letraX != '\0' || letraY != '\0')
	{
		letra = verificaLetra();

		if (letra != '\0')
			Serial.print(letra);
	}

	letraX = '\0';
	letraY = '\0';
}

char obterLetraEixoX()
{
	anguloX = mpu6050.getAngleX();

	if (anguloX >= 20 && anguloX < 50) // cima 1
		return 'A';
	if (anguloX >= 50) // cima 2
		return 'U';
	if (anguloX <= -20 && anguloX > -50) // baixo 1
		return 'O';
	if (anguloX <= -50) // baixo 2
		return '\n';
	else
		return '\0';
}

char obterLetraEixoY()
{
	anguloY = mpu6050.getAngleY();

	if (anguloY >= 20 && anguloY < 50) // direita 1
		return 'I';
	if (anguloY >= 50) // direita 2
		return 'V';
	if (anguloY <= -20 && anguloY > -50) // esquerda 1
		return 'E';
	if (anguloY <= -50) // esquerda 2
		return 'L';
	else
		return '\0';
}

char verificaLetra()
{
	if (letraX != '\0' && letraY == '\0')
	{
		return letraX;
	}
	if (letraX == '\0' && letraY != '\0')
	{
		return letraY;
	}
	if (letraX != '\0' && letraY != '\0')
	{
		// '\n' no eixo X funciona como alterador
		if (letraX == '\n' && letraY == 'L')
			return 'C';
		if (letraX == '\n' && letraY == 'E')
			return 'F';
		if (letraX == '\n' && letraY == 'I')
			return 'G';
		if (letraX == '\n' && letraY == 'V')
			return 'S';

		// 'L' no eixo Y funciona como alterador
		if (letraY == 'L' && letraX == 'U')
			return 'D';
		if (letraY == 'L' && letraX == 'A')
			return 'B';
		if (letraY == 'L' && letraX == 'O')
			return 'R';
	}
	else // ambas iguais a \0
	{
		return '\0';
	}
}
