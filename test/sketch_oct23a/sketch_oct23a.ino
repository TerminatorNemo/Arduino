#define TXD 0 // GPIO1/TXD01

void setup() {
  pinMode(TXD, OUTPUT);
}

void loop() {
  digitalWrite(TXD, HIGH);
  delay(1000);
  digitalWrite(TXD, LOW);
  delay(1000);
}
