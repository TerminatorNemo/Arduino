/*
 * Время на часах
 * Время рассвета
 * Время заката
 * Скорость рассвета (В минутах)
 * Скорость заката (В минутах)
 */

#include <OLED_I2C.h>
#include <iarduino_RTC.h>                                   // Подключаем библиотеку iarduino_RTC для работы с модулями реального времени.
iarduino_RTC watch(RTC_DS1302, 8, 6, 7);                // Объявляем объект watch для работы с RTC модулем на базе чипа DS1302, указывая выводы Arduino подключённые к выводам модуля RST, CLK, DAT.
OLED  myOLED(SDA, SCL, 8);

#define one 2
#define two 3
#define butt 4
int N1 = 0;
int N2 = 0;
int Num=0;
extern uint8_t SmallFontRus[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];
extern uint8_t MediumFontRus[];

volatile int encCounter;
volatile boolean state0, lastState, turnFlag;
void setupp();
void setup()
{
  myOLED.begin();
  
  watch.begin(); 
  pinMode(one, INPUT);
  pinMode(two, INPUT);
  pinMode(butt, INPUT);
  attachInterrupt(0, int0, CHANGE);  
  setupp();
}
void setupp(){
  myOLED.setFont(MediumFontRus);
  myOLED.print("start", CENTER, 10);
  myOLED.update();  
  delay(1000);
  
  }
void int0() {

  state0 = bitRead(PIND, one);
  if (state0 != lastState) {
    encCounter += (bitRead(PIND, two) != lastState) ? -1 : 1;
    lastState = state0;
  }
}


void loop()
{

    myOLED.setFont(SmallFontRus);
    myOLED.printNumI(encCounter, CENTER, 50);
    myOLED.printNumI(digitalRead(butt), RIGHT, 50);
    myOLED.update();
    switch (encCounter) {
      case 1:
        myOLED.clrScr();
        myOLED.setFont(MediumFontRus);
        myOLED.print(watch.gettime("H:i:s"), CENTER, 10);
        //выполняется, когда var равно 1
        break;
      case 2:
        myOLED.clrScr();
        myOLED.print("Brema rasveta", CENTER, 10);
        
        //выполняется когда  var равно 2
        break;
      case 3:
        myOLED.clrScr();
        myOLED.print("Brema zakata", CENTER, 10);
        //выполняется когда  var равно 3
        break;
      case 4:
        myOLED.clrScr();
        myOLED.print("Skorost rasveta", CENTER, 10);
        //выполняется когда  var равно 4
        break;
      case 5:
        myOLED.clrScr();
        myOLED.print("Skorost zakata", CENTER, 10);      
        //выполняется когда  var равно 5
        break;
      default:
        myOLED.clrScr();
        myOLED.print("Zashkal", CENTER, 10);
        // выполняется, если не выбрана ни одна альтернатива
        // default необязателен
    }


    
}
