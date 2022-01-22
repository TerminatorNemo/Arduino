/*
   Пример вывода на дисплей с регистром TM1637
   показывает все возможности библиотеки GyverTM1637
   AlexGyver Technologies http://alexgyver.ru/
*/

#define CLK 2
#define DIO 3

#define CLK_ 5
#define DIO_ 4

#define tonePin 13

#define stolb2 6 //белый
#define stolb3 7 //крастный
#define stolb4 8 //серый
#define rad1 9   //орнж
#define rad2 10  //фиолетовый
#define rad3 11  //желтый
#define rad4 12  //синий
//селеный+ коричневый -
#define time_to_boom 20

#define time_ckick 300
#include "GyverTM1637.h"
GyverTM1637 disp1(CLK, DIO);
GyverTM1637 disp2(CLK_, DIO_);

int master_pin[4]={4,8,5,4};

int but_in=0;
void setup() {
  Serial.begin(9600);
    Serial.println("start");
  disp1.clear();
  disp1.brightness(7);  // яркость, 0 - 7 (минимум - максимум)

  disp2.clear();
  disp2.brightness(7);  // яркость, 0 - 7 (минимум - максимум)

  Serial.begin(9600);
  pinMode(stolb2, OUTPUT); 
  pinMode(stolb3, OUTPUT); 
  pinMode(stolb4, OUTPUT); 

  pinMode(tonePin, OUTPUT); 
  digitalWrite(tonePin,LOW);

  pinMode(rad1, INPUT_PULLUP); 
  pinMode(rad2, INPUT_PULLUP); 
  pinMode(rad3, INPUT_PULLUP); 
  pinMode(rad4, INPUT_PULLUP); 
 
 


 
  Serial.println("mode");
  
}
//byte print_but(int but_int);
int klav();
int klav_tik(){//ожидание ввода
  int button;
      while(1){
        klav();
        if(but_in<10){
          button=but_in;
          return button;
        }
      }   
  }

void del(){//ожидание нажатия любой клавиши
  while(but_in==13){klav();}
  delay(time_ckick);
  while(but_in!=13){klav();}
}
void boom();
void obezv(int hr_, int min_, int sek);
void NeObezv();
void time_to_win();
void time_of_retention();
void loop() {
  disp2.displayByte (_n,_o,_d,_E);
  disp1.displayByte(0,0,0,0);
  klav();
  if(but_in==1){del();disp2.displayByte (_t,_i,_n,_E);Serial.println("boom");boom();}
  if(but_in==2){del();disp2.displayByte (_t,_i,_n,_n);Serial.println("time_to_win");time_to_win();}
  if(but_in==3){del();disp2.displayByte (_t,_i,_n,_E);Serial.println("time_of_retention");time_of_retention();} 
  disp1.point(0); 
}

void time_of_retention(){
  
  long game_time=inp_time();
  long time_of_go_game=0;
  int but_tik = klav_tik();
  long start_time=0;
  long time1=0;
  long time2=0;
  long time1_save=game_time;
  long time2_save=game_time;
  
  //int flag = 0;
  int flag1 = 0;
  int flag2=0;
  disp1.display(0,0,0,0);
  disp2.display(0,0,0,0);  
  time_of_go_game=millis();

    print_time1(disp2,game_time);
    print_time1(disp1,game_time);   
  game_time=game_time+time_of_go_game/1000;
  //del();
  while(1){

    but_tik = klav();
    if(but_tik==12&&flag2!=1){
      disp1.clear();
     // flag=1;
      start_time=millis()/1000;
      del(); 
      time2=0;
      flag2=1;
    }else if(but_tik==11&&flag2!=2){
      disp2.clear();
     // flag=2;
      start_time=millis()/1000;
      del();
      time1=0;
      flag2=2;
    }else if(but_tik==5){loose();break;}

    if(flag2==1){
       time1=millis()/1000-start_time;
       print_time1(disp1,time1_save-time1);
       if(flag1!=millis()/1000%2){if(time1_save-time1<60){tone(tonePin, 500, 150);}else{tone(tonePin, 1000, 150);} flag1=millis()/1000%2;}
       if(time1_save-time1<=0){win(); break;}
      
    }else if(flag2==2){
       time2=millis()/1000-start_time;
       print_time1(disp2,time2_save-time2);
       if(flag1!=millis()/1000%2){if(time2_save-time2<60){tone(tonePin, 500, 150);}else{tone(tonePin, 1500, 150);}flag1=millis()/1000%2;}   
       if(time2_save-time2<=0){win(); break;}
    }


    
    Serial.print(" time1 ");
    Serial.print(time1);
    Serial.print(" time2 ");
    Serial.print(time2);    
    Serial.print(" time1_save ");
    Serial.print(time1_save);
    Serial.print(" time2_save ");
    Serial.print(time2_save);    
    Serial.print(" millis()/1000-start_time ");
    Serial.print(millis()/1000-start_time);    
    Serial.print(" start_time ");
    Serial.println(start_time);
  }
  
 // time1_save+=time1;
 // time2_save+=time2;

  //print_time1(disp1,time1_save-time1);
  //print_time1(disp2,time2_save-time2);
   
  //  loose();
  }


