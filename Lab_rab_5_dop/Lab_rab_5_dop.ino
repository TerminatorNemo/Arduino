
int b=0;
int c;
int z;
int x;
int a = 0;
int xz=0;

void setup() {

 Serial.begin(115200);

//Serial.print("Vvedite deistvie");
//delay(30);
Serial.println("1 це +");
delay(30);
Serial.println("2 це -");
delay(30);
Serial.println("3 це *");
delay(30);
Serial.println("4 це /");
delay(30);
}
void loop() {

//---------------------------------------------------
   if(a==0){ 
 if(Serial.available()) {  
      b = Serial.parseInt();  
      Serial.print("b  ");
      Serial.println(b);
      a++;
      if(b>4||b<1){a--;
  Serial.println("Неверный ввод");
}
     }
   }
//--------------------------------------------------

//--------------------------------------------------
   while(a==1){ 

 while(Serial.available()>0) {  
      z = Serial.parseInt();  
      a++;
     }
   }
//--------------------------------------------------
   while(a==2){ 

 while(Serial.available()>0) {  
      z = Serial.parseInt();  
       Serial.print("z  ");
      Serial.println(z);
      a++;
     // delay(90);
      break;
     }
     if(z!=0)break;
   }
//--------------------------------------------------
   while(a==3){ 

 while(Serial.available()>0) {  
      c = Serial.parseInt();  
    //   Serial.print("c  ");
   //   Serial.println(c);
      a++;
     // delay(90);
      break;
     }
     if(c!=0)break;
   }





   if(a==4){ 
 if(Serial.available()) {  
      c = Serial.parseInt();
       Serial.print("c  ");   
      Serial.println(c);
      if(b==1){x=c+z;
                 Serial.print("Ответ ");
      Serial.println(x);
      }
      else if(b==2){x=z-c;
                 Serial.print("Ответ ");
      Serial.println(x);
      }
      else if(b==3){x=c*z;
                 Serial.print("Ответ ");
      Serial.println(x);
      }
      else if(b==4){x=z/c;
      xz=z%c;
      xz=xz*100;
      xz=xz/c;
      Serial.print("Ответ ");
      Serial.print(x);
         Serial.print(",");
            Serial.println(xz);
      
      }

      a++;
     }
   }
//--------------------------------------------------
     
}








