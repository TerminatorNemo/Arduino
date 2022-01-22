#include<SPI.h>
#include"nRF24L01.h"
#include "RF24.h"




RF24 radio(9, 10);
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};

//byte counter;

//byte transmit_data[3];

void setup() {


  
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

 pinMode(2, OUTPUT); 
}

void loop() {

  byte pipeNo, gotByte;
//   Serial.println(gotByte);
  while(radio.available(&pipeNo)){
 radio.read(&gotByte,1);//1 это длина вх значения если масив то написать sizeof(gotByte)
  Serial.print("Prinal - ");
  Serial.println(gotByte);

  if(gotByte==1)    digitalWrite(2, HIGH); 
 if(gotByte==0)    digitalWrite(2, LOW); 

  
  }
 delay(10);
}
