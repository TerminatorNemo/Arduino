#include <EEPROM.h>

//Пин подключен к ST_CP входу 74HC595
int latchPin = 11;
//Пин подключен к SH_CP входу 74HC595
int clockPin = 12;
//Пин подключен к DS входу 74HC595
int dataPin = 10;

//Кнопка 1
const int buttonPin0 = 9;  
//Кнопка 2
const int buttonPin1 = 6;  
//Кнопка 3
const int buttonPin2 = 7;  
//Кнопка 4
const int buttonPin3 = 8;  

int me;//нужно для кружков

int q;//для вывода Кружки каждую минуту
int w;//для вывода Кружки каждую минуту
int q1;//для вывода АРС каждый час
int w1;//для вывода АРС каждый час


int eprom1=0;
int eprom2=1;
int eprom3=2;
int eprom4=3;

int epromread1;
int epromread2;
int epromread3;
int epromread4;

int cek  = 0;
int min0 = 05;
int chas = 18;

int m =1000;
int x =0;//_____________________________ОТЛАДКА
int y =0;//_____________________________ОТЛАДКА НАСТРОЙКА ВРЕМЕНИ
int timee = 500;



int z;
int t=1;
int a1 = 128;
int a2 = 128;
int a3 = 4;
int a4 = 4;


int b1 = 0;
int b2 = 0;
int b3 = 0;
int b4 = 0;
void setup() {


    Serial.begin(9600);
//начинаю устанавливать выходы
  pinMode(buttonPin0, INPUT_PULLUP);   

  pinMode(buttonPin1, INPUT_PULLUP);   

  pinMode(buttonPin2, INPUT_PULLUP);   

  pinMode(buttonPin3, INPUT_PULLUP);   

  pinMode(latchPin, OUTPUT);
  
  pinMode(clockPin, OUTPUT);
  
  pinMode(dataPin, OUTPUT);
//Заканивую устанавливать
 
a1 = 0;
a2 = 0;
a3 = 0;
a4 = 0;   

delay(200);

    


APC();        //Запускаю АРС
kryski();     //Запускаю кружки
    
    
    
    //Считывую из независимой памяти откуда ститывать время)))
       eprom1=EEPROM.read(50);
       eprom2=EEPROM.read(51);
       eprom3=EEPROM.read(52);
       eprom4=EEPROM.read(53);

       
//Вспоминаю время если не включена настройка времени   
if(y==0){     
min0=EEPROM.read(eprom1);
chas=EEPROM.read(eprom3);
}



//Зашита для востановления памяти
epromread1=EEPROM.read(eprom1);
epromread2=EEPROM.read(eprom2);
epromread3=EEPROM.read(eprom3);
epromread4=EEPROM.read(eprom4);
    
while(epromread1!=epromread2 || epromread3!=epromread4){
       eprom1=eprom1+4;
       eprom2=eprom2+4;
       eprom3=eprom3+4;
       eprom4=eprom4+4;
        
    EEPROM.update(50,eprom1);
    EEPROM.update(51,eprom2);
    EEPROM.update(52,eprom3);
    EEPROM.update(53,eprom4);
        
    EEPROM.update(eprom1,0);
    EEPROM.update(eprom2,0);
    EEPROM.update(eprom3,0);
    EEPROM.update(eprom4,0);

   
    }




  /*
 cek  = 0;
 min0 = 12;
 chas = 17;
*/
w=min0;
w1=chas;
q1=chas;

}
//---------------------------------------------------------------------------------------------------------------------------------------
void loop() {
if(x==1)  Seria1();//если запушена отладка вывожу в порт значения


//==========================Запуск АРС каждий час
 q1=chas;
 if(q1!=w1)APC();
 w1=chas;
//==========================Запуск АРС каждий час

//==========================Запуск Кружки каждую минуту
 q=min0%10;
 if(q==0 && q!=w)kryski();
 w=min0%10;
//==========================Запуск Кружки каждую минуту



//--------------------------Каждую секунду к секунде прибавляет 1 
if(t-z>=1){ cek=cek+1; 
 z=millis()/m;
 }
t=millis()/m; 
//--------------------------Каждую секунду к секунде прибавляет 1 


//--------------------------Каждую минуту к минуте прибавляет 1 
    if(cek==60){
      cek=0;
      min0=min0+1;
      }
//--------------------------Каждую минуту к минуте прибавляет 1 


//--------------------------Каждый час к часу прибавляет 1 
    if(min0==60){
      min0=0;
      chas=chas+1;
      }
//--------------------------Каждый час к часу прибавляет 1 


//--------------------------Обнуляет часы каждые сутки
    if(chas==24)chas=0;
//--------------------------Обнуляет часы каждые сутки




    
//==========================Записывает в энергонезависимую  память    
   EEPROM.update(eprom1,min0);
    EEPROM.update(eprom2,min0);
    EEPROM.update(eprom3,chas);
     EEPROM.update(eprom4,chas);
//==========================Записывает в энергонезависимую  память    


    
    
    
 /*     a1  a2   a3   a4   
  * 1   96  96   96  96                 
  * 2   55  55   179 179             
  * 3   118 118  242 242                 
  * 4   108 108  232 232                   
  * 5   30  30   218 218                    
  * 6   31  31   219 219                   
  * 7   112 112  112 112                      
  * 8   127 127  251 251                      
  * 9   126 126  250 250                    
  * 0   123 123  123 123                         
  * a   27  27   249 249
  * p   61  61   185 185
  * c   125 125  125 125 
  */



b1=chas/10;//Десятки часов
b2=chas%10;//Часы
b3=min0/10;//Десятки минут
b4=min0%10;//Минуты



  //  if(millis()%m==0)cek=cek+1;


//========================Мигает точками
  if(cek%2!=0)    {
NOtochka();
}
  if(cek%2==0)    {
   tochka();
  }
//========================Мигает точками
  
 
 /*     a1  a2   a3   a4   
  * 1   96  96   96  96                 
  * 2   55  55   179 179             
  * 3   118 118  242 242                 
  * 4   108 108  232 232                   
  * 5   30  30   218 218                    
  * 6   31  31   219 219                   
  * 7   112 112  112 112                      
  * 8   127 127  251 251                      
  * 9   126 126  187 187                    
  * 0   123 123  123 123                         
  * a   27  27   249 249
  * p   61  61   185 185
  * c   125 125  125 125 
  */

  
//__________________________________________________Вывожу на цыферблат цыфры
 digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, a4);
    shiftOut(dataPin, clockPin, MSBFIRST, a3);
    shiftOut(dataPin, clockPin, MSBFIRST, a2);
    shiftOut(dataPin, clockPin, MSBFIRST, a1);
    digitalWrite(latchPin, HIGH);
