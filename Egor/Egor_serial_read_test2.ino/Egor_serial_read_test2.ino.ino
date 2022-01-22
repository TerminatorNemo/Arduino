 int ledPin = 3;
int ledPin1[] = {2,3,4,5,6,7,8,9};
byte incomingByteMas[10];
byte incomingByte;
int flag=0;
int number_port = 3;
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  for(int i= sizeof(ledPin1)/2;i>0;i--){
      pinMode(ledPin1[i-1], OUTPUT);
    }
  Serial.println("I'm reloaded");
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();

    if(incomingByte == 10){
        flag=0;
        Serial.print("I received: number_port ");
        Serial.print(number_port);
        Serial.print(" Status ");
        Serial.println(digitalRead(number_port));
      }

    if(incomingByte == '0'&&flag==0){
      Serial.println("I'm here 300");
    }    else if(incomingByte == '1'&&flag==0){
            for(int i= sizeof(ledPin1)/2;i>0;i--){
               Serial.print("Status: number_port ");
               Serial.print(ledPin1[i-1]);
               Serial.print(" Status ");
               Serial.println(digitalRead(ledPin1[i-1]));
          }
    } else if(incomingByte == '2'&&flag==0){
      number_port=2;
      flag=1;
    } else if(incomingByte == '3'&&flag==0){
      number_port=3;
      flag=1;
    }    else if (incomingByte == '4'&&flag==0){
      number_port=4;
      flag=1;
    }    else if (incomingByte == '5'&&flag==0){
      number_port=5;
      flag=1;
    }    else if (incomingByte == '6'&&flag==0){
      number_port=6;
      flag=1;
    }    else if (incomingByte == '7'&&flag==0){
      number_port=7;
      flag=1;
    }    else if (incomingByte == '8'&&flag==0){
      number_port=8;
      flag=1;
    }    else if (incomingByte == '9'&&flag==0){
      number_port=9;
      flag=1;
    } 
  
    
    if(incomingByte == '1'&&flag==1){
      digitalWrite(number_port, HIGH);
      flag=2;
    }
    else if (incomingByte == '0'&&flag==1){
      digitalWrite(number_port, LOW); 
      flag=2;
    }


  }
  delay(10);
}
