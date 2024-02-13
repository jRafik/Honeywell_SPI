#include <Honeywell_SPI.h>                         //подключение библиотеки
Honeywell_SPI PS1(10, 0.915541, -6000, 1638, 10);  // (SS пин, константа, минимальное давление, минимальное значение с датчика, кол-во измерений в одной точке)----Константа равна = (maxPressure-minPressure) / (outputMax - outputMin)
float Pressure;                                    //переменная для давления (можно не создавать- см как выводится температура)

void setup() {
  Serial.begin(9600);  //COM порт
  PS1.begin();         //инициализация датчика
}
void loop() {
  PS1.readSensorSum();           //считать показания с датчика (возмется среднее значение из 10 измерений)
  Pressure = PS1.getPressure();  //расчёт давления
  Serial.print("PS1: ");
  Serial.print(Pressure);  // вывод давления в порт
  Serial.print(" Pa, ");
  Serial.print(PS1.getTemperature());  //вывод температуры в порт
  Serial.println(" C");
}
