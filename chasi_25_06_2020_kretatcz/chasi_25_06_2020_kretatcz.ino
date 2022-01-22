//Пин подключен к ST_CP входу 74HC595
int latchPin = 5;
//Пин подключен к SH_CP входу 74HC595
int clockPin = 4;
//Пин подключен к DS входу 74HC595
int dataPin = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);


}

void loop() {

  //  delay(20000);
    // устанавливаем синхронизацию "защелки" на LOW
    //digitalWrite(latchPin, HIGH);
    // передаем отсчет для вывода на зеленые светодиоды
   //shiftOut(dataPin, clockPin, MSBFIRST, 0); 
 //  delay(100);
    // передаем обратный отсчет  для вывода на красные светодиоды
   // shiftOut(dataPin, clockPin, LSBFIRST, 0b10000000);
    //"защелкиваем" регистр, тем самым устанавливая значения на выходах
   digitalWrite(latchPin, LOW);


    
    // пауза перед следующей итерацией
    
}
