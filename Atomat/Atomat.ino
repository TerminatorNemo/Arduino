#define klapan 0
#define spusk 2
#define zemla_spusk 1
#define diod 4
int flag=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(klapan,OUTPUT);
  pinMode(diod,OUTPUT);
  pinMode(spusk,INPUT);
  pinMode(zemla_spusk,OUTPUT);
  digitalWrite(zemla_spusk,LOW);
  digitalWrite(diod,HIGH);
  delay(5000);
  digitalWrite(diod,LOW); 
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(spusk)==0&&flag==0){
    digitalWrite(klapan,HIGH);
    digitalWrite(diod,HIGH);
    delay(700);
    digitalWrite(klapan,LOW);
    digitalWrite(diod,LOW);
    flag=1;
  }
  if(digitalRead(spusk)==1&&flag==1)flag=0;
  delay(300);
}
