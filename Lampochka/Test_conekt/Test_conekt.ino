/*
    HTTP over TLS (HTTPS) example sketch
    This example demonstrates how to use
    WiFiClientSecure class to access HTTPS API.
    We fetch and display the status of
    esp8266/Arduino project continuous integration
    build.
    Created by Ivan Grokhotkov, 2015.
    This example is in public domain.
*/

//C:\Users\arcen\Documents\ArduinoData\packages\esp8266\hardware\esp8266\2.7.3\libraries\ESP8266WiFi\src\BearSSLHelpers.cpp line 734

#include <ESP8266WiFi.h>
    #include <WiFiClientSecure.h>

    #ifndef STASSID
    #define STASSID "xxxxxxx"
    #define STAPSK  "xxxxxxxxx"
    #endif

    const char* ssid = "Kyivstar_F0E6";
    const char* password = "48544854";

    const char* host = "webhook.site";
    const int httpsPort = 443;



    const char fingerprint[] PROGMEM = "09:F6:00:C3:67:B0:80:14:34:E3:08:D7:4A:64:20:85:83:F4:80:A1";

    void setup() {
      Serial.begin(115200);
      Serial.println();
      Serial.print("connecting to ");
      Serial.println(ssid);
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());

      // Use WiFiClientSecure class to create TLS connection
      WiFiClientSecure client;
      Serial.print("connecting to ");
      Serial.println(host);

      Serial.printf("Using fingerprint '%s'\n", fingerprint);
      client.setFingerprint(fingerprint);

      if (!client.connect(host, httpsPort)) {
        Serial.println("connection failed");
        return;
      }
      delay(500);
       if (client.verify(fingerprint, host)) {
        Serial.println("certificate matches");
      } else {
        Serial.println("certificate doesn't match");
      }
    delay(500);
      String url = "/4cf42a06-5df4-4459-b8f3-5d29f1ed319d";
      Serial.print("requesting URL: ");
      Serial.println(url);


    String request = String("GET ") + url + " HTTP/1.0\r\n" +
                     "Host: " + host + "\r\n" +
                     "Accept: *" + "/" + "*\r\n" +
                      "User-Agent: BuilderFailureDetectorESP8266\r\n" +
                      "Connection: close\r\n\r\n";
      Serial.println(request);               
      client.print(request);

      Serial.println("request sent");
      int waitcount = 0;
      while (!client.available() && waitcount++ ) {
         delay(10);
    }
      while(client.available()){
        String line = client.readStringUntil('\r');
         Serial.print(line);
    }
      while (client.connected()) {
        String line = client.readStringUntil('\r');
        Serial.println("headers received"+line);
        if (line == "\r") {
          Serial.println("headers received"+line);
          break;
        }
      }

    }

    void loop() {
    }
