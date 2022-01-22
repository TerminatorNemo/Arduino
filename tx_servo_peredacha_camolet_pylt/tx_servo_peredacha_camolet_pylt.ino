#include<SPI.h>
#include"nRF24L01.h"
#include "RF24.h"

RF24 radio(9, 10);
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};

byte counter[4];
 int val;
//byte transmit_data[3];

void setup() {
   Serial.begin(9600);
  radio.begin(); //Активировать модуль
radio.setAutoAck(1);//1 прием, 0 передача
radio.setRetries(0, 15); //Время между пропыткой достучатся, число попиток
radio.enableAckPayload();//разрешить отсылку данных в ответ на вх сиграл
radio.setPayloadSize(32);//размер пакета в байтах

radio.openWritingPipe(address[0]); //Мы труба 0
radio.setChannel(0x6f);//канал

radio.setPALevel (RF24_PA_MAX);//Уровень мощности передатчика MIN LOW HIGH MAX
radio.setDataRate  (RF24_1MBPS);// Скорость обмена (RF24_2MPS, 1MBPS 250KBPS)


radio.powerUp();//начать работу
radio.stopListening();//передатчик не слушает
}

void loop() {
//val=analogRead(0);
     counter[0] = map(analogRead(6), 0, 1023, 45, 120);//поворот
     counter[1] = map(analogRead(7), 1023, 0, 20, 165);//стабилизатор
     counter[2] = map(analogRead(4), 0, 1023, 0, 100);//мотор

     Serial.println(counter[1]);
 radio.write(&counter,4);
 
 //counter++;
 delay(10);
//   Serial.println(counter);
}
