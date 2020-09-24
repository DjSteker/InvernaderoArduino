//#include "DHT.h"
//
//#define DHTPIN 0     // Digital pin connected to the DHT sensor
//#define DHTTYPE DHT11
//DHT dht(DHTPIN, DHTTYPE);
//
//#include <Arduino.h>
//#include <Wire.h>
//#include "Adafruit_BMP085.h"
//Adafruit_BMP085 bmp180;
//
//#include "DS3231.h"
//RTClib RTC;

class classFecha {
	public:
	int Anio = 0 ;
	int Mes = 0 ;
	int Dia = 0 ;
	int Hora = 0 ;
	int Minuto = 0 ;
	int Segundo = 0 ;
	private:
};


double i2c_Regar1(int TiempoSeg);
double i2c_Regar2(int TiempoSeg);
double i2c_GetHumedadSuelo1();

void i2c_SetHumedadSuelo1MinMax();

double i2c_GetHumedadSuelo2();

void i2c_SetHumedadSuelo2MinMax();

void i2c_SetHumedadAmbiente();

void i2c_SetTemperaturaAmbiente() ;

void i2c_SetPresionAmbiente();


void i2c_SetAnio();
void i2c_SetMes();
void i2c_SetHora() ;

void i2c_SetDia() ;

void i2c_SetMinuto() ;

void i2c_SetSegundo() ;


double GetHumedadAmbiente();
double GetTemperaturaAmbiente();
double GetPresionAmbiente();


double GetAnio();
double GetMes();
double GetHora() ;

double GetDia();

double GetMinuto() ;

double GetSegundo() ;
classFecha GetFecha(classFecha ArchivoFecha) ;
classFecha SetFecha(classFecha ArchivoFecha) ;


void inicializar() ;

void lectura() ;


void EnviarFecha();

void Ambiente() ;


void setup_Sensores() ;


void loop1() ;
