
#define led 4  //объявление переменной целого типа, содержащей номер порта к которому мы подключили второй провод
#define time_ 1
void setup()  //обязательная процедура setup, запускаемая в начале программы; объявление процедур начинается словом void

{

pinMode(led, OUTPUT); //объявление используемого порта, led - номер порта, второй аргумент - тип использования порта - на вход (INPUT) или на выход (OUTPUT)
Serial.begin(9600);
}

void loop() //обязательная процедура loop, запускаемая циклично после процедуры setup

{

digitalWrite(led, LOW); //эта команда используется для включения или выключения напряжения на цифровом порте; led - номер порта, второй аргумент - включение (HIGH) или выключение (LOW)
   Serial.println(led); 
   delay(time_); 
   digitalWrite(led, HIGH); 
   delay(time_);
/*
delay(1000); //эта команда используется для ожидания между действиями, аргумент - время ожидания в миллисекундах

digitalWrite(led, LOW);

delay(1000);
*/
}
