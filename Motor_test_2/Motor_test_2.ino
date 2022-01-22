#include <Servo.h> 


Servo motor;

void setup() {
motor.attach(2);
motor.writeMicroseconds(2300);
delay(3000);
motor.writeMicroseconds(800);
delay(6000);
}

void loop() {
motor.writeMicroseconds(900);
 
}
