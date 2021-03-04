/*

Iniciar programa com:

	o semáforo para carros no verde
	a luz para pedestres no vermelho

Ao pressionar o botão:

	verificar se greenTime, transcorreu com o semáforo para carros no verde e:
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
#define BUTTON 4
#define RED_Car 12
#define YELLOW_Car 11
#define GREEN_Car 10
#define RED_Ped 9
#define GREEN_Ped 8

// timeset
unsigned long startTime = millis(); // time after start (in miliseconds)

// time to cars (in miliseconds, to use like seconds)
const float greenTime = 1000.00; // 6000.00
const float yellowTime = 100.00; // 1000.00
// time to pedestrians (in miliseconds, to use like seconds)
const float crossTime = 500.00; // 3000.00


// functions prototype
int init(int clk);
int comparePassedTime(float compareTime);


void setup()
{
	// setup pinmodes
	pinMode(BUTTON, INPUT_PULLUP);
	pinMode(RED_Car, OUTPUT);
	pinMode(YELLOW_Car, OUTPUT);
	pinMode(GREEN_Car, OUTPUT);
	pinMode(RED_Ped, OUTPUT);
	pinMode(GREEN_Ped, OUTPUT);

	// serial connection
	Serial.begin(9600); // start serial con. in 9600 baunds
}

void loop()
{
	int clicked = 0;

	while (! clicked)
	{
		digitalWrite(GREEN_Car, HIGH);
		digitalWrite(RED_Ped, HIGH);

		clicked = digitalRead(BUTTON);
		if (clicked)
			clicked = init(clicked);
	}
}

int init(int clk)
{
	while (clk)
	{
		if (comparePassedTime(greenTime))
		{
			digitalWrite(GREEN_Car, LOW);
			digitalWrite(YELLOW_Car, HIGH);

			if (comparePassedTime(yellowTime))
			{
				digitalWrite(YELLOW_Car, LOW);
				digitalWrite(RED_Car, HIGH);
				digitalWrite(RED_Ped, LOW);
				digitalWrite(GREEN_Ped, HIGH);
				delay(crossTime);
				clk = 0;
			}
		}
	}

	return clk;
}

int comparePassedTime(float compareTime)
{
	if ((millis() - startTime) < compareTime)
	{
		startTime = millis();
		return 0;
	}
	else // if the time goes passed
	{
		startTime = millis();
		return 1;
	}
}
