
#include <ESP8266WiFi.h>



//#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>      
#include <IRremoteESP8266.h> //  Подключаем библиотеку IRremoteESP8266
#include <IRsend.h>      
//#include <ESP8266TelegramBOT.h>

#include "index.h" //Our HTML webpage contents
                                                            



//SSID and Password of your WiFi router

const char* ssid = "Hostel-7";
const char* password = "12345678";

/*
const char* ssid = "Lampa_Staff";
const char* password = "Qy2_$X{5^}5=F6Fv";
*/
/*
const char* ssid = "Kyivstar_F0E6";
const char* password = "48544854";
 */
 /*
 const char* ssid = "DESKTOP-7AV6QP1";
  const char* password = "48544854";
 */
const int relay = 0;   // реле на 0м контаке, диод на 1м
const int IR = 1;   // реле на 0м контаке, диод на 1м
IRsend irsend(IR);
const char *ssid_ = "Test_IDE_18_01_2021";
ESP8266WebServer server(4590); //Server on port 80

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
                                                 // Определяем объект для работы с модулем по FTP (для отладки HTML)

 

void setup(void){

  
  Serial.begin(9600);
  pinMode(relay,OUTPUT);  
  irsend.begin();  // Инициализируем ИК передатчик
  WiFi.softAP(ssid_);
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
  digitalWrite(relay, HIGH);
  digitalWrite(IR, HIGH);
  // Wait for connection
  int time_delay=0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    time_delay++;
    if(time_delay>120)break;
  }
  // Serial.println(WiFi.localIP()); //вывод на монитор порта динамического (выданного WiFi маршрутизатором) IP адреса esp8266

  
//  SPIFFS.begin();
  server.on("/", handleRoot);      //Which routine to handle at root location

  server.begin();                  //Start server

  Serial.println("HTTP server started");
  server.on("/relay_switch", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", relay_switch());                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/relay_status", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", relay_status());                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });

//------------------------------------------------
  server.on("/FF3AC5", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF3AC5));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FFBA45", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFFBA45));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF827D", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF827D));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF02FD", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF02FD));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF1AE5", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF1AE5));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF9A65", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF9A65));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FFA25D", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFFA25D));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF22DD", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF22DD));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF2AD5", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF2AD5));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FFAA55", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFFAA55));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF926D", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF926D));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF12ED", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF12ED));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF0AF5", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF0AF5));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF8A75", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF8A75));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FFB24D", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFFB24D));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF32CD", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF32CD));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF38C7", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF38C7));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FFB847", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFFB847));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF7887", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF7887));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FFF807", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFFF807));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF18E7", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF18E7));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF9867", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF9867));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF58A7", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF58A7));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FFD827", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFFD827));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF28D7", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF28D7));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FFA857", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFFA857));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF6897", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF6897));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FFE817", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFFE817));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF08F7", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF08F7));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF8877", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF8877));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF48B7", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF48B7));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FFC837", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFFC837));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF30CF", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF30CF));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FFB04F", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFFB04F));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF708F", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF708F));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FFF00F", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFFF00F));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF10EF", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF10EF));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF906F", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF906F));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF50AF", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF50AF));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FFD02F", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFFD02F));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF20DF", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF20DF));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FFA05F", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFFA05F));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FF609F", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFF609F));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
  server.on("/FFE01F", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", RGB_go(0xFFE01F));                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });
//------------------------------------------------




  
  server.on("/ip", [](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      server.send(200, "text/plain", WIP());                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });





  
  server.onNotFound([](){                                        // При HTTP запросе вида http://192.168.4.1/relay_switch
      if(!handleFileRead(server.uri()))
      server.send(404, "text/plain", "404");                     // Отдаём клиенту код успешной обработки запроса, сообщаем, что формат ответа текстовый и возвращаем результат выполнения функции relay_switch 
  });




  // digitalWrite(relay, HIGH);


}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}



String relay_switch() {// Функция переключения реле 
  if(millis()<5000){
    return "1";
    } 
  byte state;
  if(digitalRead(relay))// возвращаем результат, преобразовав число в строку
    state = 0;
  else
    state = 1;  
 //   Serial.print(digitalRead(relay));
   // Serial.print("   ");
    //  Serial.print(state);
   //       Serial.print("   ");
  digitalWrite(relay, state);
   //   Serial.println(digitalRead(relay));
  return String(state);
}
String WIP(){
  IPAddress ip= WiFi.localIP();
  return String(ip[0])+"."+String(ip[1])+"."+String(ip[2])+"."+String(ip[3]);
  }
String RGB_go(uint64_t kode){
  irsend.sendNEC(kode); // Отправляем данные по протоколу NEC
  //relay_switch();
   digitalWrite(IR, HIGH);
 //delay(100);
  return String(kode);
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
