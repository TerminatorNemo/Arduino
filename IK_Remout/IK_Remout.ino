//#include "IRremote.h"
#include <IRremote.h>
IRsend irsend;

decode_results results;

void setup() {
  Serial.begin(9600); // выставляем скорость COM порта
////////////  irrecv.enableIRIn(); // запускаем прием
 // IrSender.sendNECRaw(0xFF02FD,5);
}

void loop() {
  //  IrSender.sendNECRaw(0xFF02FD,6);
  //  irsend.sendNEC(0xFF02FD, 32);
    //irsend.sendNEC(0xFF02FD, 6);
   irsend.sendNEC(0xFF02FD, 32);
    delay(3000);
}