void print_time1(GyverTM1637 disp1,long sek){
//вывод цыфр
        long min_=0;
        long hr_=0;

        Serial.print(sek);

        while(sek>59){min_++;sek-=60;}
        while(min_>59){hr_++;min_-=60;}
      

        disp1.point(millis()/1000%2);
   
        if(hr_==0){
          disp1.display( min_/10, min_%10,sek/10, sek%10);
         
        }else if(hr_>0){
          disp1.display(hr_/10, hr_%10, min_/10, min_%10);
        }
        delay(30);
//вывод цыфр}
}
long inp_time(){
    disp1.point(1);
    long hr_=0;
    long min_=0;
    disp1.point(1);
    disp1.displayByte(0, 0b0001000);
    disp1.display(1, hr_%10);
    disp1.display(2, min_/10);
    disp1.display(3, min_%10);

    hr_=klav_tik() * 10;
    disp1.display(hr_/10, hr_%10, min_/10, min_%10);
    del();

              
    disp1.display(0, hr_/10);
    disp1.displayByte(1, 0b0001000);
    hr_+=klav_tik() ;
    disp1.display(hr_/10, hr_%10, min_/10, min_%10);
    del();
      
             Serial.print("hr_");
          Serial.println(hr_);
    disp1.display(0, hr_/10);
    disp1.display(1, hr_%10);
    disp1.displayByte(2, 0b0001000);
    min_=klav_tik() * 10;
    disp1.display(hr_/10, hr_%10, min_/10, min_%10);
    del();

    disp1.display(0, hr_/10);
    disp1.display(1, hr_%10);
    disp1.display(2, min_/10);
    disp1.displayByte(3, 0b0001000);
    min_+=klav_tik() ;
    disp1.display(hr_/10, hr_%10, min_/10, min_%10);
    del();

    while(min_>60){
        min_-=60;
        hr_++;
      }
    while(hr_>99){
        hr_--;
       }
    disp1.display(hr_/10, hr_%10, min_/10, min_%10);
    delay(500);
    min_=min_*60;

    hr_=hr_*3600;
          Serial.print("hr_");
          Serial.println(hr_);
       Serial.print("min_+hr_");
          Serial.println(min_+hr_);
    return min_+hr_;
  }




