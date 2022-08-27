#include "BMP208.h"

  const int16_t I2C_BMP_208 = 0x77; //I2C address BMP208
  int32_t t_fine;

  unsigned short int dig_T1_my = 0;
  short int dig_T2_my = 0;
  short int dig_T3_my = 0;

  unsigned short int dig_P1 = 0;
  short int dig_P2 = 0;
  short int dig_P3 = 0;
  short int dig_P4 = 0;
  short int dig_P5 = 0;
  short int dig_P6 = 0;
  short int dig_P7 = 0;
  short int dig_P8 = 0;
  short int dig_P9 = 0;

  signed char tmp_to_send = 0;
  signed char tmp_to_send2 = 0;

  signed char osrs_t = 1 << 5;      //Temperature oversampling = x1
  signed char osrs_p = 1 << 2;      //Pressure oversampling ×1
  signed char mode_ = 0;           //Mode - sleap 

  signed char t_sb = 0 << 5;        //Controls inactive duration tstandby in normal mode
  signed char filter = 0x02 << 2;   //Filter x4 
  signed char spi3w_en = 0;        //SPI off 



void BMP_208_Forced_mode() {

    tmp_to_send = osrs_t | osrs_p | 1;
    Wire.beginTransmission(I2C_BMP_208);
    Wire.write(0xF4);
    Wire.write(tmp_to_send);
    Wire.endTransmission(true);

    while (BMP_208_read(0xF3) >> 3) {}      //wheit to end measurement
}

double BMP_208_pressure_read() {
    int pressure_xlsb = 0;
    int pressure_lsb = 0;
    int pressure_msb = 0;

    pressure_xlsb = BMP_208_read(0xF9) >> 4;
    pressure_lsb = BMP_208_read(0xF8);
    pressure_msb = BMP_208_read(0xF7);

    int pressure = (pressure_msb << 12) | (pressure_lsb << 4) | (pressure_xlsb);

    return bmp280_calculate_pressure(pressure);
}

double BMP_208_temp_read() {

    int temp_xlsb = 0;
    int temp_lsb = 0;
    int temp_msb = 0;

    temp_xlsb = BMP_208_read(0xFC) >> 4;
    temp_lsb = BMP_208_read(0xFB);
    temp_msb = BMP_208_read(0xFA);

    int temp = (temp_msb << 12) | (temp_lsb << 4) | (temp_xlsb);

    return bmp280_calculate_temp(temp);
}

void BMP_208_init() {

    tmp_to_send = osrs_t | osrs_p | mode_;
    tmp_to_send2 = t_sb | filter | spi3w_en;


    Wire.beginTransmission(I2C_BMP_208);
    Wire.write(0xF4);
    Wire.write(tmp_to_send);

    Wire.write(0xF5);
    Wire.write(tmp_to_send2);
    Wire.endTransmission(true);

    if (BMP_208_read(0xF4) != tmp_to_send || BMP_208_read(0xF5) != tmp_to_send2) {
#if serial_on
        Serial.println("Set error!");

        Serial.print("id ");
        Serial.println(BMP_208_read(0xD0));

        Serial.print("tmp_to_send ");
        Serial.println(tmp_to_send);

        Serial.print("BMP_208_read(0xF4) ");
        Serial.println(BMP_208_read(0xF4));

        Serial.print("tmp_to_send2 ");
        Serial.println(tmp_to_send2);

        Serial.print("BMP_208_read(0xF5) ");
        Serial.println(BMP_208_read(0xF5));
#endif
        while (true) {}
    }

    dig_T1_my = BMP_208_read(0x89) << 8;
    dig_T1_my = dig_T1_my | BMP_208_read(0x88);

    dig_T2_my = BMP_208_read(0x8B) << 8;
    dig_T2_my = dig_T2_my | BMP_208_read(0x8A);

    dig_T3_my = BMP_208_read(0x8D) << 8;
    dig_T3_my = dig_T3_my | BMP_208_read(0x8C);


    dig_P1 = BMP_208_read(0x8F) << 8;
    dig_P1 = dig_P1 | BMP_208_read(0x8E);

    dig_P2 = BMP_208_read(0x91) << 8;
    dig_P2 = dig_P2 | BMP_208_read(0x90);

    dig_P3 = BMP_208_read(0x93) << 8;
    dig_P3 = dig_P3 | BMP_208_read(0x92);

    dig_P4 = BMP_208_read(0x95) << 8;
    dig_P4 = dig_P4 | BMP_208_read(0x94);

    dig_P5 = BMP_208_read(0x97) << 8;
    dig_P5 = dig_P5 | BMP_208_read(0x96);

    dig_P6 = BMP_208_read(0x99) << 8;
    dig_P6 = dig_P6 | BMP_208_read(0x98);

    dig_P7 = BMP_208_read(0x9B) << 8;
    dig_P7 = dig_P7 | BMP_208_read(0x9A);

    dig_P8 = BMP_208_read(0x9D) << 8;
    dig_P8 = dig_P8 | BMP_208_read(0x9C);

    dig_P9 = BMP_208_read(0x9F) << 8;
    dig_P9 = dig_P9 | BMP_208_read(0x9E);

}

int BMP_208_read(uint8_t reg) {
    Wire.beginTransmission(I2C_BMP_208);

    Wire.write(reg);
    Wire.endTransmission(true);

    Wire.requestFrom(I2C_BMP_208, 1, true);
    int out = 0;
    while (Wire.available()) {
        out = Wire.read();
    }
    return out;
}

double bmp280_calculate_temp(int adc_T)
{
    double var1, var2, T;
    var1 = (((double)adc_T) / 16384.0 - ((double)dig_T1_my) / 1024.0) * ((double)dig_T2_my);
    var2 = ((((double)adc_T) / 131072.0 - ((double)dig_T1_my) / 8192.0) * (((double)adc_T) / 131072.0 - ((double)dig_T1_my) / 8192.0)) * ((double)dig_T3_my);
    t_fine = (int32_t)(var1 + var2);
    T = (var1 + var2) / 5120.0;
    return T;
}

double bmp280_calculate_pressure(int adc_P)
{
    int64_t var1, var2, p;
    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)dig_P6;
    var2 = var2 + ((var1 * (int64_t)dig_P5) << 17);
    var2 = var2 + (((int64_t)dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)dig_P3) >> 8) + ((var1 * (int64_t)dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)dig_P1) >> 33;
    if (var1 == 0)
    {
        return 0; // avoid exception caused by division by zero
    }
    p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7) << 4);
    return (unsigned long)p / 256;

}

float above_the_sea(float pressure) {
    float seaLevelhPa = 1013.25;
    float altitude;

    pressure /= 100;

    altitude = 44330 * (1.0 - pow(pressure / seaLevelhPa, 0.1903));

    return altitude;
}
