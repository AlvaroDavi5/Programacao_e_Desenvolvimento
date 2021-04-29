
// inclusao da biblioteca para o sensor HC-SR04
/* #include <Ultrasonic.h>	 nao necessario */


// definicao de constantes e variaveis
#define TRIGGER_PIN 10 // pino do disparador sonico (PWM)
#define ECHO_PIN 9 // pino do receptor de echo (PWM)
const float VelocidadeSom_mpors = 340; // em metros por segundo
const float VelocidadeSom_mporus = 0.000340; // em metros por microsegundo
float TempoEcho = 0;


// funcao para enviar o pulso de trigger
void DisparaPulsoUltrassonico()
{
	digitalWrite(TRIGGER_PIN, HIGH); // enviar para o pino de trigger um sinal de nivel alto...
	delayMicroseconds(10); // com pelo menos 10us de duracao
	digitalWrite(TRIGGER_PIN, LOW);
}

// funcao para calcular a distancia em metros
float CalculaDistancia(float tempo_us)
{
	return ((tempo_us * VelocidadeSom_mporus) / 2);
}

// funcao 'setup' roda uma vez quando a placa e ligada ou resetada
void setup()
{
	pinMode(TRIGGER_PIN, OUTPUT); // configura pino de Trigger como saida...
	digitalWrite(TRIGGER_PIN, LOW);// e o inicializa com nivel baixo
	pinMode(ECHO_PIN, INPUT); // configura pino Echo como entrada
	Serial.begin(9600); // inicializa a porta serial
	delay(100);
}

// funcao que se repete infinitamente quando a placa e ligada
void loop()
{
	DisparaPulsoUltrassonico(); // envia pulso para o disparar o sensor
	TempoEcho = pulseIn(ECHO_PIN, HIGH); // mede o tempo de duracao do sinal no pino de leitura(us)
	Serial.println("Distancia em metros: ");
	Serial.println(CalculaDistancia(TempoEcho));
	Serial.println("Distancia em centimetros: ");
	Serial.println(CalculaDistancia(TempoEcho) * 100);
	// aguarda um pouco antes de comecar tudo de novo
	delay(500); // delay para evitar queda de desempenho
}