void time_to_win(){
  long game_time=inp_time();
  long time_of_go_game=0;
  int but_tik = klav_tik();
  long start_time=0;
  long time1=0;
  long time2=0;
  long time1_save=0;
  long time2_save=0;
  
  int flag = 0;
  int flag1 = 0;
  int flag2=0;
  disp1.display(0,0,0,0);
  disp2.display(0,0,0,0);  
  time_of_go_game=millis();
  
  game_time=game_time+time_of_go_game/1000;
  del();
  while(game_time-millis()/1000>0){

    but_tik = klav();
    if(but_tik==12&&flag2!=1){
      disp1.clear();
      flag=1;
      start_time=millis()/1000;
      del(); 
      time2_save+=time2;
      time2=0;
      flag2=1;
    }
    if(but_tik==11&&flag2!=2){
      disp2.clear();
      flag=2;
      start_time=millis()/1000;
      del();
      time1_save+=time1;
      time1=0;
      flag2=2;
    }else if(but_tik==5)break;

    if(flag==1){
       time1=millis()/1000-start_time;
       print_time1(disp1,time1_save+time1);
      if(flag1!=millis()/1000%2){tone(tonePin, 1000, 150);flag1=millis()/1000%2;}
      
    }else if(flag==2){
       time2=millis()/1000-start_time;
       print_time1(disp2,time2_save+time2);
       if(flag1!=millis()/1000%2){tone(tonePin, 1500, 150);flag1=millis()/1000%2;}   
    }
    Serial.print(" time1 ");
    Serial.print(time1);
    Serial.print(" time2 ");
    Serial.print(time2);    
    Serial.print(" time1_save ");
    Serial.print(time1_save);
    Serial.print(" time2_save ");
    Serial.print(time2_save);    
    Serial.print(" millis()/1000-start_time ");
    Serial.print(millis()/1000-start_time);    
    Serial.print(" start_time ");
    Serial.println(start_time);
  }
  
  time1_save+=time1;
  time2_save+=time2;

  print_time1(disp1,time1_save);
  print_time1(disp2,time2_save);
     
    loose();
 // }
 }



  
void boom(){
  

      long time_of_game = inp_time();
      disp2.displayByte (_empty,_P,_i,_n);
      disp1.displayByte (0b0001000,0b0001000,0b0001000,0b0001000);
      int pin[4]={0,0,0,0};
      long temp=0;
      int nom_mas=0;
            

      
       disp1.point(0);
      while(1){
        klav();
        if(but_in<10){
          pin[temp]=but_in;
          disp1.display(temp, but_in);
          del();
          temp++;
          if(temp>3)break;
        }
      }
 
      
          del();
          disp1.clear();
//-----------------------игра пошла
      int flag =0; 

      double time_=millis();
      long time2=millis()-time_;
      disp2.displayByte (0b0001000,0b0001000,0b0001000,0b0001000);
      int pin2[4]={0,0,0,0};
      //temp=0;

       
      while(time2/1000<time_of_game){

       
        //пикание
        
        if(flag!=millis()/1000%2&&time_to_boom<time_of_game-time2/1000){tone(tonePin, 1000, 150);Serial.println("1");flag=millis()/1000%2;}
        else if(flag!=millis()/500%2&&time_to_boom>=time_of_game-time2/1000){tone(tonePin, 1000, 150);Serial.println("2");flag=millis()/500%2;}

        
        time2=millis()-time_;       
        //пикание


        
//ввод пароля
        klav();
        if(but_in<10){
          pin2[nom_mas]=but_in;
          
          disp2.display(nom_mas, but_in);
          del();
          nom_mas++;
        }
        if(nom_mas>3){
          nom_mas=0;
          for(int i=0;i<4;i++){
            if(pin2[i]!=pin[i]){disp2.displayByte (0b0001000,0b0001000,0b0001000,0b0001000);nom_mas=0;}
            if(pin2[i]==pin[i]){}
            else if(pin2[i]!=master_pin[i]){disp2.displayByte (0b0001000,0b0001000,0b0001000,0b0001000);nom_mas=0;break;}
            nom_mas=1;
          }
          if(nom_mas==1){        
            long sek=0;
            long min_=0;
            long hr_=0;
            sek=temp;
            while(sek>59){min_++;sek-=60;}
            while(min_>59){hr_++;min_-=60;}obezv(hr_, min_, sek);return 1; } 
            nom_mas=0;
         }
//ввод пароля

       

//вывод цыфр
        temp=time_of_game-time2/1000;//получаю минуты
        print_time1(disp1, temp);   
//вывод цыфр
        

        
  }
  tone(tonePin,900,1000);delay(1000);
  NeObezv();
}



