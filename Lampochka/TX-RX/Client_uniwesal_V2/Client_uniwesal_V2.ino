#include <ESP8266WiFi.h>                           
//SSID and Password of your WiFi router
const char* ssid = "Kyivstar_F0E6";
const char* password = "48544854";
//==============================================================
//                  SET
//==============================================================
int kol=0;
int elem=0;
int set_=0; //какая кнопка отвечает от 0 и до скок хоч
int relay_set=0;
int connect_1 = 0;//куда подключен диод индикации подкючения к вай фаю
int connect_2 = 1;//куда подключен диод индикации подкючения к серверу
int relay = 2;//куда подключено реле
byte server___[] = { 192, 168, 1, 10 }; // IP базы
//==============================================================
//                  SET
//==============================================================
WiFiClient client;  
//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  pinMode(relay,OUTPUT); 
  pinMode(connect_1,OUTPUT);
  pinMode(connect_2,OUTPUT);  
  //подключение к вайфаю
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  //  Serial.print(".");
  }
  digitalWrite(connect_1, HIGH);
  //запрос на сервер
  int prov =client.connect(server___, 80);
    // делаем HTTP-запрос:
    client.print("GET ");
    client.print("/status");
    client.println(" HTTP/1.0");
    client.println();
}
//==============================================================
//                     LOOP
//==============================================================



void loop(void){

int test =client.read();  //считывание ответа сервера
//в зависимости от ответа сервера вкл или откл реле
if(kol==12+set_){
  relay_set=test-48;
  if(relay_set==1||relay_set==0)digitalWrite(relay, relay_set);
  kol=0;
    int prov =client.connect(server___, 80);
    digitalWrite(connect_2, prov);
    client.print("GET ");
    client.print("/status");
    client.println(" HTTP/1.0");
    client.println();
    //запрос на сервер
}

//поиск в отвнете сервера фразы Relai sratus
if(test==82&&elem==0){kol++;elem++;}
else if(test==101&&elem==1){kol++;elem++;}
else if(test==108&&elem==2){kol++;elem++;}
else if(test==97 &&elem==3||test==97 &&elem==8){kol++;elem++;}
else if(test==105&&elem==4){kol++;elem++;}
else if(test==32 &&elem==5){kol++;elem++;}
else if(test==115&&elem==6||test==115&&elem==11){kol++;elem++;}
else if(test==114&&elem==7){kol++;elem++;}
//else if(test==97 &&elem==8){kol++;elem++;}
else if(test==116&&elem==9){kol++;elem++;}
else if(test==117&&elem==10){kol++;elem++;}
//else if(test==115&&elem==11){kol++;elem++;}
else {kol=0;elem=0;}

//если потеряна связь с вай фаем
if(WiFi.status() != WL_CONNECTED) {
    digitalWrite(connect_1, LOW);
    WiFi.begin(ssid, password);     //Connect to your WiFi router
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
      digitalWrite(connect_1, HIGH);
  }
  
}