delay(10);
//__________________________________________________Вывожу на цыферблат цыфры


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=Кнопки
 while (buttonPin0 == LOW) {
  //Serial.print("chas"); 
  /*
        if (buttonPin1 == LOW) {   
       chas=chas+1;   
    }
        if (buttonPin3 == LOW) {  
           chas=chas-1;   
        }
    delay(100);
    */
    Serial.print("1");   
 }
 while (buttonPin1 == LOW) { 
      /*
        
        if (buttonPin1 == LOW) {  
           min0=min0+1 ; 
    }
        if (buttonPin3 == LOW) {     
           min0=min0-1;
    }    
    delay(100); 
 */
    Serial.print("2");  
 }
  while (buttonPin2 == LOW) {
//Serial.print("chas"); 
  /*
        if (buttonPin1 == LOW) {   
       chas=chas+1;   
    }
        if (buttonPin3 == LOW) {  
           chas=chas-1;   
        }
    delay(100);
    */
    Serial.print("3");   
 }
 while (buttonPin3 == LOW) { 
      /*
        
        if (buttonPin1 == LOW) {  
           min0=min0+1 ; 
    }
        if (buttonPin3 == LOW) {     
           min0=min0-1;
    }    
    delay(100); 
 */
    Serial.print("4");  
 }

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=Кнопки


delay(10);




}




//__________________ОТЛАДКА
 void Seria1(){
 Serial.print(chas); 
 Serial.print("  "); 
 Serial.print(min0); 
 Serial.print("  "); 
 Serial.println(cek); 
  }       
//__________________ОТДАЛКА 
        
        
//______________________________________________________________Гашу точку  
 void NOtochka(){ 
  
    if(b1==0)a1=123;
else if(b1==1)a1=96;
else if(b1==2)a1=55;

if(b2==0)a2=123;
else if(b2==1)a2=96;
else if(b2==2)a2=55;
else if(b2==3)a2=118;
else if(b2==4)a2=108;
else if(b2==5)a2=30;
else if(b2==6)a2=95;
else if(b2==7)a2=112;
else if(b2==8)a2=127;
else if(b2==9)a2=126;

if(b3==0)a3=123;
else if(b3==1)a3=96;
else if(b3==2)a3=179;
else if(b3==3)a3=242;
else if(b3==4)a3=232;
else if(b3==5)a3=218;
else if(b3==6)a3=219;

if(b4==0)a4=123;
else if(b4==1)a4=96;
else if(b4==2)a4=179;
else if(b4==3)a4=242;
else if(b4==4)a4=232;
else if(b4==5)a4=218;
else if(b4==6)a4=219;
else if(b4==7)a4=112;
else if(b4==8)a4=251;
else if(b4==9)a4=250;
    
}
//______________________________________________________________Гашу точку    
    
    
    
