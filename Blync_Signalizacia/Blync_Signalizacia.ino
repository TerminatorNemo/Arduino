
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "060a9b1708e44b5698d5e826cf1e5bc4";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Kyivstar_F0E6";
char pass[] = "48544854";

void setup()
{
  // Debug console
 // Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
