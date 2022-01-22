
void setup() {
 Serial.begin(9600);
}
void loop() {
 int sensorValue = analogRead(A4);
 Serial.println(sensorValue);
 delay(1);
}

