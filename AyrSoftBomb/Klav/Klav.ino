#define stolb1 7
#define stolb2 7
#define stolb3 8
#define stolb4 6
#define rad1 10
#define rad2 11
#define rad3 A5
#define rad4 9
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(stolb1, OUTPUT); 
pinMode(stolb2, OUTPUT); 
pinMode(stolb3, OUTPUT); 
pinMode(stolb4, OUTPUT); 

pinMode(rad1, INPUT_PULLUP); 
pinMode(rad2, INPUT_PULLUP); 
pinMode(rad3, INPUT_PULLUP); 
pinMode(rad4, INPUT_PULLUP); 
}

void loop() {
/*
digitalWrite(stolb1,LOW);
  if(digitalRead(rad1)==LOW){Serial.println("pin9");}
   else if(digitalRead(rad2)==LOW){Serial.println("pin10");}
    else if(digitalRead(rad3)==LOW){Serial.println("pin11");}
     else if(digitalRead(rad4)==LOW){Serial.println("pin12");}
digitalWrite(stolb1,HIGH);
*/
digitalWrite(stolb2,LOW);
  if(digitalRead(rad1)==LOW)Serial.println("red");
   if(digitalRead(rad2)==LOW)Serial.println("9");
    if(digitalRead(rad3)==LOW)Serial.println("6");
     if(digitalRead(rad4)==LOW)Serial.println("3");
digitalWrite(stolb2,HIGH);

digitalWrite(stolb3,LOW);
  if(digitalRead(rad1)==LOW)Serial.println("0");
   if(digitalRead(rad2)==LOW)Serial.println("8");
    if(digitalRead(rad3)==LOW)Serial.println("5");
     if(digitalRead(rad4)==LOW)Serial.println("2");
digitalWrite(stolb3,HIGH);

digitalWrite(stolb4,LOW);
  if(digitalRead(rad1)==LOW)Serial.println("green");
   if(digitalRead(rad2)==LOW)Serial.println("7");
    if(digitalRead(rad3)==LOW)Serial.println("4");
     if(digitalRead(rad4)==LOW)Serial.println("1");
digitalWrite(stolb4,HIGH);


}
