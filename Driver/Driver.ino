void setup() {
   Serial.begin(9600);     // запускаем монитор порта
   pinMode(A0, INPUT); // к входу A1 подключаем потенциометр
   
   pinMode(A1, INPUT); // к входу A1 подключаем потенциометр
   
   pinMode(A2, INPUT); // к входу A1 подключаем потенциометр
   
   pinMode(A3, INPUT); // к входу A1 подключаем потенциометр
}

void loop() {
   int val0 = analogRead(A0); // считываем данные с порта A1
   
   int val1 = analogRead(A1); // считываем данные с порта A1
   

   Serial.print(val0);             // выводим данные на монитор порта
        Serial.print("      "); 
   Serial.println(val1);             // выводим данные на монитор порта
      }
