/*
 * Sensores.cpp
 *
 * Created: 16/09/2020 13:38:59
 *  Author: UsuarioDj
 */ 
#include "Sensores.h"
#include "DHT.h"

#define DHTPIN 0     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_BMP085.h"
Adafruit_BMP085 bmp180;

#include "DS3231.h"
RTClib RTC;


bool EstadoDHT, EstadoBMP, EstadoSD, EstadoReloj, estado;

double i2c_Regar1(int TiempoSeg) {
	//  char c = 0;
	//  Wire.requestFrom(8, 6);    // request 6 bytes from slave device #8
	//  while (Wire.available()) { // slave may send less than requested
	//    c = Wire.read(); // receive a byte as character
	//    Serial.print(c);         // print the character
	//    //stringOne = stringOne + c ;
	//  }
	Wire.beginTransmission(8);
	Wire.write(6);
	Wire.write(TiempoSeg);        // sends five bytes
	int32_t WireValor = Wire.read();
	Wire.endTransmission();
	return WireValor;
}
double i2c_Regar2(int TiempoSeg) {
	Wire.beginTransmission(8);
	Wire.write(7);
	Wire.write(TiempoSeg);        // sends five bytes
	int32_t WireValor = Wire.read();
	Wire.endTransmission();
	return WireValor;
}
double i2c_GetHumedadSuelo1() {
	//char c = 0;
	//  Wire.requestFrom(8, 4);    // request 6 bytes from slave device #8
	//  while (Wire.available()) { // slave may send less than requested
	//    c = Wire.read(); // receive a byte as character
	//    Serial.print(c);         // print the character
	//    //stringOne = stringOne + c ;
	//  }
	Wire.beginTransmission(8);
	Wire.write(4);
	Wire.write(512);        // sends five bytes
	int32_t WireValor = Wire.read();
	Wire.endTransmission();
	return WireValor;
}

void i2c_SetHumedadSuelo1MinMax() {
	char c = 0;
	Wire.beginTransmission(8); // transmit to device #8
	Wire.write(4);
	Wire.write(512);        // sends five bytes
	Wire.write(1023);              // sends one byte
	Wire.endTransmission();
}

double i2c_GetHumedadSuelo2() {
	//  char c = 0;
	//  Wire.requestFrom(8, 5);    // request 6 bytes from slave device #8
	//  while (Wire.available()) { // slave may send less than requested
	//    c = Wire.read(); // receive a byte as character
	//    Serial.print(c);         // print the character
	//    //stringOne = stringOne + c ;
	//  }
	Wire.beginTransmission(8);
	Wire.write(5);
	Wire.write(512);        // sends five bytes
	int32_t WireValor = Wire.read();
	Wire.endTransmission();
	return WireValor;
}

void i2c_SetHumedadSuelo2MinMax() {
	char c = 0;
	Wire.beginTransmission(8); // transmit to device #8
	Wire.write(5);
	Wire.write(512);        // sends five bytes
	Wire.write(1023);              // sends one byte
	Wire.endTransmission();

}

void i2c_SetHumedadAmbiente() {
	Wire.beginTransmission(8);
	Wire.write(2);
	int32_t Valor = (dht.readHumidity());
	Wire.write(Valor);
	Wire.endTransmission();
}

void i2c_SetTemperaturaAmbiente() {
	//return (bmp180.readTemperature() + dht.readTemperature()) / 2;
	Wire.beginTransmission(8);
	Wire.write(1);
	int32_t Valor = (bmp180.readTemperature());
	Wire.write(Valor);
	Wire.write(1023);
	Wire.endTransmission();
}

void i2c_SetPresionAmbiente() {
	Wire.beginTransmission(8);
	Wire.write(3);
	Wire.write(bmp180.readPressure());
	Wire.endTransmission();
}


void i2c_SetAnio() {
	DateTime now = RTC.now();
	Wire.beginTransmission(8);
	Wire.write(8);
	Wire.write(now.year());
	Wire.endTransmission();
}
void i2c_SetMes() {
	DateTime now = RTC.now();
	Wire.beginTransmission(8);
	Wire.write(9);
	Wire.write(now.month());
	Wire.endTransmission();
}
void i2c_SetHora() {
	DateTime now = RTC.now();
	Wire.beginTransmission(8);
	Wire.write(10);
	Wire.write(now.hour());
	Wire.endTransmission();
}

void i2c_SetDia() {
	DateTime now = RTC.now();
	Wire.beginTransmission(8);
	Wire.write(11);
	Wire.write(now.day());
	Wire.endTransmission();
}

void i2c_SetMinuto() {
	DateTime now = RTC.now();
	Wire.beginTransmission(8);
	Wire.write(12);
	Wire.write(now.minute());
	Wire.endTransmission();
}

void i2c_SetSegundo() {
	DateTime now = RTC.now();
	Wire.beginTransmission(8);
	Wire.write(13);
	Wire.write(now.second());
	Wire.endTransmission();
}


