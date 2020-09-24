#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "classDatos.h"
extern classDatos ArchivoDatos;



#include "Servidor.h"
//#include "Sensores.h"

#ifndef STASSID
#define STASSID "Neurotron"
#define STAPSK  "Caperuzo001"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

//ESP8266WebServer server(80);


// Variable to store the HTTP request
String header;


bool SetParametros = false;

String FechaHTML = "";



String ArchivoTexto = "";
String ArchivoTexto2 = "";

int Riego1Segundos = 0;
int Riego2Segundos = 0;
int Riego1ServerGet() {
	int var = Riego1Segundos;
	Riego1Segundos = 0;
	return var;
}
int Riego2ServerGet() {
	int var = Riego2Segundos;
	Riego2Segundos = 0;
	return var;
}
bool NuevaFecha = false;
bool ServerNuevaFecha() {
	if (NuevaFecha == true) {
		NuevaFecha = false;
		return true;
		} else {
		return false;
	}
}

const String postForms = "<html>\
<head>\
<title>ESP8266 Web Server POST handling</title>\
<style>\
body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
</style>\
</head>\
<body>\
<h1>Sensores /postform/</h1><br>\
<form method=\"post\" enctype=\"text/plain\" action=\"/sensores/\">\
<input type=\"text\" name=\"sensores\" value=\"todos\"><br>\
<input type=\"submit\" value=\"Submit\">\
<a type=\"submit\" href=\"/texto\">- SD -</a>\
</form>\
<h1>POST plain text to /postplain/</h1><br>\
<form method=\"post\" enctype=\"text/plain\" action=\"/postplain/\">\
<input type=\"text\" name=\'{\"Configuracion\": \"world\", \"trash\": \"\' value=\"0\"\'\"}\'><br>\
<input type=\"submit\" value=\"Submit\">\
<input type=\"text\" name=\'{\"Regar\": \"sensores\", \"segundos\": \"\' value=\"0\"\'\"}\'><br>\
<input type=\"submit\" value=\"Submit\">\
</form>\
<h1>Posicion</h1><br>\
<form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/geoposicion/\">\
Altura en metros <input type=\"text\" name=\"Altura\" value=\"700\"><br>\
<input type=\"submit\" value=\"Submit\">\
</form>\
<h1>Historial</h1><br>\
<form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/historial_horas/\">\
<h2>Historial en horas</h2>\
<table>\
<tr>\
<td>presion hace 0 hora <input type=\"text\" name=\"presion0\" value=\"-\"> mhPa<br></td>\
<td>presion hace 1 hora <input type=\"text\" name=\"presion1\" value=\"-\"> mhPa<br></td>\
<td>presion hace 2 hora <input type=\"text\" name=\"presion2\" value=\"-\"> mhPa<br></td>\
<td>presion hace 3 hora <input type=\"text\" name=\"presion3\" value=\"-\"> mhPa<br></td>\
<td>presion hace 4 hora <input type=\"text\" name=\"presion4\" value=\"-\"> mhPa<br></td>\
<td>presion hace 5 hora <input type=\"text\" name=\"presion5\" value=\"-\"> mhPa<br></td></tr>\
<tr>\
<td>temperatura hace 0 hora <input type=\"text\" name=\"temperatura0\" value=\"-\"><br></td>\
<td>temperatura hace 1 hora <input type=\"text\" name=\"temperatura1\" value=\"-\"><br></td>\
<td>temperatura hace 2 hora <input type=\"text\" name=\"temperatura2\" value=\"-\"><br></td>\
<td>temperatura hace 3 hora <input type=\"text\" name=\"temperatura3\" value=\"-\"><br></td>\
<td>temperatura hace 4 hora <input type=\"text\" name=\"temperatura4\" value=\"-\"><br></td>\
<td>temperatura hace 5 hora <input type=\"text\" name=\"temperatura5\" value=\"-\"><br></td></tr>\
</table>\
<input type=\"submit\" value=\"Submit\">\
</form>\
<form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/historial_dias/\">\
<h2>Historial en dias</h2>\
<table>\
<tr>\
<td>presion hace 0 dias <input type=\"text\" name=\"presion0Dia\" value=\"-\"> mhPa<br></td>\
<td>presion hace 1 dias <input type=\"text\" name=\"presion1Dia\" value=\"-\"> mhPa<br></td>\
<td>presion hace 2 dias <input type=\"text\" name=\"presion2Dia\" value=\"-\"> mhPa<br></td>\
<td>presion hace 3 dias <input type=\"text\" name=\"presion3Dia\" value=\"-\"> mhPa<br></td>\
<td>presion hace 4 dias <input type=\"text\" name=\"presion4Dia\" value=\"-\"> mhPa<br></td>\
<td>presion hace 5 dias <input type=\"text\" name=\"presion5Dia\" value=\"-\"> mhPa<br></td></tr>\
<tr>\
<td>temperatura hace 0 dias <input type=\"text\" name=\"temperatura0Dia\" value=\"-\"><br></td>\
<td>temperatura hace 1 dias <input type=\"text\" name=\"temperatura1Dia\" value=\"-\"><br></td>\
<td>temperatura hace 2 dias <input type=\"text\" name=\"temperatura2Dia\" value=\"-\"><br></td>\
<td>temperatura hace 3 dias <input type=\"text\" name=\"temperatura3Dia\" value=\"-\"><br></td>\
<td>temperatura hace 4 dias <input type=\"text\" name=\"temperatura4Dia\" value=\"-\"><br></td>\
<td>temperatura hace 5 dias <input type=\"text\" name=\"temperatura5Dia\" value=\"-\"><br></td></tr>\
<tr>\
<td>humedad hace 0 dias <input type=\"text\" name=\"humedad0Dia\" value=\"-\"><br></td>\
<td>humedad hace 1 dias <input type=\"text\" name=\"humedad1Dia\" value=\"-\"><br></td>\
<td>humedad hace 2 dias <input type=\"text\" name=\"humedad2Dia\" value=\"-\"><br></td>\
<td>humedad hace 3 dias <input type=\"text\" name=\"humedad3Dia\" value=\"-\"><br></td>\
<td>humedad hace 4 dias <input type=\"text\" name=\"humedad4Dia\" value=\"-\"><br></td>\
<td>humedad hace 5 dias <input type=\"text\" name=\"humedad5Dia\" value=\"-\"><br></td></tr>\
</table>\
<input type=\"submit\" value=\"Submit\">\
</form>\
<h1>Riego</h1><br>\
<form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/postform/\">\
Purga suelo 1 = <input type=\"text\" name=\"Purga1\" value=\"0\"><br>\
Purga suelo 1 = <input type=\"text\" name=\"Purga2\" value=\"0\"><br>\
Riego suelo 1 = <input type=\"text\" name=\"Riego1\" value=\"0\"><br>\
Riego suelo 2 = <input type=\"text\" name=\"Riego2\" value=\"0\"><br>\
Riego suelo 1 diario = <input type=\"text\" name=\"Riego1diario\" value=\"0\"><br>\
Riego suelo 1 diario hora = <input type=\"text\" name=\"Riego1diarioHora\" value=\"0\"><br>\
Riego suelo 2 diario hora = <input type=\"text\" name=\"Riego2diarioHora\" value=\"0\"><br>\
<input type=\"submit\" value=\"Submit\">\
</form>\
<h1>Fecha</h1><br>\
<form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/postfecha/\">\
Año = <input type=\"text\" name=\"Anio\" value=\"-\"><br>\
Mes = <input type=\"text\" name=\"Mes\" value=\"-\"><br>\
Dia = <input type=\"text\" name=\"Dia\" value=\"-\"><br>\
Hora = <input type=\"text\" name=\"Hora\" value=\"-\"><br>\
Minuto = <input type=\"text\" name=\"Minuto\" value=\"-\"><br>\
Segundo = <input type=\"text\" name=\"Segundo\" value=\"-\"><br>\
<input type=\"submit\" value=\"Submit\">\
</form>\
</body>\
</html>";


