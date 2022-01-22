int pos = 850;//180
int incomingByte = 0;
int servo=9;

void setup() {
  Serial.begin(9600);
  pinMode(servo, OUTPUT);
}

void loop() {
  digitalWrite(servo, LOW);//=============
     for (int i=1;i<=180;i++){        
        digitalWrite(servo, HIGH);
        delayMicroseconds(pos);
        digitalWrite(servo, LOW);
        delayMicroseconds(20000-pos);
        delay(1);
      }
      pos=170;//0

      for (int i=1;i<=180;i++){        
        digitalWrite(servo, HIGH);
        delayMicroseconds(pos);
        digitalWrite(servo, LOW);
        delayMicroseconds(20000-pos);
        delay(1);
      }

pos = 830;//180
}
