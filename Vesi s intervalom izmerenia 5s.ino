#include "HX711.h"                                // библиотека тензодатчика
 #include <Wire.h>                                 // Библиотека порта
 #include <LiquidCrystal_I2C.h>                    // Библиотека дисплея
 HX711 scale(A1, A0);                              // Выводы для подключения тензодатчика
 LiquidCrystal_I2C lcd(0x3F,16,2);                 // Устанавливаем дисплей
 float myScale;                                    // Переменая для хранения значения веса
 unsigned long currentTime;
 unsigned long loopTime;
 
 void setup() {
 scale.set_scale(-410.4);                          // Калибровочная константа
 scale.tare();                                     // Сбрасываем на 0
 myScale = round(scale.get_units(3));              // Запоминаем среднее значение без груза, но с учетом тары 
 Serial.begin(115200);                             // инициализация порта
 lcd.init();                                       // инициализация ЖК дисплея                   
 lcd.backlight();                                  // Включаем подсветку дисплея
 currentTime = millis();       // считываем время, прошедшее с момента запуска программы
 loopTime = currentTime; 
}

void loop() {
 
myScale = scale.get_units(10);                     // Запоминаем текущий вес  

currentTime = millis();                           // считываем время, прошедшее с момента запуска программы
  if(currentTime >= (loopTime + 5000)){            // поставить вместо 5000 нужное значение времени в милисекундах.
Serial.println(myScale);                           // сейчас стоит 5 секунд.
loopTime = currentTime;
}
char myStr[6]; 
dtostrf(myScale, 5, 0, myStr);                    // Подготовка 5 знакомест
lcd.setCursor(4, 1);                              // Переводим курсор
lcd.print(myStr);                                 // выводим значение веса


}
