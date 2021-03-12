/*

Esse código foi baseado no seguinte site:
http://www.instructables.com/id/Seven-Segment-Display-Tutorial/?ALLSTEPS

E modificado por Álvaro Davi.
A matriz displayletras contem 22 letras (as que sao possiveis de representar).
E para que o código funcione com base no esquemático do site é necessário trocar as portas,
ou seja, iniciar no pino 3 e terminar no 9 - diferente do esquemático original que ia de 2 a 8 - pois
o pino 2 sera usado como input-pullup para um botao.

link para o novo esquemático:
https://www.tinkercad.com/things/4N8W6uJ81Vn

As ligações foram feitas para um display de anodo comum
no caso de um display de catodo comum basta inverter os
valores de 1 para 0 e de 0 para 1

				Pinos do Dislpay:{ A,B,C,D,E,F,G }
				Pinos do Arduino:{ 3,4,5,6,7,8,9 } 
*/
byte displayletras[22][7] = {
								{ 0,0,0,1,0,0,0 }, // = A
								{ 0,0,0,0,0,0,0 }, // = B
								{ 0,1,1,0,0,0,1 }, // = C
								{ 0,0,0,0,0,0,1 }, // = D
								{ 0,1,1,0,0,0,0 }, // = E
								{ 0,1,1,1,0,0,0 }, // = F
								{ 0,1,0,0,0,0,0 }, // = G
								{ 1,0,0,1,0,0,0 }, // = H
								{ 1,1,1,1,0,0,1 }, // = I
								{ 0,0,0,0,0,1,1 }, // = J
								{ 1,1,1,0,0,0,1 }, // = L
								{ 1,1,0,1,0,1,0 }, // = N
								{ 0,0,0,0,0,0,1 }, // = O
								{ 0,0,1,1,0,0,0 }, // = P
								{ 1,1,1,1,0,1,0 }, // = R
								{ 0,1,0,0,1,0,0 }, // = S
								{ 0,0,0,1,1,1,1 }, // = T
								{ 1,1,0,0,0,1,1 }, // = U
								{ 1,0,0,0,0,0,1 }, // = V
								{ 1,0,0,1,0,0,0 }, // = X
								{ 1,0,0,1,1,0,0 }, // = Y
								{ 0,0,1,0,0,1,0 }  // = Z
							};

void setup()
{
	pinMode(2, INPUT_PULLUP);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	attachInterrupt(digitalPinToInterrupt(2), changeButtonState, RISING);
}

void segmentos7(byte digito);

int clicked = 0;
int num = 0;

void loop()
{
	if (clicked == 1)
	{
		delay(500);
		segmentos7(num);
		clicked = 0;
		num++;
	}
	if (num >= 22)
		num = 0;
	delay(2000);
}

void segmentos7(byte digito)
{
	byte pino = 3;
	for (byte segmento = 0; segmento < 7; segmento++)
	{
		digitalWrite(pino, displayletras[digito][segmento]);
		pino++;
	}
}

void changeButtonState()
{
	clicked = 1;
}
