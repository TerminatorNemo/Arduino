
#include <SPI.h>
#include <WiFi.h>
 
char ssid[] = "Kyivstar_F0E6";       //  SSID-имя вашей сети (name) 
char pass[] = "48544854";   // пароль вашей сети
 
int status = WL_IDLE_STATUS;
IPAddress server(74,125,115,105);  // Google
 
// Инициализируем объект client
WiFiClient client;
 
void setup() {
  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);
 
  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) { 
    Serial.println("Couldn't get a wifi connection");
    // больше ничего не делаем:
    while(true);
  } 
  else {
    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
    // в случае успешного подключения - сообщаем об этом через последовательный порт:
    if (client.connect(server, 80)) {
      Serial.println("connected");
      // посылаем HTTP-запрос:
      client.println("GET /search?q=arduino HTTP/1.0");
      client.println();
    }
  }
}
 
void loop() {
 
}
