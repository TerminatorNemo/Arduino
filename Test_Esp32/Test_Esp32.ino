#define led0 2
#define LOCK 32
#define led1 33
#define led2 26
#define buz 25
void setup() {
  // put your setup code here, to run once:
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led0, OUTPUT);
pinMode(LOCK, OUTPUT);
pinMode(buz, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led0,HIGH);
  digitalWrite(LOCK,HIGH);
  digitalWrite(buz,HIGH);
  delay(1000);
  
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led0,LOW);
  digitalWrite(LOCK,LOW);  
  digitalWrite(buz,LOW);  
  delay(1000);  
  
}
