int pos = 830;//180
int incomingByte = 0;
int servo=9;

void setup() {
  Serial.begin(9600);
  pinMode(servo, OUTPUT);
}

void loop() {
  digitalWrite(servo, LOW);//=============
  //if (Serial.available() > 0) {
    /*
    incomingByte = Serial.read()-48;
  Serial.print("ввод - 48 ");Serial.println(incomingByte);
delay(400);
    
    if (incomingByte>=0 and incomingByte<=9) {
      pos=pos*10+incomingByte;
      Serial.println(pos, DEC);
    } else {
    */  
  Serial.print("pos= ");Serial.println(pos);
      Serial.print("move: ");Serial.println(pos, DEC);Serial.print(" - ");Serial.println(pos, DEC);
      for (int i=1;i<=180;i++){        
        digitalWrite(servo, HIGH);
        delayMicroseconds(pos);
        digitalWrite(servo, LOW);
        delayMicroseconds(20000-pos);
        delay(1);
      }
      pos=170;//0
//    }
 // }
}
