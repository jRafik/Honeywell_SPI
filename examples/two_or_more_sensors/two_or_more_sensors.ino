#include <Honeywell_SPI.h>  //подключение библиотеки
Honeywell_SPI PS1(10, 0.915541, -6000, 1638, 10);  // (SS пин, константа, минимальное давление, минимальное значение с датчика,кол-во измерений в одной точке)----Константа равна = (maxPressure-minPressure) / (outputMax - outputMin)
Honeywell_SPI PS2(9, 0.915541, -6000, 1638, 10);  //второй датчик

void setup() {
  Serial.begin(9600); //COM порт
  PS1.begin();  //инициализация датчика 1
  PS2.begin();  //инициализация датчика 2
}

void loop() {
  PS1.readSensorSum(); //считать УСРЕДНЕННЫЕ показания с датчика 1 
  Serial.print("PS1: ");
  Serial.print(PS1.getTemperature()); // вывод значения давления 1 
  Serial.print(" C, ");
  Serial.print(PS1.getPressure()); //вывод значения температуры 1
  Serial.print(" Pa");

  PS2.readSensor(); //считать показания с датчика 1
  Serial.print("PS2: ");
  Serial.print(PS2.getTemperature()); // вывод значения давления 1 
  Serial.print(" C, ");
  Serial.print(PS2.getPressure()); //вывод значения температуры 1
  Serial.print(" Pa");
}
