int* tem=12;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9800);
}
int *test(){
  int t=5;//[5]={5,4,3,2,8};
  
  return t;
  }
void loop() {
  // put your main code here, to run repeatedly:

tem=test();
//int t=5;
//tem=&t;
int tmp=*tem;
Serial.println(tmp);
}
