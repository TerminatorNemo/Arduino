
#include <Wire.h>
#include <LiquidCrystal.h>   // Лобавляем необходимую библиотеку
// Битовая маска символа улыбки
byte smile[8] =
{
  B00010,
  B00001,
  B11001,
  B00001,
  B11001,
  B00001,
  B00010,
};    
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // (RS, E, DB4, DB5, DB6, DB7)

void setup(){ 
  lcd.begin(16, 2);                  // Задаем размерность экрана

  lcd.createChar(1, smile);          // Создаем символ под номером 1

  lcd.setCursor(0, 0);               // Устанавливаем курсор в начало 1 строки
  lcd.print("\1");                   // Выводим смайлик (символ под номером 1) - "\1"
      }

void loop(){
}
