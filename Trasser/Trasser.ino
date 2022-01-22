#define inputA0 A0
#define outputD4 D4
int trasser = 0;
void setup() {
  // put your setup code here, to run once:
    pinMode(outputD4, OUTPUT);
   // Serial.begin(500000);
    digitalWrite(outputD4,HIGH);    
}

void loop() {
  // put your main code here, to run repeatedly:
  trasser=analogRead(inputA0);
  if(trasser<1022){ 
    digitalWrite(outputD4,LOW);
    delay(50);
    digitalWrite(outputD4,HIGH);
 //   Serial.println(trasser); 
  }
}
