#include<SPI.h>
#include"nRF24L01.h"
#include "RF24.h"
#include <LiquidCrystal.h>


LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
RF24 radio(9, 10);
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};

byte counter[4];
 int val;



int x1;
int x2;
int x3;

int but;
 
//byte transmit_data[3];

void setup() {


  
  
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
 lcd.begin(16, 2);//запускаю 1602
 lcd.print("Terminator Nemo");
 if(analogRead(2)<5&&but<10)menu();
}

void loop() {


  //===============1602
but = analogRead(3);
   //lcd.setCursor(0, 1);
 //lcd.print(but);

 
if(but<3){
   lcd.setCursor(0, 1);
 lcd.print(counter[2]);
 
 lcd.print(" ");
 
 lcd.print(counter[0]);
 
 lcd.print(" "); 

 lcd.print(counter[1]);

  lcd.print(" ");

   lcd.print(but);
  } 
//=================1602


     x1 = map(analogRead(0), 290, 490, 0, 150);//поворот
     x2 = map(analogRead(1), 550, 270, 0, 150);//стабилизатор
     x3 = map(analogRead(2), 3, 1023, 0, 100);//мотор




if(x1>150)x1=150;
if(x2>150)x2=150;




     counter[0] = x1;
     counter[1] = x2;
     counter[2] = x3;

   
 radio.write(&counter,4);
 
 //counter++;
 delay(10);
//   Serial.println(counter);
}


void menu(){
   lcd.begin(16, 2);//запускаю 1602
 lcd.print("Menu");
while(1>0){


   if(analogRead(2)>20){
     lcd.setCursor(0, 1);
     lcd.print("                ");
     
     lcd.setCursor(0, 1);
     lcd.print("3");
delay(1000);
     lcd.setCursor(0, 1);
     lcd.print("2");
delay(1000);
     lcd.setCursor(0, 1);
     lcd.print("1");
delay(1000);
break ;        
    }
}


  lcd.begin(16, 2);//запускаю 1602
 lcd.print("Terminator Nemo");
  }
