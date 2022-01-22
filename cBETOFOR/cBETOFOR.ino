#define led 13//green
#define led1 10//ЖEЛТЫЙ
#define led2 8//синий
int z = 500;

#define but 12
void setup() {
pinMode(led, OUTPUT); 
pinMode(led1, OUTPUT); 
pinMode(led2, OUTPUT); 
pinMode(but, INPUT);
Serial.begin(250000);
}

void loop() {
        digitalWrite(led, HIGH); 
         Serial.println("1"); 
        int buttonState = digitalRead(but);
        delay(50);
        int buttonState1 = digitalRead(but);
         Serial.println(buttonState1); 
        if(buttonState==buttonState1){
          if(buttonState!=0){
            digitalWrite(led, LOW); 
            int a = 2;
               while(a>=0){
                 // Serial.println("2"); 

                   digitalWrite(led1, HIGH);
                   delay(z);
                                      digitalWrite(led1, LOW);
                   delay(z);
                   a--;
                }
              digitalWrite(led2, HIGH);
              //  Serial.println("3"); 
              delay(3000);
              a = 2;
              while(a>=0){
                //  Serial.println("2"); 

                   digitalWrite(led1, HIGH);
                   delay(z);
                                      digitalWrite(led1, LOW);
                   delay(z);
                   a--;
              }
              digitalWrite(led2, LOW); 
            }
        }
}
