/*

			Enderecos do Datasheet

0x68 - Dispositivo MPU-6050

	Acelerometro (HIGH)
		0x3B - Eixo X
		0x3D - Eixo Y
		0x3F - Eixo Z

	Temperatura (HIGH)
		0x41

	Giroscopio (HIGH)
		0x43 - Eixo X
		0x45 - Eixo Y
		0x47 - Eixo Z


*/


#include <Wire.h>


#define TRUE 1
#define FALSE 0

const int16_t I2C_master = 0x42;
const int16_t I2C_slave_MPU = 0x68;
int AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void setup()
{
	Wire.begin(); // inicializar Wire
	Serial.begin(9600);

	Wire.beginTransmission(I2C_slave_MPU); // inicializar MPU-6050
	Wire.write(0x6B); // reset
	Wire.write(0);
	Wire.endTransmission(TRUE);
}

void loop()
{
	Wire.beginTransmission(I2C_slave_MPU); // transmitir para o dispositivo 0x68
	Wire.write(0x3B); // inicializa o eixo X do acelerometro
	Wire.endTransmission(FALSE); // parar transmissao

	Wire.requestFrom(I2C_slave_MPU, 14, TRUE); // solicita os dados do sensor (endereco, numero de bytes, pausa)

	// armazena o valor dos sensores nas variaveis correspondentes, a comecar a ler pelo eixo X do acelerometro
	AcX = Wire.read() << 8 | Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
	AcY = Wire.read() << 8 | Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
	AcZ = Wire.read() << 8 | Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
	Tmp = Wire.read() << 8 | Wire.read(); //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
	GyX = Wire.read() << 8 | Wire.read(); //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
	GyY = Wire.read() << 8 | Wire.read(); //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
	GyZ = Wire.read() << 8 | Wire.read(); //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

	// mostra os valores na serial
	Serial.print("Acel. X = "); Serial.print(AcX);
	Serial.print(" | Y = "); Serial.print(AcY);
	Serial.print(" | Z = "); Serial.print(AcZ);
	Serial.print(" | Gir. X = "); Serial.print(GyX);
	Serial.print(" | Y = "); Serial.print(GyY);
	Serial.print(" | Z = "); Serial.print(GyZ);
	Serial.print(" | Temp = "); Serial.println(Tmp/340.00+36.53);

	delay(300);
}
