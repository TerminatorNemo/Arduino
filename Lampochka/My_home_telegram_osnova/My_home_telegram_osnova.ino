

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
//#include <FS.h>                                                         // Библиотека для работы с файловой системой
#include <ESP8266FtpServer.h>  
#include <UniversalTelegramBot.h>

#include "index.h" //Our HTML webpage contents
                                                          
//SSID and Password of your WiFi router
const char* ssid = "MyESP";
const char* password = "";
//bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_
#define BOT_TOKEN "1194479028:AAE0TiS0Y9YpspHvSfJY4HCfS-kUii1joHU"
WiFiClientSecure secured_client;
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
UniversalTelegramBot bot (BOT_TOKEN, secured_client);
unsigned long bot_lasttime;          // last time messages' scan has been done
const unsigned long BOT_MTBS = 1000; // mean time between scan messages


//bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_

#define relay  2   
#define button 4
int flag = 0;
ESP8266WebServer server(10200); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
 void handleRoot() {
 String s = FPSTR(MAIN_page); //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
//==============================================================
//                  SETUP
//==============================================================

 

void setup(void){
   Serial.begin(9600);
  //bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_
  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  secured_client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  //bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_
  pinMode(relay,OUTPUT);  
  pinMode(button,INPUT);  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    
  }
  SPIFFS.begin();


    //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 // char temp[11]=WiFi.localIP()
  bot.sendMessage("629436257","Baza is restart");


  
  server.on("/", handleRoot);      //Which routine to handle at root location
  server.begin();                  //Start server
  
  server.on("/relay_switch", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", relay_switch());                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/relay_status", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", relay_status());                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.onNotFound([](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      if(!handleFileRead(server.uri()))
      server.send(404, "text/plain", "404");                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  IPAddress  IP=WiFi.localIP();
  bot.sendMessage("629436257",String(IP[0])+"."+String(IP[1])+"."+String(IP[2])+"."+String(IP[3])+":10200");
  

}
//==============================================================
//                     LOOP
//==============================================================



void loop(void){
  server.handleClient();          //Handle client requests
  if(digitalRead(button)==1&&flag==0)relay_switch();flag=1;
  if(digitalRead(button)==0)flag=0;
}



String relay_switch() {                                                 // Функция переключения реле 
  byte state;
  if(digitalRead(relay))// возвращаем результат, преобразовав число в строку
    state = 0;
  else
    state = 1;  
  digitalWrite(relay, state);
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