double GetHumedadAmbiente() {
	return dht.readHumidity();;
}
double GetTemperaturaAmbiente() {
	return (bmp180.readTemperature() + dht.readTemperature()) / 2;
}
double GetPresionAmbiente() {
	//  //wait for the measurement to finish. proceed as soon as hasValue() returned true.
	//  do
	//  {
	//    delay(100);
	//  } while (!bmp180.hasValue());
	//  return bmp180.getTemperature(); // degC
	//
	//  //
	//  //  temperature = (bmp180.getTemperature() + dht.readTemperature()) / 2;
	//  //  humidity = dht.readHumidity();
	//  //  pressure = bmp180.getPressure();
	//  //  altitude = 0;//bme.readAltitude(SEALEVELPRESSURE_HPA);
	return bmp180.readPressure();
}


double GetAnio() {
	DateTime now = RTC.now();
	return now.year();
}
double GetMes() {
	DateTime now = RTC.now();
	return now.month();
}
double GetHora() {
	DateTime now = RTC.now();
	return now.hour();
}

double GetDia() {
	DateTime now = RTC.now();
	return now.day();
}

double GetMinuto() {
	DateTime now = RTC.now();
	return now.minute();
}

double GetSegundo() {
	DateTime now = RTC.now();
	return now.second();
}
classFecha GetFecha(classFecha ArchivoFecha) {
	DateTime now = RTC.now();
	ArchivoFecha.Anio =  now.year() ;
	ArchivoFecha.Mes =  now.month() ;
	ArchivoFecha.Dia =  now.day() ;
	ArchivoFecha.Hora =  now.hour() ;
	ArchivoFecha.Minuto =  now.minute();
	ArchivoFecha.Segundo =  now.second() ;
	return ArchivoFecha;
}
classFecha SetFecha(classFecha ArchivoFecha) {
	DateTime now; // = RTC.now();



	//Clock.setClockMode(false);  // set to 24h
	//setClockMode(true); // set to 12h


	//  now.second(ArchivoFecha.Segundo);
	//  RTC.setSeconds(now.second);
	//  now.minute(ArchivoFecha.Minuto);
	//  RTC.setMinutes(now.minute);
	//  now.hour(ArchivoFecha.Hora);
	//  RTC.setHour(now.hour);
	//  now.day(ArchivoFecha.Dia);
	//  RTC.setDay(now.day);
	//  now.month(ArchivoFecha.Mes);
	//  RTC.setMonth(now.month);
	//  now.year(ArchivoFecha.Anio);
	//  RTC.setYear = now.year;

	DS3231 Clock;
	Clock.setSecond(ArchivoFecha.Segundo);
	Clock.setMinute(ArchivoFecha.Minuto);
	Clock.setHour(ArchivoFecha.Hora);
	Clock.setDoW(ArchivoFecha.Dia);
	//Clock.setDate(Date);
	Clock.setMonth(ArchivoFecha.Mes);
	Clock.setYear(ArchivoFecha.Anio);


	//  RTC_DS3231 RTC_adj;
	//  RTC_adj.adjust(DateTime(ArchivoFecha.Anio, ArchivoFecha.Mes, ArchivoFecha.Dia, ArchivoFecha.Hora, ArchivoFecha.Minuto, ArchivoFecha.Segundo));

	//RTC.setTime( ArchivoFecha.Hora, ArchivoFecha.Minuto, ArchivoFecha.Segundo);

	return ArchivoFecha;
}


void inicializar() {

	Serial.println(F("DHTxx test!"));
	dht.begin();

	//Wire.begin();
	//begin() initializes the interface, checks the sensor ID and reads the calibration parameters.
	if (!bmp180.begin())
	{
		Serial.println("begin() failed. check your BMP180 Interface and I2C Address.");
		while (1);
	}
	//reset sensor to default parameters.
	//bmp180.resetToDefaults();
	//enable ultra high resolution mode for pressure measurements
	//bmp180.setSamplingMode(BMP180MI::MODE_UHR);




}

void lectura() {

	// if (ReferenciaWire == 1) // DTH11
	//  {
	//    if (ValorWire == 1) {
	//      Humedad1(); // Tempetatura
	//    }
	//    else if (ValorWire == 2) {
	//      Riego1(); // Humedad
	//    }
	//  }
	//  if (ReferenciaWire == 2) // BMP180
	//  {
	//    //Valor = Wire.read();
	//    if (ValorWire == 1) {
	//      Humedad1(); // Barometro
	//    }
	//    else if (ValorWire == 2) {
	//      Riego1(); // Termometro
	//    }
	//  }
	//  if (ReferenciaWire == 3) Enviar Fecha
	//  if (ReferenciaWire == 4) lectura suelo 1
	//  if (ReferenciaWire == 5) lectura suelo 2
	//  if (ReferenciaWire == 6) riego1
	//  if (ReferenciaWire == 7) riego2


}


