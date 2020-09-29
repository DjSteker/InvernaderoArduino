
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
void handle_HistorialHoras();
void handle_HistorialDias();
void handle_Fecha();
void handle_Restaura();


String SendHTML(float temperature, float humidity, float pressure, float altitude, String FechaHtml, float PrediccionPresion);
String SendHTML_SD();
void SetParametrosHtml(float temperature_var, float humidity_var, float pressure_var, float Tempetura_var[5], float Presion_var[5], String FechaHtml_var);
void SetParametrosHtmlSD(String Texto);
void SetParametrosHtmlSD2(String Texto);
//void SetParametrosHtmlPrediccionBaro(float Pred_var);


int Riego1ServerGet();
int Riego2ServerGet();

bool ServerNuevaFecha();

//bool ServerRestauraHistorial();
bool ServerRestaura(); 

//ESP8266WebServer server(int a);

//class server : public ESP8266WebServer {
//  public:
//    server(int a);
//
//  private:
//    int32_t _id;
//
//};


//class server : public ESP8266WebServer {
//protected:
//

//class server : public ESP8266WebServer{
//  public:
//    server(int puerto);
//    void loopServer() ;
//    void setup_Inicio();
//
//  private:
//    void handleRoot() ;
//    void handlePlain() ;
//    void handleForm() ;
//    void handleNotFound() ;
//};
