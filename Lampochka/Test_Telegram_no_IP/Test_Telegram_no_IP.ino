

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <FS.h>                                                         // Библиотека для работы с файловой системой
#include <ESP8266FtpServer.h>  
#include <UniversalTelegramBot.h>
#include <ESP8266mDNS.h> 
#include "index.h" //Our HTML webpage contents
                                                          
//SSID and Password of your WiFi router
const char* ssid = "Kyivstar_F0E6";
const char* password = "48544854";
IPAddress ip(192,168,1,17);  //статический IP 
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
//bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_
#define BOT_TOKEN "1194479028:AAE0TiS0Y9YpspHvSfJY4HCfS-kUii1joHU"
WiFiClientSecure secured_client;
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
UniversalTelegramBot bot (BOT_TOKEN, secured_client);
unsigned long bot_lasttime;          // last time messages' scan has been done
const unsigned long BOT_MTBS = 1000; // mean time between scan messages
void handleNewMessages(int numNewMessages)
{
  Serial.println("Here in bot");
    IPAddress  IP=WiFi.localIP();
  bot.sendMessage("629436257",String(IP[0])+"."+String(IP[1])+"."+String(IP[2])+"."+String(IP[3])+":10200");//бот шлет мне в лс ip
  for (int i = 0; i < numNewMessages; i++)
  {
    if (bot.messages[i].type == "channel_post")
    {
      bot.sendMessage(bot.messages[i].chat_id, bot.messages[i].chat_title + " " + bot.messages[i].text, "");
    }
    else
    {
      bot.sendMessage(bot.messages[i].chat_id, bot.messages[i].chat_id, "");
    }
  }
}
//bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_bot_

const int relay = 2;   
const char *ssid_ = "MyESP";
ESP8266WebServer server(10200); //Server on port 80
MDNSResponder mdns; 
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {//открытие HTML страници 
 String s = FPSTR(MAIN_page); //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
//==============================================================
//                  SETUP
//==============================================================

 

void setup(void){
//для роботы бота нужно
  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  secured_client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
//что бы тг разрешил работу


  
  Serial.begin(9600);
    pinMode(relay,OUTPUT);  

  //запуск вай фая
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
  
   WiFi.config(ip, gateway, subnet);//проблемная строчка  
  // Wait for connection
//подключение к вай фаю
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
     //назначаем символьное имя mDNS нашему серверу опираясь на его динамически полученный IP
 if (MDNS.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
//запуск точки доступа
  WiFi.softAP(ssid_);
  SPIFFS.begin();


  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 // char temp[11]=WiFi.localIP()
  IPAddress  IP=WiFi.localIP();
   server.handleClient();          //Handle client requests

 // bot.sendMessage("629436257","Baza is restart");//письмо от бота мне в лс, в не зависимости от содержимого виснет


  //настройки для рабты сайта и дергания реле 
  server.on("/", handleRoot);      //Which routine to handle at root location
  Serial.println("sms sended");
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

  bot.sendMessage("629436257",String(IP[0])+"."+String(IP[1])+"."+String(IP[2])+"."+String(IP[3])+":10200");//бот шлет мне в лс ip


}
//==============================================================
//                     LOOP
//==============================================================



void loop(void){
  server.handleClient();          //Handle client requests
//test_bot__test_bot__test_bot__test_bot__test_bot__test_bot__test_bot__test_bot__test_bot__test_bot__
//получение смс от меня и отправка мне чат id
  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
//test_bot__test_bot__test_bot__test_bot__test_bot__test_bot__test_bot__test_bot__test_bot__test_bot__


  
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
