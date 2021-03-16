/*
 __________________________________________
| Curso Arduino 5 - Display de 7 Segmentos |
|				 OnDuino				   |
|	http://www.onduino.blogspot.com.br	   |
|__________________________________________|

Esse código foi baseado no seguinte site:
http://www.instructables.com/id/Seven-Segment-Display-Tutorial/?ALLSTEPS
E modificado por Álvaro Davi.

As ligações foram feitas para um display de anodo comum
no caso de um display de catodo comum basta inverter os
valores de 1 para 0 e de 0 para 1

				Pinos do Dislpay:{ A,B,C,D,E,F,G }
				Pinos do Arduino:{ 2,3,4,5,6,7,8 } */
byte display7segmentos[10][7] = {
									{ 0,0,0,0,0,0,1 }, // = 0
									{ 1,0,0,1,1,1,1 }, // = 1
									{ 0,0,1,0,0,1,0 }, // = 2
									{ 0,0,0,0,1,1,0 }, // = 3
									{ 1,0,0,1,1,0,0 }, // = 4
									{ 0,1,0,0,1,0,0 }, // = 5
									{ 0,1,0,0,0,0,0 }, // = 6
									{ 0,0,0,1,1,1,1 }, // = 7
									{ 0,0,0,0,0,0,0 }, // = 8
									{ 0,0,0,1,1,0,0 }  // = 9
								};

void setup() {								
	pinMode(2, OUTPUT);	 
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
}

void segmentos7(byte digito) {
	byte pino = 2;
	for (byte segmento = 0; segmento < 7; segmento++) {
		digitalWrite(pino, display7segmentos[digito][segmento]);
		pino++;
	}
}

void loop() {
	for (byte num = 0; num < 10; num++) {
	 delay(1000);
	 segmentos7(num); 
	}
	delay(5000);
}
