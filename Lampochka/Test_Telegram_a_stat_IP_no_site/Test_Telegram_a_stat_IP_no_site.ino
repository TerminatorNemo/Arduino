#define TELEGRAM_DEBUG

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#include <UniversalTelegramBot.h>
                         
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
  //bot.sendMessage("629436257",String(IP[0])+"."+String(IP[1])+"."+String(IP[2])+"."+String(IP[3])+":10200");//бот шлет мне в лс ip
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


//==============================================================
//                  SETUP
//==============================================================

 

void setup(void){
//для роботы бота нужно

//что бы тг разрешил работу


  
  Serial.begin(9600);
 
    configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  secured_client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  //запуск вай фая
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  //WiFi.config(ip, gateway, subnet);//проблемная строчка  
  
  // Wait for connection
//подключение к вай фаю
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
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
  //secured_client.connect(TELEGRAM_HOST, TELEGRAM_SSL_PORT);
  secured_client.connect("www.google.com",443);
  Serial.println(secured_client.connected());
 //bot.sendMessage("629436257","Baza is restart");//письмо от бота мне в лс, в не зависимости от содержимого висне
  
 //bot.sendMessage("629436257",String(IP[0])+"."+String(IP[1])+"."+String(IP[2])+"."+String(IP[3])+":10200");//бот шлет мне в лс ip


}
//==============================================================
//                     LOOP
//==============================================================



void loop(void){
//bot.sendMessage("629436257","Loop");
  
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
