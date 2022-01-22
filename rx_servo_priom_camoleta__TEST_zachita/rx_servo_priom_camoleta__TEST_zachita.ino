#include<SPI.h>
#include"nRF24L01.h"
#include "RF24.h"


#include <Servo.h> //используем библиотеку для работы с сервоприводом

int motorX;
int zahita = 0;//защита АКБ


Servo servo; //объявляем переменную servo типа Servo
Servo serv; //объявляем переменную servo типа Servo
Servo motor;//подключаю мотор

RF24 radio(9, 10);
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};

//byte counter;

//byte transmit_data[3];

void setup() {

Serial.begin(9600);
  
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

radio.openReadingPipe(1,address[0]); //Мы труба 0
radio.setChannel(0x6f);//канал

radio.setPALevel (RF24_PA_MAX);//Уровень мощности передатчика MIN LOW HIGH MAX
radio.setDataRate  (RF24_1MBPS);// Скорость обмена (RF24_2MPS, 1MBPS 250KBPS)


radio.powerUp();//начать работу

radio.startListening();//периемник слушает


}

void loop() {

  byte pipeNo, gotByte[4];
//   Serial.println(gotByte);
  while(radio.available(&pipeNo)){
 radio.read(&gotByte,3);//1 это длина вх значения если масив то написать sizeof(gotByte)

  servo.write(gotByte[0]); //ставим вал под 0
 serv.write(gotByte[1]); //ставим вал под 0
 motorX=map(gotByte[2], 0, 100, 800, 2300);//мотор
motor.writeMicroseconds(motorX);


 zahita=analogRead(7);
 Serial.println(zahita);
  }
 delay(10);
}
