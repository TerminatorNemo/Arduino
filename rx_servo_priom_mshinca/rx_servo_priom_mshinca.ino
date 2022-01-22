#include<SPI.h>
#include"nRF24L01.h"
#include "RF24.h"


#include <Servo.h> //используем библиотеку для работы с сервоприводом

int motorX;

Servo servo; //объявляем переменную servo типа Servo
Servo serv; //объявляем переменную servo типа Servo
Servo motor;//подключаю мотор

RF24 radio(9, 10);
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};




int Spede=0;

void setup() {



  
servo.attach(3); //привязываем привод к порту 10





 pinMode (4, OUTPUT); 
 pinMode (5, OUTPUT);
 pinMode (6, OUTPUT);
  
  Serial.begin(9600);
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
  while(radio.available(&pipeNo)){
  radio.read(&gotByte,3);//1 это длина вх значения если масив то написать sizeof(gotByte)

  servo.write(map(gotByte[0],0,150,10,0)); //ставим вал под 0

 motorX=gotByte[2];
 
if(motorX>40){
    digitalWrite (4, HIGH);
  digitalWrite (5, LOW);
  Spede=map(motorX,40,100,130,255);//135
  analogWrite(6,Spede);
  }else if(motorX>30&&motorX<41){
  analogWrite(6,0);
   }else{
     digitalWrite (5, HIGH);
  digitalWrite (4, LOW);
  Spede=map(motorX,0,30,185,130);
  analogWrite(6,Spede);
 }



  }
 delay(10);
}
