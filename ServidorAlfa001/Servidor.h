
#ifndef Servidor_H
#define Servidor_H
#endif

//#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <ESP8266WebServer.h>


extern ESP8266WebServer server;


void setup_Server();
void loopServer();

void handleRoot();
void handleNotFound();
void handlePlain();
void handleForm();
void handle_OnConnect();
void handle_SD();
void handle_geoposicion();
void handle_Historial();
String SendHTML(float temperature, float humidity, float pressure, float altitude, String FechaHtml);
String SendHTML_SD();
void SetParametrosHtml(float temperature_var, float humidity_var, float pressure_var, float Tempetura_var[5], float Presion_var[5], String FechaHtml_var);
void SetParametrosHtmlSD(String Texto);
void SetParametrosHtmlPrediccionBaro(byte Pred_var);


int Riego1ServerGet();
int Riego2ServerGet();