void setup_Server() {
	//pinMode(led, OUTPUT);
	//digitalWrite(led, 0);
	WiFi.begin(ssid, password);
	Serial.println("");
	int Intentoscontador = 0;
	// Wait for connection
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
		Intentoscontador++;
		if (Intentoscontador > 10)
		{
			Serial.print("Configuring access point...");
			WiFi.softAP(ssid, password);
			IPAddress myIP = WiFi.softAPIP();
			Serial.print("AP IP address: ");
			Serial.println(myIP);
			break;
		}
	}
	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	if (MDNS.begin("esp8266")) {
		Serial.println("MDNS responder started");
	}

	server.on("/", handleRoot);
	server.on("/postplain/", handlePlain);
	server.on("/postform/", handleForm);
	server.on("/sensores/", handle_OnConnect);
	server.on("/prediccion", handleForm);
	server.on("/texto", handle_SD);
	server.on("/geoposicion/", handle_geoposicion);
	server.on("/historial_horas/", handle_HistorialHoras);
	server.on("/historial_dias/", handle_HistorialDias);
	server.on("/postfecha/", handle_Fecha);
	server.onNotFound(handleNotFound);

	server.begin();
	Serial.println("HTTP server started");

}

void loopServer() {
	server.handleClient();
	//handleClient();

}