void loose() {

    tone(tonePin, 73, 187.5);
    delay(208.333333333);
    tone(tonePin, 146, 375.0);
    delay(416.666666667);
    tone(tonePin, 146, 187.5);
    delay(208.333333333);
    if(klav()==12)return;
    tone(tonePin, 73, 187.5);
    delay(208.333333333);
    tone(tonePin, 146, 375.0);
    delay(416.666666667);
    tone(tonePin, 146, 187.5);
    delay(208.333333333);
    tone(tonePin, 82, 187.5);
    delay(208.333333333);
    if(klav()==12)return;
    tone(tonePin, 164, 375.0);
    delay(416.666666667);
    tone(tonePin, 164, 187.5);
    delay(208.333333333);
    tone(tonePin, 82, 187.5);
    delay(208.333333333);
    tone(tonePin, 164, 375.0);
    delay(416.666666667);
    tone(tonePin, 164, 187.5);
    delay(208.333333333);
    if(klav()==12)return;
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    tone(tonePin, 184, 375.0);
    delay(416.666666667);
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    if(klav()==12)return;
    tone(tonePin, 184, 375.0);
    delay(416.666666667);
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    tone(tonePin, 184, 375.0);
    delay(416.666666667);
    if(klav()==12)return;
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    tone(tonePin, 184, 375.0);
    delay(416.666666667);
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 73, 187.5);
    delay(208.333333333);
    if(klav()==12)return;
    tone(tonePin, 146, 375.0);
    delay(416.666666667);
    tone(tonePin, 146, 187.5);
    delay(208.333333333);
    tone(tonePin, 73, 187.5);
    delay(208.333333333);
    tone(tonePin, 146, 375.0);
    delay(416.666666667);
    if(klav()==12)return;
    tone(tonePin, 146, 187.5);
    delay(208.333333333);
    tone(tonePin, 82, 187.5);
    delay(208.333333333);
    tone(tonePin, 164, 375.0);
    delay(416.666666667);
    tone(tonePin, 164, 187.5);
    delay(208.333333333);
    if(klav()==12)return;
    tone(tonePin, 82, 187.5);
    delay(208.333333333);
    tone(tonePin, 164, 375.0);
    delay(416.666666667);
    tone(tonePin, 164, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    tone(tonePin, 184, 375.0);
    delay(416.666666667);
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    if(klav()==12)return;
    tone(tonePin, 184, 375.0);
    delay(416.666666667);
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    tone(tonePin, 184, 375.0);
    delay(416.666666667);
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    if(klav()==12)return;
    tone(tonePin, 184, 375.0);
    delay(416.666666667);
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 73, 187.5);
    delay(208.333333333);
    tone(tonePin, 146, 187.5);
    delay(208.333333333);
    if(klav()==12)return;
    tone(tonePin, 73, 187.5);
    delay(208.333333333);
    tone(tonePin, 146, 187.5);
    delay(208.333333333);
    tone(tonePin, 73, 187.5);
    delay(208.333333333);
    tone(tonePin, 146, 187.5);
    delay(208.333333333);
    tone(tonePin, 73, 187.5);
    delay(208.333333333);
    tone(tonePin, 146, 187.5);
    delay(208.333333333);
    if(klav()==12)return;
    tone(tonePin, 82, 187.5);
    delay(208.333333333);
    tone(tonePin, 164, 187.5);
    delay(208.333333333);
    tone(tonePin, 82, 187.5);
    delay(208.333333333);
    tone(tonePin, 164, 187.5);
    delay(208.333333333);
    tone(tonePin, 82, 187.5);
    delay(208.333333333);
    if(klav()==12)return;
    tone(tonePin, 164, 187.5);
    delay(208.333333333);
    tone(tonePin, 82, 187.5);
    delay(208.333333333);
    tone(tonePin, 164, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    if(klav()==12)return;
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    if(klav()==12)return;
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    if(klav()==12)return;
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 73, 187.5);
    delay(208.333333333);
    tone(tonePin, 146, 187.5);
    delay(208.333333333);
    if(klav()==12)return;
    tone(tonePin, 73, 187.5);
    delay(208.333333333);
    tone(tonePin, 146, 187.5);
    delay(208.333333333);
    tone(tonePin, 73, 187.5);
    delay(208.333333333);
    tone(tonePin, 146, 187.5);
    delay(208.333333333);
    tone(tonePin, 73, 187.5);
    delay(208.333333333);
    tone(tonePin, 146, 187.5);
    delay(208.333333333);
    tone(tonePin, 82, 187.5);
    delay(208.333333333);
    if(klav()==12)return;
    tone(tonePin, 164, 187.5);
    delay(208.333333333);
    tone(tonePin, 82, 187.5);
    delay(208.333333333);
    tone(tonePin, 164, 187.5);
    delay(208.333333333);
    tone(tonePin, 82, 187.5);
    delay(208.333333333);
    tone(tonePin, 164, 187.5);
    delay(208.333333333);
    tone(tonePin, 82, 187.5);
    delay(208.333333333);
    tone(tonePin, 164, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    if(klav()==12)return;
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    if(klav()==12)return;
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    tone(tonePin, 92, 187.5);
    delay(208.333333333);
    tone(tonePin, 184, 187.5);
    delay(208.333333333);
    if(klav()==12)return;
    tone(tonePin, 73, 187.5);
    delay(208.333333333);
    tone(tonePin, 146, 187.5);
    delay(208.333333333);
    tone(tonePin, 73, 187.5);
    delay(208.333333333);
    tone(tonePin, 146, 187.5);
    delay(208.333333333);
}
void win() {

   
    tone(tonePin, 92, 160.714125);
    delay(178.57125);
    tone(tonePin, 110, 160.714125);
    delay(178.57125);
    tone(tonePin, 155, 160.714125);
    delay(178.57125);
    tone(tonePin, 146, 482.142375);
    if(klav()==12)return;
    delay(535.71375);
    delay(357.1425);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 110, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 482.142375);
    delay(535.71375);
    if(klav()==12)return;
    delay(892.85625);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 92, 80.3570625);
    delay(89.285625);
    tone(tonePin, 92, 80.3570625);
    delay(89.285625);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 321.42825);
    delay(357.1425);
    if(klav()==12)return;
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 97, 80.3570625);
    delay(89.285625);
    tone(tonePin, 97, 80.3570625);
    delay(89.285625);
    tone(tonePin, 146, 160.714125);
    delay(178.57125);
    tone(tonePin, 146, 321.42825);
    delay(357.1425);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 92, 80.3570625);
    delay(89.285625);
    if(klav()==12)return;
    tone(tonePin, 92, 80.3570625);
    delay(89.285625);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 321.42825);
    delay(357.1425);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 97, 80.3570625);
    delay(89.285625);
    tone(tonePin, 97, 80.3570625);
    delay(89.285625);
    tone(tonePin, 146, 160.714125);
    delay(178.57125);
    tone(tonePin, 146, 321.42825);
    delay(357.1425);
  //////////////////////////////////
    if(klav()==12)return;
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 92, 80.3570625);
    delay(89.285625);
    tone(tonePin, 92, 80.3570625);
    delay(89.285625);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 321.42825);
    delay(357.1425);
    if(klav()==12)return;
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 97, 80.3570625);
    delay(89.285625);
    tone(tonePin, 97, 80.3570625);
    delay(89.285625);
    tone(tonePin, 146, 160.714125);
    delay(178.57125);
    tone(tonePin, 146, 321.42825);
    delay(357.1425);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 92, 80.3570625);
    delay(89.285625);
    if(klav()==12)return;
    tone(tonePin, 92, 80.3570625);
    delay(89.285625);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 321.42825);
    delay(357.1425);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 97, 80.3570625);
    delay(89.285625);
    tone(tonePin, 97, 80.3570625);
    delay(89.285625);
    tone(tonePin, 146, 160.714125);
    delay(178.57125);
    tone(tonePin, 146, 321.42825);
    delay(357.1425);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
  if(klav()==12)return;
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 92, 80.3570625);
    delay(89.285625);
    tone(tonePin, 92, 80.3570625);
    delay(89.285625);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 321.42825);
    delay(357.1425);
    if(klav()==12)return;
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 97, 80.3570625);
    delay(89.285625);
    tone(tonePin, 97, 80.3570625);
    delay(89.285625);
    tone(tonePin, 146, 160.714125);
    delay(178.57125);
    tone(tonePin, 146, 321.42825);
    delay(357.1425);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 92, 80.3570625);
    delay(89.285625);
    if(klav()==12)return;
    tone(tonePin, 92, 80.3570625);
    delay(89.285625);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 321.42825);
    delay(357.1425);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 97, 80.3570625);
    delay(89.285625);
    tone(tonePin, 97, 80.3570625);
    delay(89.285625);
    tone(tonePin, 146, 160.714125);
    delay(178.57125);
    tone(tonePin, 146, 321.42825);
    delay(357.1425);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
      if(klav()==12)return;
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 92, 80.3570625);
    delay(89.285625);
    tone(tonePin, 92, 80.3570625);
    delay(89.285625);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 321.42825);
    delay(357.1425);
    if(klav()==12)return;
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 97, 80.3570625);
    delay(89.285625);
    tone(tonePin, 97, 80.3570625);
    delay(89.285625);
    tone(tonePin, 146, 160.714125);
    delay(178.57125);
    tone(tonePin, 146, 321.42825);
    delay(357.1425);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 92, 80.3570625);
    delay(89.285625);
    if(klav()==12)return;
    tone(tonePin, 92, 80.3570625);
    delay(89.285625);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 321.42825);
    delay(357.1425);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 123, 160.714125);
    delay(178.57125);
    tone(tonePin, 97, 80.3570625);
    delay(89.285625);
    tone(tonePin, 97, 80.3570625);
    delay(89.285625);
    tone(tonePin, 146, 160.714125);
    delay(178.57125);
    tone(tonePin, 146, 321.42825);
    delay(357.1425);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
    tone(tonePin, 138, 160.714125);
    delay(178.57125);
}


