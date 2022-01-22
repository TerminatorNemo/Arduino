

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>                                              // Библиотека для работы с файловой системой
#include <ESP8266FtpServer.h>  
#include <UniversalTelegramBot.h>

#include "index.h" //Our HTML webpage contents
                                                          
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
int relay = 2;//куда подключено реле
byte server___[] = { 192, 168, 1, 10 }; // IP базы
IPAddress ip(192,168,1,17);  //статический IP 
//==============================================================
//                  SET
//==============================================================
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);


WiFiClient client;  
ESP8266WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {//открытие HTML страници 
 String s = FPSTR(MAIN_page); //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
//==============================================================

//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  pinMode(relay,OUTPUT); 
  Serial.begin(9600);
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  WiFi.config(ip, gateway, subnet);//проблемная строчка  
  // Wait for connection
//подключение к вай фаю
 while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  SPIFFS.begin();


  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("Connected do ");

  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 // char temp[11]=WiFi.localIP()
  IPAddress  IP=WiFi.localIP();
   server.handleClient();          //Handle client requests

 
  //настройки для рабты сайта и дергания реле 
  server.on("/", handleRoot);      //Which routine to handle at root location
  server.begin();                  //Start server
  Serial.println("HTTP server started");
  server.on("/relay_switch", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", relay_switch());                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/relay_status", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", relay_status());                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/test", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", "1");                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  
  server.onNotFound([](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      if(!handleFileRead(server.uri()))
      server.send(404, "text/plain", "404");                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
 server.handleClient();          //Handle client requests



int prov =client.connect(server___, 80);
Serial.println(prov);
    Serial.println("connected");
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

  server.handleClient();          //Handle client requests


int test =client.read();
if(kol==12+set_){

  relay_set=test-48;
  if(relay_set==1||relay_set==0)digitalWrite(relay, relay_set);
  Serial.print("          ");
  Serial.print(relay_set);
  Serial.print("   relay_set  ");
  Serial.println(kol);


  kol=0;
    client.connect(server___, 80);
    client.print("GET ");
    client.print("/status");
    client.println(" HTTP/1.0");
    client.println();
}
  

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
/*
Serial.print(kol);
Serial.print("  ");
Serial.println(test);
*
}



String relay_switch() {                                                 // Функция переключения реле 
  byte state;
  if(digitalRead(relay))// возвращаем результат, преобразовав число в строку
    state = 0;
  else
    state = 1;  
    Serial.print(digitalRead(relay));
    Serial.print("   ");
      Serial.print(state);
          Serial.print("   ");
  digitalWrite(relay, state);
      Serial.println(digitalRead(relay));
  return String(state);
}



String relay_status() {                                                 // Функция переключения реле 
  byte state;
  state=digitalRead(relay);// возвращаем результат, преобразовав число в строку
  return String(state);
}



bool handleFileRead(String path){                                       // Функция работы с файловой системой
  if(path.endsWith("/")) path += "index.html";                          // Если устройство вызывается по корневому адресу, то должен вызываться файл index.html (добавляем его в конец адреса)
  String contentType = getContentType(path);                            // С помощью функции getContentType (описана ниже) определяем по типу файла (в адресе обращения) какой заголовок необходимо возвращать по его вызову
  if(SPIFFS.exists(path)){                                              // Если в файловой системе существует файл по адресу обращения
    File file = SPIFFS.open(path, "r");                                 //  Открываем файл для чтения
    size_t sent = server.streamFile(file, contentType);                   //  Выводим содержимое файла по HTTP, указывая заголовок типа содержимого contentType
    file.close();                                                       //  Закрываем файл
    return true;                                                        //  Завершаем выполнение функции, возвращая результатом ее исполнения true (истина)
  }
  return false;                                                         // Завершаем выполнение функции, возвращая результатом ее исполнения false (если не обработалось предыдущее условие)
}




String getContentType(String filename){                                 // Функция, возвращающая необходимый заголовок типа содержимого в зависимости от расширения файла
  if (filename.endsWith(".html")) return "text/html";                   // Если файл заканчивается на ".html", то возвращаем заголовок "text/html" и завершаем выполнение функции
  else if (filename.endsWith(".css")) return "text/css";                // Если файл заканчивается на ".css", то возвращаем заголовок "text/css" и завершаем выполнение функции
  else if (filename.endsWith(".js")) return "application/javascript";   // Если файл заканчивается на ".js", то возвращаем заголовок "application/javascript" и завершаем выполнение функции
  else if (filename.endsWith(".png")) return "image/png";               // Если файл заканчивается на ".png", то возвращаем заголовок "image/png" и завершаем выполнение функции
  else if (filename.endsWith(".jpg")) return "image/jpeg";              // Если файл заканчивается на ".jpg", то возвращаем заголовок "image/jpg" и завершаем выполнение функции
  else if (filename.endsWith(".gif")) return "image/gif";               // Если файл заканчивается на ".gif", то возвращаем заголовок "image/gif" и завершаем выполнение функции
  else if (filename.endsWith(".ico")) return "image/x-icon";            // Если файл заканчивается на ".ico", то возвращаем заголовок "image/x-icon" и завершаем выполнение функции
  return "text/plain";                                                  // Если ни один из типов файла не совпал, то считаем что содержимое файла текстовое, отдаем соответствующий заголовок и завершаем выполнение функции
}