void handleRoot() {
	//  digitalWrite(led, 1);
	server.send(200, "text/html", postForms);
	//send(200, "text/html", postForms);
	// digitalWrite(led, 0);
}

void handlePlain() {
	if (server.method() != HTTP_POST) {
		//digitalWrite(led, 1);
		server.send(405, "text/plain", "Method Not Allowed");
		//digitalWrite(led, 0);
		} else {
		//digitalWrite(led, 1);

		String message = "FOR :\n";
		for (uint8_t i = 0; i < server.args(); i++) {
			message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
			message += " server.argName(i)= " + server.argName(i) + "\n";
			message += " server.arg(i)= " + server.arg(i) + "\n";
			//message += " server.arg(i)= " + server.value(i) + "\n";
			if ( server.argName(i) == "\"segundos\"") {
				//Regar1Tiempo = (server.arg(i).toInt());
				message += "Regando1 " + server.arg(i) + " segundos. \n";
			}

		}
		server.send(200, "text/plain", "POST body was:\n" + server.arg("plain") + "\n" + message);
	}

	//digitalWrite(led, 0);

	//  if (method() != HTTP_POST) {
	//    digitalWrite(led, 1);
	//    send(405, "text/plain", "Method Not Allowed");
	//    digitalWrite(led, 0);
	//  } else {
	//    digitalWrite(led, 1);
	//    send(200, "text/plain", "POST body was:\n" + arg("plain"));
	//    digitalWrite(led, 0);
	//  }
	//}

}

void handleForm() {
	if (server.method() != HTTP_POST) {
		//digitalWrite(led, 1);
		server.send(405, "text/plain", "Method Not Allowed");
		//digitalWrite(led, 0);
		} else {
		//digitalWrite(led, 1);
		String message = "POST form was:\n";
		for (uint8_t i = 0; i < server.args(); i++) {
			message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
			if ( server.argName(i) == "Riego1") {
				Riego1Segundos = (server.arg(i).toInt());
				message += "Regando1 " + server.arg(i) + " segundos. \n";
			}
			if ( server.argName(i) == "Riego2") {
				Riego2Segundos = (server.arg(i).toInt());
				message += "Regando2 " + server.arg(i) + " segundos. \n";
			}
			if ( server.argName(i) == "Purga1") {
				Riego2Segundos = (server.arg(i).toInt());
				message += "Regando2 " + server.arg(i) + " segundos. \n";
			}
			if ( server.argName(i) == "Purga2") {
				Riego2Segundos = (server.arg(i).toInt());
				message += "Regando2 " + server.arg(i) + " segundos. \n";
			}

		}
		server.send(200, "text/plain", message + " " + postForms);
		//digitalWrite(led, 0);
	}

	//  if (method() != HTTP_POST) {
	//    digitalWrite(led, 1);
	//    send(405, "text/plain", "Method Not Allowed");
	//    digitalWrite(led, 0);
	//  } else {
	//    digitalWrite(led, 1);
	//    String message = "POST form was:\n";
	//    for (uint8_t i = 0; i < args(); i++) {
	//      message += " " + argName(i) + ": " + arg(i) + "\n";
	//    }
	//    send(200, "text/plain", message);
	//    digitalWrite(led, 0);
	//  }
}

void handleNotFound() {
	//digitalWrite(led, 1);
	String message = "File Not Found\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += (server.method() == HTTP_GET) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";
	for (uint8_t i = 0; i < server.args(); i++) {
		message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
	}
	server.send(404, "text/plain", message);
	//digitalWrite(led, 0);


	//  digitalWrite(led, 1);
	//  String message = "File Not Found\n\n";
	//  message += "URI: ";
	//  message += uri();
	//  message += "\nMethod: ";
	//  message += (method() == HTTP_GET) ? "GET" : "POST";
	//  message += "\nArguments: ";
	//  message += args();
	//  message += "\n";
	//  for (uint8_t i = 0; i < args(); i++) {
	//    message += " " + argName(i) + ": " + arg(i) + "\n";
	//  }
	//  send(404, "text/plain", message);
	//  digitalWrite(led, 0);
}