//______________________________________________________________Включаю точку  
void tochka(){ 
  
if(b1==0)a1=123;
else if(b1==1)a1=96;
else if(b1==2)a1=55;

if(b2==0)a2=251;
else if(b2==1)a2=224;
else if(b2==2)a2=183;
else if(b2==3)a2=246;
else if(b2==4)a2=236;
else if(b2==5)a2=222;
else if(b2==6)a2=223;
else if(b2==7)a2=240;
else if(b2==8)a2=255;
else if(b2==9)a2=254;

if(b3==0)a3=127;
else if(b3==1)a3=100;
else if(b3==2)a3=183;
else if(b3==3)a3=246;
else if(b3==4)a3=236;
else if(b3==5)a3=222;
else if(b3==6)a3=223;

if(b4==0)a4=123;
else if(b4==1)a4=96;
else if(b4==2)a4=179;
else if(b4==3)a4=242;
else if(b4==4)a4=232;
else if(b4==5)a4=218;
else if(b4==6)a4=219;
else if(b4==7)a4=112;
else if(b4==8)a4=251;
else if(b4==9)a4=250;
    

}
//______________________________________________________________Включаю точку    


//______________________________________________________________Кружки
void kryski(){  
//Вывожу кружки  
      digitalWrite(latchPin, LOW);              
      shiftOut(dataPin, clockPin, MSBFIRST, 16); 
      shiftOut(dataPin, clockPin, MSBFIRST, 8); 
      shiftOut(dataPin, clockPin, MSBFIRST, 1); 
      shiftOut(dataPin, clockPin, MSBFIRST, 2); 
     digitalWrite(latchPin, HIGH);
//Вывожу кружки  

//Вывожу кружки цыклом     
while(me!=17){   me=me+1;
        if(me==1 || me==7)z=64;
        if(me==2 || me==8)z=32;
        if(me==3 || me==9)z=16;
        if(me==4 || me==10)z=8;
        if(me==5 || me==11)z=1;
        if(me==6 || me==12)z=2;
        if(me==13|| me==14|| me==15 )z=2;
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, z); 
      digitalWrite(latchPin, HIGH);
      delay(100);  
  }
me=0;  
//Вывожу кружки цыклом   
}
//______________________________________________________________Кружки




//______________________________________________________________АРС   
void APC(){  
    digitalWrite(latchPin, LOW);
         shiftOut(dataPin, clockPin, MSBFIRST, 0); 
         shiftOut(dataPin, clockPin, MSBFIRST, 0); 
         shiftOut(dataPin, clockPin, MSBFIRST, 0); 
         shiftOut(dataPin, clockPin, MSBFIRST, 27); 
    digitalWrite(latchPin, HIGH);
    delay(timee);



    digitalWrite(latchPin, LOW);
    
         shiftOut(dataPin, clockPin, MSBFIRST, 0); 
         shiftOut(dataPin, clockPin, MSBFIRST, 0); 
         shiftOut(dataPin, clockPin, MSBFIRST, 27); 
         shiftOut(dataPin, clockPin, MSBFIRST, 61); 
    digitalWrite(latchPin, HIGH);
    delay(timee);


    digitalWrite(latchPin, LOW);
    
         shiftOut(dataPin, clockPin, MSBFIRST, 0); 
         shiftOut(dataPin, clockPin, MSBFIRST, 27); 
         shiftOut(dataPin, clockPin, MSBFIRST, 61); 
         shiftOut(dataPin, clockPin, MSBFIRST, 125); 
    digitalWrite(latchPin, HIGH);
    delay(timee);


    digitalWrite(latchPin, LOW);
    
         shiftOut(dataPin, clockPin, MSBFIRST, 27); 
         shiftOut(dataPin, clockPin, MSBFIRST, 185); 
         shiftOut(dataPin, clockPin, MSBFIRST, 125); 
         shiftOut(dataPin, clockPin, MSBFIRST, 0); 
    digitalWrite(latchPin, HIGH);
    delay(timee);


    
    digitalWrite(latchPin, LOW);
    
         shiftOut(dataPin, clockPin, MSBFIRST, 185); 
         shiftOut(dataPin, clockPin, MSBFIRST, 249); 
         shiftOut(dataPin, clockPin, MSBFIRST, 0); 
         shiftOut(dataPin, clockPin, MSBFIRST, 0); 
    digitalWrite(latchPin, HIGH);
    delay(timee);



    digitalWrite(latchPin, LOW);
    
         shiftOut(dataPin, clockPin, MSBFIRST, 249); 
         shiftOut(dataPin, clockPin, MSBFIRST, 0); 
         shiftOut(dataPin, clockPin, MSBFIRST, 0); 
         shiftOut(dataPin, clockPin, MSBFIRST, 0); 

    digitalWrite(latchPin, HIGH);
    delay(timee);

    

    digitalWrite(latchPin, LOW);
    
         shiftOut(dataPin, clockPin, MSBFIRST, 0); 
         shiftOut(dataPin, clockPin, MSBFIRST, 0); 
         shiftOut(dataPin, clockPin, MSBFIRST, 0); 
         shiftOut(dataPin, clockPin, MSBFIRST, 0); 
}  
//______________________________________________________________АРС     
