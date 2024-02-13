#pragma once
#include <Arduino.h>
#include <SPI.h>

class Honeywell_SPI {
public:
	Honeywell_SPI(byte SS_pin, float pressureConst, int pMin, int oMin, byte Sum);
	void begin();
	void readSensor();
	void readSensorSum();
	float getPressure();
	float getTemperature();
	int getPressureCount();
	int getTemperatureCount();
	
private:
	void calibration();
	byte _SS_pin;
	int _pMin;
	int _oMin;
	float _pressureConst;
	int pressureCount;
	int temperatureCount;
	float pressure;
	float temperature;
	float pressureCalibrFactor;
	byte _Sum;
};
