
#include "Servidor.h"
#include "Sensores.h"


#include "classDatos.h"
classDatos ArchivoDatos;

#include "Memoria.h"
#include "Prediccion.h"

#include "TramasMicros2.h"

//#include "Perceptron.h"

int HoraGruadado = 0;



void ObtenerDatos() {

  ArchivoDatos.HumedadAmbiente = GetHumedadAmbiente();
  ArchivoDatos.TemperaturaAmbiente = GetTemperaturaAmbiente() ;
  ArchivoDatos.PresionAmbiente = GetPresionAmbiente();
  ArchivoDatos.HumedadSuelo1 = i2c_GetHumedadSuelo1() ;
  ArchivoDatos.HumedadSuelo2 = i2c_GetHumedadSuelo2() ;

  classFecha FechaActual;
  FechaActual = GetFecha(FechaActual);
  ArchivoDatos.Anio = FechaActual.Anio ;
  ArchivoDatos.Mes = FechaActual.Mes ;
  ArchivoDatos.Dia = FechaActual.Dia ;
  ArchivoDatos.Hora = FechaActual.Hora ;
  ArchivoDatos.Minuto = FechaActual.Minuto ;
  ArchivoDatos.Segundo = FechaActual.Segundo ;
  ArchivoDatos.Riego1Segundos = 0 ;
  ArchivoDatos.Riego2Segundos = 0 ;


  if (HoraGruadado <  ArchivoDatos.Hora) {
    HoraGruadado = ArchivoDatos.Hora;
    ArchivoDatos.PresionHoras[5] = ArchivoDatos.PresionHoras[6];
    ArchivoDatos.PresionHoras[4] = ArchivoDatos.PresionHoras[3];
    ArchivoDatos.PresionHoras[3] = ArchivoDatos.PresionHoras[2];
    ArchivoDatos.PresionHoras[2] = ArchivoDatos.PresionHoras[1];
    ArchivoDatos.PresionHoras[1] = ArchivoDatos.PresionHoras[0];
    ArchivoDatos.PresionHoras[0] = ArchivoDatos.PresionAmbiente;

    ArchivoDatos.TemperaturaHoras[5] = ArchivoDatos.TemperaturaHoras[6];
    ArchivoDatos.TemperaturaHoras[4] = ArchivoDatos.TemperaturaHoras[3];
    ArchivoDatos.TemperaturaHoras[3] = ArchivoDatos.TemperaturaHoras[2];
    ArchivoDatos.TemperaturaHoras[2] = ArchivoDatos.TemperaturaHoras[1];
    ArchivoDatos.TemperaturaHoras[1] = ArchivoDatos.TemperaturaHoras[0];
    ArchivoDatos.TemperaturaHoras[0] = ArchivoDatos.TemperaturaAmbiente;

    Guardar_Hora(ArchivoDatos.Hora, ArchivoDatos.HumedadAmbiente,  ArchivoDatos.TemperaturaAmbiente, ArchivoDatos.PresionAmbiente, ArchivoDatos.HumedadSuelo1, ArchivoDatos.HumedadSuelo2);

    // i2c_SetHumedadSuelo2MinMax();
    // i2c_SetHumedadSuelo1MinMax();
    i2c_SetHumedadAmbiente();
    i2c_SetTemperaturaAmbiente();
    i2c_SetPresionAmbiente();
    i2c_SetAnio();
    i2c_SetMes();
    i2c_SetHora();
    i2c_SetDia();
    i2c_SetMinuto();
    i2c_SetSegundo();
    double HumedadSuelo1 = i2c_GetHumedadSuelo1();
    double HumedadSuelo2 =  i2c_GetHumedadSuelo2();
    //double Riego1Cantidad = i2c_Regar1();
    //double Riego2Cantidad = i2c_Regar2();


  }


  if (ArchivoDatos.Hora == 7) {
    ArchivoDatos.TemperaturaDias[5];
    ArchivoDatos.PresionDias[5];

    ArchivoDatos.TemperaturaDias[5] = ArchivoDatos.TemperaturaDias[6];
    ArchivoDatos.TemperaturaDias[4] = ArchivoDatos.TemperaturaDias[3];
    ArchivoDatos.TemperaturaDias[3] = ArchivoDatos.TemperaturaDias[2];
    ArchivoDatos.TemperaturaDias[2] = ArchivoDatos.TemperaturaDias[1];
    ArchivoDatos.TemperaturaDias[1] = ArchivoDatos.TemperaturaDias[0];
    ArchivoDatos.TemperaturaDias[0] = ArchivoDatos.TemperaturaAmbiente;

    ArchivoDatos.PresionDias[5] = ArchivoDatos.PresionDias[6];
    ArchivoDatos.PresionDias[4] = ArchivoDatos.PresionDias[3];
    ArchivoDatos.PresionDias[3] = ArchivoDatos.PresionDias[2];
    ArchivoDatos.PresionDias[2] = ArchivoDatos.PresionDias[1];
    ArchivoDatos.PresionDias[1] = ArchivoDatos.PresionDias[0];
    ArchivoDatos.PresionDias[0] = ArchivoDatos.TemperaturaAmbiente;
    Guardar_Dia(ArchivoDatos.Anio, ArchivoDatos.Mes, ArchivoDatos.Dia, ArchivoDatos.Hora, ArchivoDatos.Minuto, ArchivoDatos.Segundo, ArchivoDatos.HumedadAmbiente,  ArchivoDatos.TemperaturaAmbiente, ArchivoDatos.PresionAmbiente, ArchivoDatos.HumedadSuelo1, ArchivoDatos.HumedadSuelo2);

    // i2c_SetHumedadSuelo2MinMax();
    // i2c_SetHumedadSuelo1MinMax();
    i2c_SetHumedadAmbiente();
    i2c_SetTemperaturaAmbiente();
    i2c_SetPresionAmbiente();
    i2c_SetAnio();
    i2c_SetMes();
    i2c_SetHora();
    i2c_SetDia();
    i2c_SetMinuto();
    i2c_SetSegundo();
    double HumedadSuelo1 = i2c_GetHumedadSuelo1();
    double HumedadSuelo2 =  i2c_GetHumedadSuelo2();
    //double Riego1Cantidad = i2c_Regar1();
    //double Riego2Cantidad = i2c_Regar2();
  }


  String FechaActualSend = String(ArchivoDatos.Anio) + " / " + String(ArchivoDatos.Mes) + " / " + String(ArchivoDatos.Dia) + " / " + String(ArchivoDatos.Hora) + " : " + String(ArchivoDatos.Minuto) + " : " + String(ArchivoDatos.Segundo)  ;


  SetParametrosHtml(ArchivoDatos.TemperaturaAmbiente,  ArchivoDatos.HumedadAmbiente, ArchivoDatos.PresionAmbiente, ArchivoDatos.TemperaturaHoras, ArchivoDatos.PresionHoras, FechaActualSend);
  SetParametrosHtmlSD(LeerArchivo());
  RiegoSuelo1_INO();
  ArchivoDatos.PrediccionPresion = prediccionPresion(ArchivoDatos.PresionHoras);
  SetParametrosHtmlPrediccionBaro(ArchivoDatos.PrediccionPresion);
}

