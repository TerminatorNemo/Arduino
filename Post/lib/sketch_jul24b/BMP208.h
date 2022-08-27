
#ifndef BMP208_h
	#define BMP208_h
	#include <Wire.h>
	#include <Arduino.h>

	/*
	  Pressure oversampling x1 (Ultra low power) 16 bit / 2.62 Pa, temperature oversampling x1 16 bit / 0.0050 °C

	*/

	#define serial_on 0
	
	void BMP_208_Forced_mode();

	double BMP_208_pressure_read();

	double BMP_208_temp_read();

	void BMP_208_init();

	int BMP_208_read(uint8_t reg);

	double bmp280_calculate_temp(int adc_T);

	double bmp280_calculate_pressure(int adc_P);

	float above_the_sea(float pressure);
 #endif