void handle_OnConnect() {
	server.send(200, "text/html", SendHTML(ArchivoDatos.TemperaturaAmbiente, ArchivoDatos.HumedadAmbiente, ArchivoDatos.PresionAmbiente, ArchivoDatos.Altitud, FechaHTML, ArchivoDatos.PrediccionPresion));
}

void handle_SD() {
	server.send(200, "text/html", SendHTML_SD());
}

void handle_geoposicion() {
	if (server.method() != HTTP_POST) {
		//digitalWrite(led, 1);
		server.send(405, "text/plain", "Method Not Allowed");
		//digitalWrite(led, 0);
		} else {
		//digitalWrite(led, 1);
		String message = "POST form was:\n";
		for (uint8_t i = 0; i < server.args(); i++) {
			message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
			if ( server.argName(i) == "Altura") {
				ArchivoDatos.Altitud = (server.arg(i).toInt());
				message += "Altura " + server.arg(i) + " metros. \n";
			}


		}
		server.send(200, "text/plain", message + " " + postForms);
	}
	server.send(200, "text/html", postForms);

}

void handle_HistorialHoras() {
	if (server.method() != HTTP_POST) {
		//digitalWrite(led, 1);
		server.send(405, "text/plain", "Method Not Allowed");
		//digitalWrite(led, 0);
		} else {
		//digitalWrite(led, 1);
		for (uint8_t i = 0; i < server.args(); i++) {
			if ( server.arg(i) != 0) {
				SetParametros = true;




				if (server.argName(i) == "presion0") {
					ArchivoDatos.PresionHoras[0] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "presion1") {
					ArchivoDatos.PresionHoras[1] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "presion2") {
					ArchivoDatos.PresionHoras[2] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "presion3") {
					ArchivoDatos.PresionHoras[3] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "presion4") {
					ArchivoDatos.PresionHoras[4] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "presion5") {
					ArchivoDatos.PresionHoras[5] = server.arg(i).toFloat();
				}

				else if (server.argName(i) == "temperatura0") {
					ArchivoDatos.TemperaturaHoras[0] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "temperatura1") {
					ArchivoDatos.TemperaturaHoras[1] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "temperatura2") {
					ArchivoDatos.TemperaturaHoras[2] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "temperatura3") {
					ArchivoDatos.TemperaturaHoras[3] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "temperatura4") {
					ArchivoDatos.TemperaturaHoras[4] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "temperatura5") {
					ArchivoDatos.TemperaturaHoras[5] = server.arg(i).toFloat();
				}

			}
		}
	}
	server.send(200, "text/html", SendHTML(ArchivoDatos.TemperaturaAmbiente, ArchivoDatos.HumedadAmbiente, ArchivoDatos.PresionAmbiente,  ArchivoDatos.Altitud, FechaHTML, ArchivoDatos.PrediccionPresion));

}


