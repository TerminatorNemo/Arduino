void setup() {
 Serial.begin(9600);
 pinMode(13, OUTPUT); 
  pinMode(10, OUTPUT); 
   pinMode(11, OUTPUT); 
    pinMode(12, OUTPUT); 
    
}
void loop() {

   
 float a = analogRead(A4);
 int sensorValue= map(a, 0, 1023,0,4);

  if(sensorValue>=1&&sensorValue<2){        digitalWrite(13, HIGH);
  
  }else  if(sensorValue>=2&&sensorValue<3){ digitalWrite(10, HIGH);
                                            digitalWrite(13, HIGH);
                                            
 }else if(sensorValue>=3&&sensorValue<4){  digitalWrite(11, HIGH);
                                           digitalWrite(10, HIGH);
                                           digitalWrite(13, HIGH);
                                           
  }else  if(sensorValue>=4){                digitalWrite(11, HIGH);
                                            digitalWrite(12, HIGH);
                                            digitalWrite(10, HIGH);
                                            digitalWrite(13, HIGH);
 }else {
  digitalWrite(13, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  }


 Serial.println(sensorValue);
 
 delay(1);
}

