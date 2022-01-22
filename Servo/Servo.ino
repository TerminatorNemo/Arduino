#include <Servo.h> //используем библиотеку для работы с сервоприводом

Servo servo; //объявляем переменную servo типа Servo
int led = 13;
void setup() //процедура setup
{
pinMode(led, OUTPUT); 
servo.attach(5); //привязываем привод к порту 10

}

void loop() //процедура loop

{

servo.write(0); //ставим вал под 0

delay(1000); //ждем 2 секунды

digitalWrite(led, HIGH); 

servo.write(90); //ставим вал под 180

delay(1000); //ждем 2 секунды

digitalWrite(led, LOW);
}