void NeObezv(){
    disp2.displayByte(_empty,_b,_O,_O); 
    loose();
    while(1){
      if(millis()/500%2){
          disp1.display(0,0,0,0);
      }else{
        disp1.clear();
      }
      

      if(klav()==12)break;

    }
  
  }




void obezv(int hr_, int min_, int sek){
    win();
    while(1){
      if(millis()/800%2){
        if(hr_==0){
          disp1.display( min_/10, min_%10,sek/10, sek%10);
        }else if(hr_>0){
          disp1.display(hr_/10, hr_%10, min_/10, min_%10);
        }
      }else{
        disp1.clear();
      }
        if(klav()==12)break;;
        
    }
  }


int klav(){
  but_in=13;
  digitalWrite(stolb2,LOW);
    if(digitalRead(rad1)==LOW)but_in=11;//red
    if(digitalRead(rad2)==LOW)but_in=9;
    if(digitalRead(rad3)==LOW)but_in = 6;
    if(digitalRead(rad4)==LOW)but_in = 3;
  digitalWrite(stolb2,HIGH);

  digitalWrite(stolb3,LOW);
    if(digitalRead(rad1)==LOW)but_in = 0;
    if(digitalRead(rad2)==LOW)but_in = 8;
    if(digitalRead(rad3)==LOW)but_in = 5;
    if(digitalRead(rad4)==LOW)but_in = 2;
  digitalWrite(stolb3,HIGH);

  digitalWrite(stolb4,LOW);
    if(digitalRead(rad1)==LOW)but_in=12;//green
    if(digitalRead(rad2)==LOW)but_in = 7;
    if(digitalRead(rad3)==LOW)but_in = 4;
    if(digitalRead(rad4)==LOW)but_in = 1;
  digitalWrite(stolb4,HIGH);
  return but_in;
  }

byte print_but(int but_int){
  byte but_;
  int flag=0;
  
  if(but_int==0){but_=_0;flag=1;}
  else if(but_int==1){but_=_1;flag=1;}  
  else if(but_int==2){but_=_2;flag=1;}
  else if(but_int==3){but_=_3;flag=1;}
  else if(but_int==4){but_=_4;flag=1;}
  else if(but_int==5){but_=_5;flag=1;}
  else if(but_int==6){but_=_6;flag=1;}
  else if(but_int==7){but_=_7;flag=1;}
  else if(but_int==8){but_=_8;flag=1;}
  else if(but_int==9){but_=_9;flag=1;}
  else if(but_int==10){but_=_E;flag=1;}
  else if(but_int==11){but_=_G;flag=1;}
  else if(but_int==12){but_=_A;flag=1;}
  if(flag==1)return but_;
  }
  
