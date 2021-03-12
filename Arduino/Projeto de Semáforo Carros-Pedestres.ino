/*
 Projeto Semáforo para Carros e Pedestres
 Álvaro Davi S. Alves - 2020101874
 Engenharia de Computação - UFES

Iniciar programa com:

	o semáforo para carros no verde
	a luz para pedestres no vermelho

Ao pressionar o botão:

	verificar se, greenTime transcorreu com o semáforo para carros no verde e:
		se sim:
			o semáforo para carros vai de verde para amarelo e depois para vermelho
			em seguida, o semáforo para pedestres vai para verde
		se não:
			armazenar a informação, de modo que o pedestre não precise apertar o botão novamente para atravessar
			assim que o tempo definido por greenTime terminar, as luzes dos semáforos para pedestres devem trocar

Ao final de um intervalo de tempo definido em crossTime:
	a luz verde para pedestres pisca, acendendo e apagando, como um aviso (o tempo definido em crossTime inclui o período do aviso, e este deve ser proporcional ao valor da variável)
	Então, a luz verde do semáforo de pedestres apaga
	a vermelha para pedestres acende
	a luz para os veículos vai de vermelho para verde, permitindo novamente o fluxo do tráfego.

*/


// pins
#define BUTTON 2
#define RED_Car 12
#define YELLOW_Car 11
#define GREEN_Car 10
#define RED_Ped 9
#define GREEN_Ped 8


// timeset
unsigned long startTime = millis(); // time after start (in miliseconds)
// button event
int clicked = 0;
// time to cars (in miliseconds, to use like seconds)
const float greenTime = 1800.00; // 6000.00 (to real Arduino)
const float yellowTime = 600.00; // 1000.00 (to real Arduino)
// time to pedestrians (in miliseconds, to use like seconds)
const float crossTime = 1400.00; // 3000.00 (to real Arduino)


// functions prototype
int comparePassedTime(float compareTime);
void blink(float delayTime);
void changeButtonState();


void setup()
{
	// setup pinmodes
	pinMode(BUTTON, INPUT_PULLUP);
	pinMode(RED_Car, OUTPUT);
	pinMode(YELLOW_Car, OUTPUT);
	pinMode(GREEN_Car, OUTPUT);
	pinMode(RED_Ped, OUTPUT);
	pinMode(GREEN_Ped, OUTPUT);

	// button event-listenner
	attachInterrupt(digitalPinToInterrupt(BUTTON), changeButtonState, RISING);

	// serial connection
	Serial.begin(9600); // start serial con. with 9600 baunds
}

void loop()
{
	digitalWrite(RED_Ped, HIGH);
	digitalWrite(GREEN_Car, HIGH);

	if (clicked && comparePassedTime(greenTime))
	{
		digitalWrite(GREEN_Car, LOW);
		digitalWrite(YELLOW_Car, HIGH);
		delay(yellowTime);
		digitalWrite(YELLOW_Car, LOW);
		digitalWrite(RED_Car, HIGH);
		digitalWrite(RED_Ped, LOW);
		digitalWrite(GREEN_Ped, HIGH);
		delay(0.84 * crossTime);
		blink(0.16 * crossTime);
		startTime = millis();
		digitalWrite(GREEN_Ped, LOW);
		digitalWrite(RED_Car, LOW);
		clicked = 0;
	}
}

int comparePassedTime(float compareTime)
{
	Serial.print(millis()); Serial.print(" - "); Serial.print(startTime);
	Serial.print(" = "); Serial.print(millis()-startTime);
	Serial.print('\n');
	if ((millis() - startTime) > compareTime)
		Serial.print("Tempo alcancado! \n");

	if ((millis() - startTime) < compareTime)
	{
		return 0;
	}
	else // if the time goes passed
	{
		startTime = millis();
		return 1;
	}
}

void blink(float delayTime)
{
	digitalWrite(GREEN_Ped, LOW);
	delay(delayTime);
	digitalWrite(GREEN_Ped, HIGH);
	delay(delayTime);
	digitalWrite(GREEN_Ped, LOW);
	delay(delayTime);
	digitalWrite(GREEN_Ped, HIGH);
	delay(delayTime);
	digitalWrite(GREEN_Ped, LOW);
	delay(delayTime);
	digitalWrite(GREEN_Ped, HIGH);
	delay(delayTime);
}

void changeButtonState()
{
	clicked = 1;
}
