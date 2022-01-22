
#include"nRF24L01.h"
#include "RF24.h"


#include <Servo.h> //используем библиотеку для работы с сервоприводом

int times;
int times1;
int motorX;
int zahita = 0;//защита АКБ
int pisk = 4;//пин пищалки
int flag = 0;//флаг для остановки мотора

Servo servo; //объявляем переменную servo типа Servo
Servo serv; //объявляем переменную servo типа Servo
Servo motor;//подключаю мотор

RF24 radio(9, 10);
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};

//byte counter;

//byte transmit_data[3];

void setup() {
  //   Serial.begin(9600);//====================================================================
  // Serial.println(   "stert");//============================================

  pinMode(pisk, OUTPUT);
  digitalWrite(pisk, LOW);
  //Serial.begin(9600);

  servo.attach(5); //привязываем привод к порту 10
  serv.attach(3); //привязываем привод к порту 10
  motor.attach(2);
  motor.writeMicroseconds(2300);
  delay(3000);
  motor.writeMicroseconds(800);
  delay(6000);



  radio.begin(); //Активировать модуль
  radio.setAutoAck(1);//1 прием, 0 передача
  radio.setRetries(0, 15); //Время между пропыткой достучатся, число попиток
  radio.enableAckPayload();//разрешить отсылку данных в ответ на вх сиграл
  radio.setPayloadSize(32);//размер пакета в байтах

  radio.openReadingPipe(1, address[0]); //Мы труба 0
  radio.setChannel(0x6f);//канал

  radio.setPALevel (RF24_PA_MAX);//Уровень мощности передатчика MIN LOW HIGH MAX
  radio.setDataRate  (RF24_1MBPS);// Скорость обмена (RF24_2MPS, 1MBPS 250KBPS)


  radio.powerUp();//начать работу

  radio.startListening();//периемник слушает
  // Serial.println(   "stop");//============================================

}

void loop() {


  byte pipeNo, gotByte[4];
  while (radio.available(&pipeNo)) {


    radio.read(&gotByte, 4); //1 это длина вх значения если масив то написать sizeof(gotByte)

    servo.write(map(gotByte[0], 0, 150, 30, 130));
    serv.write( map(gotByte[1], 0, 150, 20, 165));
    motorX = map(gotByte[2], 0, 100, 800, 2300); //мотор

    if (flag == 0) {
      motor.writeMicroseconds(motorX);//Кручу мотор
    }

    // Serial.println(   gotByte[1]);//============================================
    zahita = analogRead(7);

    if (zahita < 50) {
      digitalWrite(pisk, HIGH);
      flag = 1;
      motor.writeMicroseconds(800);//Кручу мотор
    }
   times=millis(); 
  }
  times1=millis(); 
  if(times1-times>500){
  motor.writeMicroseconds(800);
  }
}
