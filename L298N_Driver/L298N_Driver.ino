// Тестировалось на Arduino IDE 1.0.5
int IN3 = 4; // Input3 подключен к выводу 5 
int IN4 = 5;
int ENB = 6;
void setup()
{
 pinMode (ENB, OUTPUT); 
 pinMode (IN3, OUTPUT);
 pinMode (IN4, OUTPUT);
}
void loop()
{
  // На пару выводов "IN" поданы разноименные сигналы, мотор готов к вращаению
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  // подаем на вывод ENB управляющий ШИМ сигнал 
  analogWrite(ENB,135);
  delay(2000);
  //analogWrite(ENB,105);
  delay(2000);
  //analogWrite(ENB,255);
  //delay(2000);
  // Останавливаем мотор повад на вывод ENB сигнал низкого уровеня. 
  // Состояние выводов "IN" роли не играет.
  analogWrite(ENB,0);
  delay(5000);
}