void handle_HistorialDias() {
	if (server.method() != HTTP_POST) {
		//digitalWrite(led, 1);
		server.send(405, "text/plain", "Method Not Allowed");
		//digitalWrite(led, 0);
		} else {
		//digitalWrite(led, 1);
		for (uint8_t i = 0; i < server.args(); i++) {
			if ( server.arg(i) != "-") {
				SetParametros = true;



				if (server.argName(i) == "presion0Dia") {
					ArchivoDatos.PresionDias[0] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "presion1Dia") {
					ArchivoDatos.PresionDias[1] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "presion2Dia") {
					ArchivoDatos.PresionDias[2] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "presion3Dia") {
					ArchivoDatos.PresionDias[3] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "presion4Dia") {
					ArchivoDatos.PresionDias[4] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "presion5Dia") {
					ArchivoDatos.PresionDias[5] = server.arg(i).toFloat();
				}

				else if (server.argName(i) == "temperatura0Dia") {
					ArchivoDatos.TemperaturaDias[0] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "temperatura1Dia") {
					ArchivoDatos.TemperaturaDias[1] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "temperatura2Dia") {
					ArchivoDatos.TemperaturaDias[2] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "temperatura3Dia") {
					ArchivoDatos.TemperaturaDias[3] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "temperatura4Dia") {
					ArchivoDatos.TemperaturaDias[4] = server.arg(i).toFloat();
				}
				else  if (server.argName(i) == "temperatura5Dia") {
					ArchivoDatos.TemperaturaDias[5] = server.arg(i).toFloat();
				}

				else if (server.argName(i) == "humedad0Dia") {
					ArchivoDatos.HumedadDias[0] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "humedad1Dia") {
					ArchivoDatos.HumedadDias[1] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "humedad2Dia") {
					ArchivoDatos.HumedadDias[2] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "humedad3Dia") {
					ArchivoDatos.HumedadDias[3] = server.arg(i).toFloat();
				}
				else if (server.argName(i) == "humedad4Dia") {
					ArchivoDatos.HumedadDias[4] = server.arg(i).toFloat();
				}
				else  if (server.argName(i) == "humedad5Dia") {
					ArchivoDatos.HumedadDias[5] = server.arg(i).toFloat();
				}

			}
		}
	}
	server.send(200, "text/html", SendHTML(ArchivoDatos.TemperaturaAmbiente, ArchivoDatos.HumedadAmbiente, ArchivoDatos.PresionAmbiente,  ArchivoDatos.Altitud, FechaHTML, ArchivoDatos.PrediccionPresion));

}

void handle_Fecha () {
	if (server.method() != HTTP_POST) {
		//digitalWrite(led, 1);
		server.send(405, "text/plain", "Method Not Allowed");
		//digitalWrite(led, 0);
		} else {
		//digitalWrite(led, 1);
		for (uint8_t i = 0; i < server.args(); i++) {
			if ( server.arg(i) != "-") {
				NuevaFecha = true;
				if (server.argName(i) == "Anio") {
					ArchivoDatos.Anio = server.arg(i).toFloat();
				}
				if (server.argName(i) == "Mes") {
					ArchivoDatos.Mes = server.arg(i).toFloat();
				}
				if (server.argName(i) == "Dia") {
					ArchivoDatos.Dia = server.arg(i).toFloat();
				}
				if (server.argName(i) == "Hora") {
					ArchivoDatos.Hora = server.arg(i).toFloat();
				}
				if (server.argName(i) == "Minuto") {
					ArchivoDatos.Minuto = server.arg(i).toFloat();
				}
				if (server.argName(i) == "Segundo") {
					ArchivoDatos.Segundo = server.arg(i).toFloat();
				}
			}
		}
	}
	String FechaActualSend = String(ArchivoDatos.Anio) + " / " + String(ArchivoDatos.Mes) + " / " + String(ArchivoDatos.Dia) + " / " + String(ArchivoDatos.Hora) + " : " + String(ArchivoDatos.Minuto) + " : " + String(ArchivoDatos.Segundo)  ;
	server.send(200, "text/html", SendHTML(ArchivoDatos.TemperaturaAmbiente, ArchivoDatos.HumedadAmbiente, ArchivoDatos.PresionAmbiente,  ArchivoDatos.Altitud, FechaActualSend, ArchivoDatos.PrediccionPresion));
}


void SetParametrosHtml(float temperature_var, float humidity_var, float pressure_var, float Tempetura_var[5], float Presion_var[5], String FechaHtml_var) {
	//temperature = temperature_var;
	//humidity = humidity_var;
	//pressure =  pressure_var;
	FechaHTML = FechaHtml_var;
	//  Presion = Presion_var;
	//  Temperatura = Tempetura_var;
}

