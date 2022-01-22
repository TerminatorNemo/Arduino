
int x =2;
void setup() {
while(x<14){
  pinMode(x, OUTPUT); 
  x++;
 }
 x=3;
}

void loop() {

while(x<14){
   digitalWrite(x, LOW); 
   x++;
} 
 x=2;
 
delay(1000);
 while(x<14){
   digitalWrite(x, HIGH); 
   x++;
}
x=2;
delay(1000);
}

