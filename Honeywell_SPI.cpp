#include <Honeywell_SPI.h>

Honeywell_SPI::Honeywell_SPI(byte SS_pin, float pressureConst, int pMin, int oMin, byte Sum){
	_SS_pin = SS_pin;
	_pMin = pMin;
	_oMin = oMin;
	_pressureConst = pressureConst;
	_Sum = Sum;
}

void Honeywell_SPI::begin() {	//инициализация
	SPI.begin();
	pinMode(_SS_pin, OUTPUT);
	digitalWrite(_SS_pin, HIGH);
	calibration();
}

void Honeywell_SPI::readSensor() {	//считать показания с датчика
	byte b1;
	byte b2;
	byte b3;
	byte b4;
	digitalWrite(_SS_pin, LOW);
	b1 = SPI.transfer(0);
	b2 = SPI.transfer(0);
	b3 = SPI.transfer(0);
	b4 = SPI.transfer(0);
	digitalWrite(_SS_pin, HIGH);
	pressureCount = (b1 << 8) | b2;
	temperatureCount = ((b3 << 8) | b4) >> 5;
}

void Honeywell_SPI::readSensorSum() {	//считать усредненные показания с датчика
	byte b1;
	byte b2;
	byte b3;
	byte b4;
	int pressureVals [_Sum];
	unsigned long pressureSum = 0;
	for (byte i = 0; i < _Sum; i++) {
	digitalWrite(_SS_pin, LOW);
	b1 = SPI.transfer(0);
	b2 = SPI.transfer(0);
	digitalWrite(_SS_pin, HIGH);
	pressureVals [i] = (b1 << 8) | b2;
	pressureSum = pressureSum + pressureVals [i];
	delay (1);
	}
	pressureCount = pressureSum / _Sum;
	digitalWrite(_SS_pin, LOW);
	b1 = SPI.transfer(0);
	b2 = SPI.transfer(0);
	b3 = SPI.transfer(0);
	b4 = SPI.transfer(0);
	digitalWrite(_SS_pin, HIGH);
	temperatureCount = ((b3 << 8) | b4) >> 5;
}

float Honeywell_SPI::getPressure() {	//давление
    pressure = ((pressureCount - _oMin) * _pressureConst) + _pMin - pressureCalibrFactor;  //вычисление давления (формулы в документации к датчику)
    if (pressure < 5.0 && pressure > -5.0) pressure = 0;
	return (pressure);
}

void Honeywell_SPI::calibration() {	//калибровка
	byte b1;
	byte b2;
	int pressureVals [10];
	unsigned long pressureSum = 0;
	for (byte i = 0; i < 10; i++) {
	digitalWrite(_SS_pin, LOW);
	b1 = SPI.transfer(0);
	b2 = SPI.transfer(0);
	digitalWrite(_SS_pin, HIGH);
	pressureVals [i] = (b1 << 8) | b2;
	pressureSum = pressureSum + pressureVals [i];
	delay (1);
	}
	pressureCount = pressureSum / 10;
	pressureCalibrFactor = ((pressureCount - _oMin) * _pressureConst) + _pMin;
}


float Honeywell_SPI::getTemperature() {	//температура
    temperature = (temperatureCount * 0.097704) - 50.0;
	return (temperature);
}

int Honeywell_SPI::getPressureCount(){	//вывод необработанного значения давления
	return (pressureCount);
}

int Honeywell_SPI::getTemperatureCount(){	//вывод необработанного значения температуры
	return (temperatureCount);
}