String SendHTML(float temperature, float humidity, float pressure, float altitude, String FechaHtml, float PrediccionPresion) {
	String ptr = "<!DOCTYPE html> <html>\n";
	ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
	ptr += "<title>ESP8266 Weather Station</title>\n";
	ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
	ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
	ptr += "p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
	ptr += "</style>\n";
	ptr += "</head>\n";
	ptr += "<body>\n";
	ptr += "<div id=\"webpage\">\n";
	ptr += "<h1>ESP8266 Weather Station</h1>\n";
	ptr += "<p>fecha ";
	String FechaActual = String(ArchivoDatos.Dia) + "/" + String(ArchivoDatos.Mes) + "/" + String(ArchivoDatos.Anio) + "   " + String(ArchivoDatos.Hora) + ":" + String(ArchivoDatos.Minuto) + ":" + String(ArchivoDatos.Segundo)  ;
	ptr += FechaActual;
	ptr += "</p>";
	ptr += "<p>Temperature: ";
	ptr += temperature;
	ptr += " C</p>";
	ptr += "<p>Humidity: ";
	ptr += humidity;
	ptr += "%</p>";
	ptr += "<p>Pressure: ";
	ptr += pressure / 100;
	ptr += "hPa</p>";
	ptr += "<p>Altitude: ";
	ptr +=  altitude;
	ptr += " m</p><p>  Presion a ";
	double PresionAltura = (pressure + (9.8 * 1.225 *  altitude)) / 100;
	// ( Pa - Pa ) / ( 9.8 * 1.225 )
	ptr += PresionAltura;
	ptr += " hPa</p>";
	ptr += "<p>  Punto de rocio ";
	ptr += ArchivoDatos.PuntoRocio;
	ptr += " C</p>";
	ptr += "<p>";
	if ((PrediccionPresion < 0) ) {
		if ((PrediccionPresion < -38400) && ((ArchivoDatos.PrediccionDias < 0) && (ArchivoDatos.PrediccionDias > -1))) {
			ptr += " Chubasco ";
		}
		else if ((PrediccionPresion < -37400) && (ArchivoDatos.PrediccionDias < 0)) {
			ptr += " Lluvia ";
		}
		else if ((PrediccionPresion <= -37562) && ((ArchivoDatos.PrediccionDias > -1) && (ArchivoDatos.PrediccionDias < 0))) {
			ptr += " Intervalos lluviosos ";
		}
		else if ((PrediccionPresion >= -37562) && (PrediccionPresion <= -400) && (ArchivoDatos.PrediccionDias < 0)) {
			ptr += " Nubes ";
		}
		else {
			ptr += " Nubes y claros ";
		}
		ptr += "<br> BORRASCA ";
		} else {
		if ((PrediccionPresion < 400) &&  (ArchivoDatos.PrediccionDias < -1)) {
			ptr += " Intervalos nubosos ";
		}
		else  {
			ptr += " Sol ";
		}
		ptr += "<br> ANTICICLON ";
	}
	ptr += PrediccionPresion;
	ptr += "<br> Prediccion dias";
	ptr += ArchivoDatos.PrediccionDias;
	ptr += "</p>";

	ptr += "<p><table>";
	ptr += "  <tr>";
	ptr += "   <td>-0h</td>";
	ptr += "   <td>-1h</td>";
	ptr += "   <td>-2h</td>";
	ptr += "   <td>-3h</td>";
	ptr += "   <td>-4h</td>";
	ptr += "   <td>-5h</td>";
	ptr += "  </tr>";
	ptr += "<tr>";
	ptr += "<td>" ;
	ptr += ArchivoDatos.PresionHoras[0] / 100 ;
	ptr += "hPa</td>";
	ptr += "<td>" ;
	ptr += ArchivoDatos.PresionHoras[1] / 100 ;
	ptr += "hPa</td>";
	ptr += "<td>" ;
	ptr += ArchivoDatos.PresionHoras[2] / 100 ;
	ptr += "hPa</td>";
	ptr += "<td>" ;
	ptr += ArchivoDatos.PresionHoras[3] / 100 ;
	ptr += "hPa</td>";
	ptr += "<td>" ;
	ptr += ArchivoDatos.PresionHoras[4] / 100 ;
	ptr += "hPa</td>";
	ptr += "<td>";
	ptr +=  ArchivoDatos.PresionHoras[5] / 100;
	ptr += "hPa</td>";
	ptr += "</tr>";
	ptr += "<tr>";
	ptr += "<td>";
	ptr += ArchivoDatos.TemperaturaHoras[0];
	ptr += "</td>";
	ptr += "<td>";
	ptr += ArchivoDatos.TemperaturaHoras[1];
	ptr += "</td>";
	ptr += "<td>";
	ptr += ArchivoDatos.TemperaturaHoras[2];
	ptr += "</td>";
	ptr += "<td>";
	ptr += ArchivoDatos.TemperaturaHoras[3];
	ptr += "</td>";
	ptr += "<td>";
	ptr += ArchivoDatos.TemperaturaHoras[4];
	ptr += "</td>";
	ptr += "<td>";
	ptr += ArchivoDatos.TemperaturaHoras[5];
	ptr += "</td>";
	ptr += "</tr>";
	ptr += "</table>";
	ptr += "<table>";
	ptr += "  <tr>";
	ptr += "   <td>-0d</td>";
	ptr += "   <td>-1d</td>";
	ptr += "   <td>-2d</td>";
	ptr += "   <td>-3d</td>";
	ptr += "   <td>-4d</td>";
	ptr += "   <td>-5d</td>";
	ptr += "  </tr>";
	ptr += "<tr>";
	ptr += "<td>" ;
	ptr += ArchivoDatos.PresionDias[0] / 100 ;
	ptr += "hPa</td>";
	ptr += "<td>" ;
	ptr += ArchivoDatos.PresionDias[1] / 100 ;
	ptr += "hPa</td>";
	ptr += "<td>" ;
	ptr += ArchivoDatos.PresionDias[2] / 100 ;
	ptr += "hPa</td>";
	ptr += "<td>" ;
	ptr += ArchivoDatos.PresionDias[3] / 100 ;
	ptr += "hPa</td>";
	ptr += "<td>" ;
	ptr += ArchivoDatos.PresionDias[4] / 100 ;
	ptr += "hPa</td>";
	ptr += "<td>";
	ptr +=  ArchivoDatos.PresionDias[5] / 100;
	ptr += "hPa</td>";
	ptr += "</tr>";
	ptr += "<tr>";
	ptr += "<td>";
	ptr += ArchivoDatos.TemperaturaDias[0];
	ptr += "</td>";
	ptr += "<td>";
	ptr += ArchivoDatos.TemperaturaDias[1];
	ptr += "</td>";
	ptr += "<td>";
	ptr += ArchivoDatos.TemperaturaDias[2];
	ptr += "</td>";
	ptr += "<td>";
	ptr += ArchivoDatos.TemperaturaDias[3];
	ptr += "</td>";
	ptr += "<td>";
	ptr += ArchivoDatos.TemperaturaDias[4];
	ptr += "</td>";
	ptr += "<td>";
	ptr += ArchivoDatos.TemperaturaDias[5];
	ptr += "</td>";
	ptr += "</tr>";
	ptr += "<tr>";
	ptr += "<td>";
	ptr += ArchivoDatos.HumedadDias[0];
	ptr += "%</td>";
	ptr += "<td>";
	ptr += ArchivoDatos.HumedadDias[1];
	ptr += "%</td>";
	ptr += "<td>";
	ptr += ArchivoDatos.HumedadDias[2];
	ptr += "%</td>";
	ptr += "<td>";
	ptr += ArchivoDatos.HumedadDias[3];
	ptr += "%</td>";
	ptr += "<td>";
	ptr += ArchivoDatos.HumedadDias[4];
	ptr += "%</td>";
	ptr += "<td>";
	ptr += ArchivoDatos.HumedadDias[5];
	ptr += "%</td>";
	ptr += "</tr>";
	ptr += "</table></p>";
	ptr += "</div>\n";

	ptr += "<div><p>\n";
	ptr += ArchivoTexto2;
	ptr += "</p></div>\n";
	ptr += "</body>\n";
	ptr += "</html>\n";
	return ptr;
}