void EnviarFecha() {

	DateTime now = RTC.now();
	if (now.second() == 0)
	{
		Serial.println();
		Serial.print(now.year(), DEC);
		Serial.print('/');
		Serial.print(now.month(), DEC);
		Serial.print('/');
		Serial.print(now.day(), DEC);
		Serial.print(' ');
		Serial.print(now.hour(), DEC);
		Serial.print(':');
		Serial.print(now.minute(), DEC);
		Serial.print(':');
		Serial.print(now.second(), DEC);
		Serial.println();

		Serial.print(" since midnight 1/1/1970 = ");
		Serial.print(now.unixtime());
		Serial.print("s = ");
		Serial.print(now.unixtime() / 86400L);
		Serial.println("d");
		//DHTSensor();
		//aaa();
	}
	else {
		if (estado == true)
		{
			estado = false;
			Serial.print(".");
		}
		else
		{
			estado = true;
		}
	}


}

void Ambiente() {

	//start a temperature measurement


	Serial.print("Pressure: ");
	Serial.print(bmp180.readPressure());
	Serial.println(" Pa");

	delay(20);

	// Reading temperature or humidity takes about 250 milliseconds!
	// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
	float h = dht.readHumidity();
	// Read temperature as Celsius (the default)
	float t = dht.readTemperature();
	// Read temperature as Fahrenheit (isFahrenheit = true)
	float f = dht.readTemperature(true);

	// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(t) || isnan(f)) {
		Serial.println(F("Failed to read from DHT sensor!"));
		return;
	}

	// Compute heat index in Fahrenheit (the default)
	float hif = dht.computeHeatIndex(f, h);
	// Compute heat index in Celsius (isFahreheit = false)
	float hic = dht.computeHeatIndex(t, h, false);

	Serial.print(F("Humidity: "));
	Serial.print(h);
	Serial.print(F("%  Temperature: "));
	Serial.print(t);
	Serial.print(F("ºC "));
	Serial.print(f);
	Serial.print(F("ºF  Heat index: "));
	Serial.print(hic);
	Serial.print(F("ºC "));
	Serial.print(hif);
	Serial.println(F("ºF"));
}



void setup_Sensores() {
	Wire.begin();
	Serial.println(F("DHTxx test!"));
	dht.begin();
	float h = dht.readHumidity();
	float t = dht.readTemperature();
	float f = dht.readTemperature(true);
	Serial.print(F("Humidity: "));
	Serial.print(h);
	Serial.print(F("%  Temperature: "));
	Serial.print(t);
	Serial.print(F("ºC "));
	Serial.print(f);
	EstadoDHT = true;


	if (!bmp180.begin())
	{
		Serial.println("begin() failed. check your BMP180 Interface and I2C Address.");
	}
	else {
		EstadoBMP = true;
		//bmp180.resetToDefaults();
		//enable ultra high resolution mode for pressure measurements
		//bmp180.setSamplingMode(BMP180MI::MODE_UHR);
	}
	Serial.println("");
	Serial.print("bmp180 ");
	Serial.print( bmp180.readTemperature());
	Serial.print("ºC ");
	Serial.print( bmp180.readPressure());
	Serial.println("Pa ");
	//  bmp180.startPressure(3);
	//  double T, P;
	//  bmp180.getPressure(P, T);
	Serial.println(bmp180.readPressure() / 100);
	Serial.println("mb");

	DateTime now = RTC.now();
	Serial.println("");
	Serial.println("DS3231");
	Serial.print( now.year());
	Serial.print("year/ ");
	Serial.print( now.month());
	Serial.println("month/ ");
	Serial.print( now.day());
	Serial.println("day/ ");
	Serial.print( now.month());
	Serial.println("month/ ");
	Serial.print( now.hour());
	Serial.println("hour/ ");
	Serial.print( now.minute());
	Serial.println("minute/ ");
	Serial.print( now.second());
	Serial.println("second/ ");
}




void loop1() {

	// Wait a few seconds between measurements.
	delay(10);

	// Reading temperature or humidity takes about 250 milliseconds!
	// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
	float h = dht.readHumidity();
	// Read temperature as Celsius (the default)
	float t = dht.readTemperature();
	// Read temperature as Fahrenheit (isFahrenheit = true)
	float f = dht.readTemperature(true);

	// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(t) || isnan(f)) {
		Serial.println(F("Failed to read from DHT sensor!"));
		return;
	}

	// Compute heat index in Fahrenheit (the default)
	float hif = dht.computeHeatIndex(f, h);
	// Compute heat index in Celsius (isFahreheit = false)
	float hic = dht.computeHeatIndex(t, h, false);

	Serial.print(F("Humidity: "));
	Serial.print(h);
	Serial.print(F("%  Temperature: "));
	Serial.print(t);
	Serial.print(F("ºC "));
	Serial.print(f);
	Serial.print(F("ºF  Heat index: "));
	Serial.print(hic);
	Serial.print(F("ºC "));
	Serial.print(hif);
	Serial.println(F("ºF"));
}
