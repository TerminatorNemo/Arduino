#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#include<SPI.h>
#include"nRF24L01.h"
#include "RF24.h"
#include <LiquidCrystal.h>
#include <EEPROM.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
RF24 radio(9, 10);
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};
byte counter[4];


int val;
/*
https://www.youtube.com/watch?v=ypH3W8r41Cw
4:40 
ограничение значений!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



*/
int x1;
int x2;
int x3;

int but;


int a=0;
int b=0;
int c=0;
int d=0;


void setup() {
// Serial.begin(9600);//==============================================================================================================================================

  
  
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


a=EEPROM.read(1); 
b=EEPROM.read(2); 
c=EEPROM.read(3); 
d=EEPROM.read(4); 



     counter[0] = b;
     counter[1] = c;
     counter[2] = 0;


  pinMode(8, INPUT);   
lcd.begin(16, 2);//запускаю 1602
lcd.print("Terminator Nemo");
but = digitalRead(8);
if(analogRead(2)<5&&but<10)menu();




}

void loop() {
x1 = map(analogRead(0), 290, 560, a, b);//поворот
x2 = map(analogRead(1), 550, 270, c, d);//стабилизатор
x3 = map(analogRead(2), 3, 1023, 0, 100);//мотор
but = digitalRead(8);
//constrain(x1, a, b);


if(x1>180)x1=180;
if(x2>180)x2=180;
if(x1<0)x1=0;
if(x2<0)x2=0;




     counter[0] = x1;
     counter[1] = x2;
     counter[2] = x3;

   
writet();
}

void writet(){  

  radio.write(&counter,4);
  

  delay(10);}

void menu(){
 lcd.setCursor(0, 0);
 lcd.print("Menu            ");


/*виыод даных которые отправлю
   lcd.setCursor(0, 1);
 lcd.print(counter[2]);
 
 lcd.print(" ");
 
 lcd.print(counter[0]);
 
 lcd.print(" "); 

 lcd.print(counter[1]);

  lcd.print(" ");

   lcd.print(but);
*/
 
while(1>0){

//пункт 1=======================================
while(1>0){  

    lcd.setCursor(7, 0);
    lcd.print("1");


    lcd.setCursor(0, 1);
    lcd.print("            ");
    lcd.setCursor(2, 1);
    lcd.print(a);
    lcd.print("  ");//===================================
       lcd.print(digitalRead(8));   //============================


    if(analogRead(1)>450)a++;
    if(analogRead(1)<300)a--;
    if(a>180)a=a-180;
    if(a<0)a=a+180;

    if(analogRead(0)>480){
       counter[1] = a;
       writet();

        
       lcd.setCursor(11, 1);
       lcd.print("a");
      }
    delay(150);


  if(analogRead(2)>20){

     lcd.setCursor(0, 1);
     lcd.print("1");
     delay(1000);
     lcd.setCursor(0, 1);
     lcd.print("                ");
     break ;        
    }

    
}
//пункт 1=======================================



//пункт 2=======================================
while(1>0){  

    lcd.setCursor(7, 0);
    lcd.print("2");


    lcd.setCursor(0, 1);
    lcd.print("            ");
    lcd.setCursor(2, 1);
    lcd.print(b);

    if(analogRead(1)>450)b++;
    if(analogRead(1)<300)b--;
    if(b>180)b=b-180;
    if(b<0)b=b+180;

    if(analogRead(0)>480){
       counter[1] = b;
       writet();
       lcd.setCursor(11, 1);
       lcd.print("b");
      }
    delay(150);


  if(analogRead(2)>20){

     lcd.setCursor(0, 1);
     lcd.print("2");
     delay(1000);
     lcd.setCursor(0, 1);
     lcd.print("                ");
     break ;        
    }

    
}
//пункт 2=======================================




//пункт 3=======================================
while(1>0){  

    lcd.setCursor(7, 0);
    lcd.print("3");


    lcd.setCursor(0, 1);
    lcd.print("            ");
    lcd.setCursor(2, 1);
    lcd.print(c);

    if(analogRead(1)>450)c++;
    if(analogRead(1)<300)c--;
    if(c>180)c=c-180;
    if(c<0)c=c+180;

    if(analogRead(0)>480){
       counter[0] = c;
       writet();
       lcd.setCursor(11, 1);
       lcd.print("c");
      }
    delay(150);


  if(analogRead(2)>20){

     lcd.setCursor(0, 1);
     lcd.print("3");
     delay(1000);
     lcd.setCursor(0, 1);
     lcd.print("                ");
     break ;        
    }

    
}
//пункт 3=======================================




//пункт 4=======================================
while(1>0){  

    lcd.setCursor(7, 0);
    lcd.print("4");


    lcd.setCursor(0, 1);
    lcd.print("            ");
    lcd.setCursor(2, 1);
    lcd.print(d);

    if(analogRead(1)>450)d++;
    if(analogRead(1)<300)d--;
    if(d>180)d=d-180;
    if(d<0)d=d+180;

    if(analogRead(0)>480){
       counter[0] = d;
       writet();
       lcd.setCursor(11, 1);
       lcd.print("d");
      }
    delay(150);


  if(analogRead(2)>20){

     lcd.setCursor(0, 1);
     lcd.print("4");
     delay(1000);
     lcd.setCursor(0, 1);
     lcd.print("                ");
     break ;        
    }

    
}
//пункт 4=======================================





//отсчет+выход=====================
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
     EEPROM.update(1,a);
     EEPROM.update(2,b);
     EEPROM.update(3,c);
     EEPROM.update(4,d);
     lcd.setCursor(0, 1);
     lcd.print("                ");
     break ;        
    }
//==================================    
}


lcd.setCursor(0, 0);
lcd.print("Terminator Nemo ");
  }



///=========================






//================================================    