String SendHTML_SD() {
	String FechaActualSend = String(ArchivoDatos.Anio) + " / " + String(ArchivoDatos.Mes) + " / " + String(ArchivoDatos.Dia) + " / " + String(ArchivoDatos.Hora) + " : " + String(ArchivoDatos.Minuto) + " : " + String(ArchivoDatos.Segundo)  ;

	String ptr = "<!DOCTYPE html> <html>\n";
	ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
	ptr += "<link href=\"https://fonts.googleapis.com/css?family=Open+Sans:300,400,600\" rel=\"stylesheet\">\n";
	ptr += "<title>ESP8266 Weather Report</title>\n";
	ptr += "<style>html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #333333;}\n";
	ptr += "body{margin-top: 50px;}\n";
	ptr += "h1 {margin: 50px auto 30px;}\n";
	ptr += ".side-by-side{display: inline-block;vertical-align: middle;position: relative;}\n";
	ptr += ".humidity-icon{background-color: #3498db;width: 30px;height: 30px;border-radius: 50%;line-height: 36px;}\n";
	ptr += ".humidity-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n";
	ptr += ".humidity{font-weight: 300;font-size: 60px;color: #3498db;}\n";
	ptr += ".temperature-icon{background-color: #f39c12;width: 30px;height: 30px;border-radius: 50%;line-height: 40px;}\n";
	ptr += ".temperature-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n";
	ptr += ".temperature{font-weight: 300;font-size: 60px;color: #f39c12;}\n";
	ptr += ".superscript{font-size: 17px;font-weight: 600;position: absolute;right: -20px;top: 15px;}\n";
	ptr += ".data{padding: 10px;}\n";
	ptr += "</style>\n";
	ptr += "</head>\n";
	ptr += "<body>\n";

	ptr += "<div id=\"webpage\">\n";

	ptr += "<h1>ESP8266 Weather Report</h1>\n";
	ptr += FechaActualSend;
	ptr += "<br>";
	ptr += "<div class=\"data\">\n";
	ptr += "<div class=\"side-by-side temperature-icon\">\n";
	ptr += "<svg version=\"1.1\" id=\"Layer_1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\n";
	ptr += "width=\"9.915px\" height=\"22px\" viewBox=\"0 0 9.915 22\" enable-background=\"new 0 0 9.915 22\" xml:space=\"preserve\">\n";
	ptr += "<path fill=\"#FFFFFF\" d=\"M3.498,0.53c0.377-0.331,0.877-0.501,1.374-0.527C5.697-0.04,6.522,0.421,6.924,1.142\n";
	ptr += "c0.237,0.399,0.315,0.871,0.311,1.33C7.229,5.856,7.245,9.24,7.227,12.625c1.019,0.539,1.855,1.424,2.301,2.491\n";
	ptr += "c0.491,1.163,0.518,2.514,0.062,3.693c-0.414,1.102-1.24,2.038-2.276,2.594c-1.056,0.583-2.331,0.743-3.501,0.463\n";
	ptr += "c-1.417-0.323-2.659-1.314-3.3-2.617C0.014,18.26-0.115,17.104,0.1,16.022c0.296-1.443,1.274-2.717,2.58-3.394\n";
	ptr += "c0.013-3.44,0-6.881,0.007-10.322C2.674,1.634,2.974,0.955,3.498,0.53z\"/>\n";
	ptr += "</svg>\n";
	ptr += "</div>\n";
	ptr += "<div class=\"side-by-side temperature-text\">Temperature</div>\n";
	ptr += "<div class=\"side-by-side temperature\">";
	ptr += (int)ArchivoDatos.TemperaturaAmbiente;
	ptr += "<span class=\"superscript\">°C</span></div>\n";
	ptr += "</div>\n";
	ptr += "<div class=\"data\">\n";
	ptr += "<div class=\"side-by-side humidity-icon\">\n";
	ptr += "<svg version=\"1.1\" id=\"Layer_2\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\n\"; width=\"12px\" height=\"17.955px\" viewBox=\"0 0 13 17.955\" enable-background=\"new 0 0 13 17.955\" xml:space=\"preserve\">\n";
	ptr += "<path fill=\"#FFFFFF\" d=\"M1.819,6.217C3.139,4.064,6.5,0,6.5,0s3.363,4.064,4.681,6.217c1.793,2.926,2.133,5.05,1.571,7.057\n";
	ptr += "c-0.438,1.574-2.264,4.681-6.252,4.681c-3.988,0-5.813-3.107-6.252-4.681C-0.313,11.267,0.026,9.143,1.819,6.217\"></path>\n";
	ptr += "</svg>\n";
	ptr += "</div>\n";
	ptr += "<div class=\"side-by-side humidity-text\">Humidity</div>\n";
	ptr += "<div class=\"side-by-side humidity\">";
	ptr += (int)ArchivoDatos.HumedadAmbiente;
	ptr += "<span class=\"superscript\">%</span></div>\n";
	ptr += "</div>\n";
	ptr += "</div>\n";

	ptr += "<div class=\"data\">\n";
	ptr += ArchivoTexto;
	ptr += "</div>\n";

	ptr += "<div class=\"data\">\n";
	ptr += ArchivoDatos.ArchivoTexto;
	ptr += "</div>\n";

	ptr += "</body>\n";
	ptr += "</html>\n";
	return ptr;
}

void SetParametrosHtmlSD(String Texto_var) {
	ArchivoTexto = Texto_var;
}
void SetParametrosHtmlSD2(String Texto_var) {
	ArchivoTexto2 = Texto_var;
}