void RiegoSuelo1_INO() {
  int TiempoRiego1 = Riego1ServerGet();
  if (TiempoRiego1 > 0) {
    i2c_Regar1(TiempoRiego1);
  }
  int TiempoRiego2 = Riego2ServerGet();
  if (TiempoRiego2 > 0) {
    i2c_Regar2(TiempoRiego2);
  }
}


TramaTiempo blink_ObtenerDatos = TramaTiempo(5000003, ObtenerDatos);
TramaTiempo blink_ServerLoop = TramaTiempo(150211, loopServer);


ESP8266WebServer server(80);

void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  setup_Server();
  setup_Sensores(); delay(100);
  ObtenerDatos(); delay(100);
  ObtenerDatos();
  //InicializarPerceptron();
  ObtenerDatos(); delay(100); Serial.print(".");
//  ObtenerDatos(); delay(200); Serial.print(".");
//  ObtenerDatos(); delay(150); Serial.print(".");
//  ObtenerDatos(); delay(100); Serial.print(".");
//  ObtenerDatos(); delay(100); Serial.print(".");
//  ObtenerDatos(); delay(100); Serial.println(".");
}

void loop(void) {
  //loopServer();
  blink_ServerLoop.check();

  blink_ObtenerDatos.check();


  //tiempoMicrosSegundos = 10000000
  // ESP.deepSleep(tiempoMicrosSegundos);
  // Entra en modo ESP8266 deep sleep durante 10 segundos   4.300 millones de µs lo que viene a ser unos 71 minutos. Este es el máximo de tiempo que puede estar en sueño profundo.
  //ESP.deepSleep(10e6);


  //modo: es el modo de ahorro de operación que quieres utilizar. Puede tomar 3 valores posibles.
  //modo =WIFI_NONE_SLEEP ;//  para poner mono activo, sin ahorro de energía.
  //modo =WIFI_LIGHT_SLEEP ;//  para poner modo sueño ligero.
  //modo = WIFI_MODEM_SLEEP ;// para poner modo modem suspendido.
  //WiFi.setSleepMode(WIFI_MODEM_SLEEP);

  //  temperature = GetTemperaturaAmbiente() ;//(bmp180.getTemperature() + dht.readTemperature()) / 2;
  //  humidity = GetHumedadAmbiente() ;// dht.readHumidity();
  //  pressure = GetPresionAmbiente() ;// bmp180.getPressure();
  //  altitude = 0;//bme.readAltitude(SEALEVELPRESSURE_HPA);


}