#define one 2
#define two 3
int N1 = 0;
int N2 = 0;
void setup() {
  // put your setup code here, to run once:
pinMode(one, INPUT);
pinMode(two, INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  
if(digitalRead(one)!=N1){
  N1=digitalRead(one);
  N2=digitalRead(two);
  Serial.println((N1==N2)? "Left" : "Right");
  }
}
