/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "060a9b1708e44b5698d5e826cf1e5bc4";

// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "TP-LINK_9B58";
//char pass[] = "82637316";

//char ssid[] = "Terminator";
//char pass[] = "48544854";


char ssid[] = "Kyivstar_F0E6";
char pass[] = "48544854";
int buttonState;
int move_=0;
int door=0;
int door_=4;
int move__=5;


WidgetTerminal terminal(V12);

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
    pinMode(move_, INPUT);
    pinMode(door, INPUT);
}



BLYNK_WRITE(V4) {
  buttonState = param.asInt();
}


void loop()
{
  // terminal.flush();
  Blynk.run();
  door=digitalRead(door_);
  move_=digitalRead(move__);

 
  // int test=0;
  //Blynk.syncVirtual(V4);
  Serial.println(buttonState);
  WidgetLED led1(V2);
  WidgetLED led2(V1);
  WidgetLED led3(V3); 
  WidgetLED led4(V5);    
 // terminal.println(String(move_));

  if(door==0){
    led1.on();
    led4.on();
  }else{
    led4.off();
  }
  
  if(move_==1){
    led2.on();
    led3.on();
  }else{
    led3.off();
  }
  if(buttonState==1){
    led1.off();
    led2.off();
  }
  
  
  //Blynk.virtualWrite (V2, HIGH);


}
