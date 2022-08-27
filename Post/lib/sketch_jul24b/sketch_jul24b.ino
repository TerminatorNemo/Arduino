#include "BMP208.h"
#include <Wire.h>


#define SDA_PIN D2
#define SCL_PIN D1
const int16_t I2C_MASTER = 0x42;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);  // start serial for output
    Wire.begin(SDA_PIN, SCL_PIN, I2C_MASTER);        // join i2c bus (address optional for master)
    delay(150);            //whait to load BMP208
    BMP_208_init();
#if serial_on
    Serial.println();
    Serial.println("Start");
#endif
}

void loop() {
  // put your main code here, to run repeatedly:
  
    BMP_208_Forced_mode();
    Serial.print(BMP_208_temp_read());
    Serial.println(" *C");
    Serial.print(BMP_208_pressure_read());    
    Serial.println(" Pask");
    Serial.print(above_the_sea(BMP_208_pressure_read()));
    Serial.println(" m");
    delay(300);
}
