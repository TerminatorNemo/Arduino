// Видеообзоры и уроки работы с ARDUINO и ESP8266 на http://iomoio.ru

// Данный скетч предназначен для демонстрации возможности обращения к модулю из интернет и обновления IP-адреса ESP8266 (WiFi-сети в которой он находится) в сервисе http://hldns.ru
// Помимо регистрации на сайте http://hldns.ru для работы также требуется настройка переадресации с 10200-го порта маршрутизатора (роутера) на ESP8266

#include <ESP8266WiFi.h>                                      // Библиотека для создания Wi-Fi подключения (клиент или точка доступа)
#include <WiFiClient.h>                                       // Библиотека для связи с сетевыми хостами (локальными и интернет)
#include <ESP8266WebServer.h>                                 // Библиотека для поднятия веб-сервера
#import "index.h"

const char* ssid = "Kyivstar_F0E6";                                // Указываем имя WiFi-сети, к которой будет подключаться ESP8266
const char* password = "48544854";                            // Указываем пароль для подключения к WiFi-сети

const char* ip_update_host = "hldns.ru";                      // Указываем хост (адрес сайта) службы DynDNS
const char* ip_update_get = "/update/RPLDDINNSX7I1ZPBL6U9SETL9RFSIY";               // Указываем GET-запрос (набор параметров) адреса идентификации в службе DynDNS

ESP8266WebServer server(10200);                               // Создаём объект для работы с нашим веб-сервером, указав номер порта, по которому он будет доступен в WWW
WiFiClient client;                                            // Создаём объект для работы с удалёнными хостами

void setup(void){
  Serial.begin(9600);                                         // Инициализируем вывод данных на серийный порт со скоростью 9600 бод
  WiFi.begin(ssid, password);                                 // Соединяемся с WiFi-сетью 
  while (WiFi.status() != WL_CONNECTED)                       // Пока соединение не установено
    delay(500);                                               //  делаем задержку в пол секунды, пока соединение не установится
  Serial.println("WiFi connected");                           // Выводим сообщение о том, что устройство соединилось с WiFi-сетью 
  server.begin();                                             // Инициализируем работу веб-сервера
  server.on("/", root);                                       // Сообщаем о том, что при обращении к корневой директории нашего веб-сервера должна вызываться функция root
  Serial.println("HTTP server started");                      // Выводим на монитор серийного порта сообщение о том, что веб-сервер запущен
  Serial.print("Local IP: ");                                 // Выводим на монитор серийного порта сообщение о том, что сейчас будем выводить локальный IP
  Serial.println(WiFi.localIP());                             // Выводим локальный IP-адрес ESP8266
  Serial.print("MAC-address: ");                              // Выводим на монитор серийного порта сообщение о том, что сейчас будем выводить MAC-адрес ESP8266
  Serial.println(WiFi.macAddress());                          // Выводим MAC-адрес ESP8266
  ip_update();                                                // Вызываем функцию, обновляющую IP маршрутизатора (роутера) в службе динамических DNS
} 
void loop(void){
  server.handleClient();    // Ожидаем обращение к веб-серверу
  //delay(100);
  root();
}

void ip_update(){                                             // Функция, обновляющая IP маршрутизатора (роутера) в службе динамических DNS
  if (client.connect(ip_update_host,80)) {                    // Если возможно соединиться с хостом на 80-й порт:
    client.print("GET ");                                     //  Эта и следующие 7 строк отправляют системные заголовки на сервер службы динамических DNS
    client.print(ip_update_get);                              //  Формат заголовков строгий и в нём важны даже переводы строк
    client.println( " HTTP/1.1");                             //
    client.print("Host:");                                    //
    client.println(ip_update_host);                           //
    client.println( "Connection: close" );                    //
    client.println();                                         //
    client.println();                                         //
    delay(200);                                               //  Задержка в 0.2 сек., чтобы дать удалённому серверу возможность обработать и отправить ответ на наш запрос
    Serial.println("\nResponse of DDNS-Server:");             //  Шлём в монитор серийного порта сообщение о том, что далее будет выводиться ответ от сервера службы DynDNS
    while (client.available()) {                              //  Пока сервер на связи
      char a = client.read();                                 //    считываем его ответ по одному символу 
      Serial.print(a);                                        //    и выводим на монитор серийного порта
    }
  }
}
void root(){  // Функция,вызывающаяся при обращении клиента к корневой дирректории нашего веб-сервера
 //int times  =10 ;//millis();
 //Serial.println(times);  
// char temp = 'Hello" ; 
  server.send(200, "text/html","<h1>Web-server ESP8266 </h1>");
  String s = MAIN_page;
  server.send(200, "text/html", s);
  // HTTP.send(200, "text/plain", relay_status());            
 // server.send(200, "text/html","<h1>Web-server ESP8266</h1>"); // Сервер отправляет клиенту информацию о том, что
}                                                              // 200 - запрос успешно обработан
                                                               // text/html - ответ на запрос предоставляется в формате HTML
                                                               // третий параметр (<h1>Web-server ESP8266</h1>) содержит текст ответа в формате HTML
