

#define HumedadMinimaSuelo1 100
#define HumedadMinimaSuelo2 100

#define HumedadMaximaSuelo1 1023
#define HumedadMaximaSuelo2 1023

#define RiegoPredeterminadoSuelo1 60
#define RiegoPredeterminadoSuelo2 60

#define PinS8 9
#define PinS7 8
#define PinS6 7
#define PinS5 6
#define PinS4 5
#define PinS3 4
#define PinS2 3
#define PinS1 2

#include "TramasMicros2.h"

#include "Perceptron.h"

#include <Arduino.h>
#include <Wire.h>

bool Regando1 = false;
bool Regando2 = false;

void Predecir() {}


namespace {

#define PresionNivelMar 1013,2 //milibares que son 760mmHg milimetros de mercurio

float temp = 0;
float rh = 0;

struct estacion {
  //Prediccion
  byte pred;
  //Error
  byte error;
  //Datos
  int temp;
  int rh;
  int lux;
  int32_t pa;
  //Maximos
  int maxtemp;
  int maxrh;
  int maxlux;
  int32_t maxpa;
  //Minimos
  int mintemp;
  int minrh;
  int minlux;
  int32_t minpa;
} Datos;
//Prediccion
int32_t tempera[5];     //Array para los valores
int32_t presure[5];     //Array para los valores
int32_t humedad[5];
unsigned long time_pred = 0;
boolean first_pred = true;
byte i = 0;

//Variables conteo de tiempo e inicializacion
unsigned long time_past;
unsigned long tiempo_pas = 0;
unsigned long tiempo_envio = 0;
boolean reinicio = true;
boolean inicio = true;
boolean initiatemaxmin = false;

//int Año, Mes, Dia, Hora, Minuto, Segundo;
int Fecha[5];

//Funcion prediccion-----------------------------------------------------------------------------------------------------------------------
void prediccion() {
  float a, b, c, d, m; //Variables de calculo
  if (inicio == true) {
    presure[i] = Datos.pa;
    i = i + 1;
    time_pred = millis();
  }
  if (time_pred + 1800000 < millis()) { //Registramos datos cada media hora
    presure[i] = Datos.pa;
    i = i + 1;
    time_pred = millis();
  }
  if (i == 6) { //Cuando tenemos 6 datos, calculamos
    a = 6 * ((1 * presure[0]) + (2 * presure[1]) + (3 * presure[2]) + (4 * presure[3]) + (5 * presure[4]) + (6 * presure[5]));
    b = (720) * (presure[0] + presure[1] + presure[2] + presure[3] + presure[4] + presure[5]);
    c = 546;
    d = 441;
    m = (a - b) / (c - d);
    if (m < 0) {
      Datos.pred = 6; //Si m menor que cero, BORRASCA
    } else {
      Datos.pred = 7; //Si m mayor que cero, ANTICICLON
    }
    i = 0;  //Reiniciamos cuenta de datos
    first_pred = false;
  }
  if (first_pred == true) Datos.pred = i; //Si es la primera vez que iniciamos la estacion, esperamos hasta tener los 6 datos.
}
}


void EnviarDatos() {
  //  int sensorValue = analogRead(A0);
  //  int sensorValue = analogRead(A1);
  //  int sensorValue = analogRead(A2);
  //  int sensorValue = analogRead(A3);
  //  int sensorValue = analogRead(A6);
}

void ActulizarDatos() {
  Datos.pa = 1;// bmp.readPressure();
  Datos.rh = 1; // DHT.humidity * 10;
  Datos.temp = 1; // DHT.temperature * 10;
  //Variables de operacion
  temp = 1; // DHT.temperature;
  rh = 1; // DHT.humidity;
}


TramaTiempo blink_DatosEnviar = TramaTiempo(500003, EnviarDatos);
TramaTiempo blink_Predecir = TramaTiempo(1800000000, prediccion);
TramaTiempo blink_Regar1 = TramaTiempo(10000, Regar1);
TramaTiempo blink_Regar2 = TramaTiempo(10000, Regar2);


void Regar1() {
  Serial.println("regando 1 -");
  pinMode(LED_BUILTIN, OUTPUT);
  if (Regando1 == true) {
    digitalWrite(LED_BUILTIN, HIGH);
    Regando1 = false;
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
    blink_Regar1.disable();
  }
}
void Regar2() {
  pinMode(LED_BUILTIN, OUTPUT);
  if (Regando2 == true) {
    digitalWrite(LED_BUILTIN, HIGH);
    Regando2 = false;
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
    blink_Regar2.disable();
  }
}

int ReferenciaWireGlobal = 0;
int ValorWireGlobal = 0;

void receiveEvent(int howMany) {
  //  while (1 < Wire.available()) { // loop through all but the last
  //    char c = Wire.read(); // receive byte as a character
  //    Serial.print(c);         // print the character
  //  }
  //  int x = Wire.read();    // receive byte as an integer
  //  Serial.println(x);         // print the integer


  int WireReferencia = Wire.read();//Wire.available();
  //int32_t WireValor = Wire.read();

  // Si hay dos bytes disponibles
  if (WireReferencia == 1) // Tempetatura
  {
    int32_t WireValor = Wire.read();
    tempera[5] =  tempera[4];
    tempera[4] =  tempera[3];
    tempera[3] =  tempera[2];
    tempera[2] =  tempera[1];
    tempera[1] =  tempera[0];
    tempera[0] =  WireValor;
  }
  if (WireReferencia == 2) // Humedad
  {
    int32_t WireValor = Wire.read();
    humedad[5] =  humedad[4];
    humedad[4] =  humedad[3];
    humedad[3] =  humedad[2];
    humedad[2] =  humedad[1];
    humedad[1] =  humedad[0];
    humedad[0] =  WireValor;
  }
  if (WireReferencia == 3) // Presion
  {
    int32_t WireValor = Wire.read();
    presure[5] =  presure[4];
    presure[4] =  presure[3];
    presure[3] =  presure[2];
    presure[2] =  presure[1];
    presure[1] =  presure[0];
    presure[0] =  WireValor;
  }
  if (WireReferencia == 4) // Humedad suelo 1
  {
    int32_t WireValor = Wire.read();
    Wire.write(analogRead(A0));

  }
  if (WireReferencia == 5) // Humedad suelo 2
  {
    int32_t WireValor = Wire.read();
    Wire.write(analogRead(A1));

  }
  if (WireReferencia == 6) // Riego suelo 1
  {

    int WireValor = Wire.read();
    Serial.print(WireValor);
    Serial.println(" segundos");
    Regando1 = true;
    //Regar1();
    blink_Regar1.setInterval(WireValor * 1000000) ;
    blink_Regar1.reset();
    blink_Regar1.enable();
    Serial.print("Regando suelo 1");
    Wire.write(WireValor);
  }
  if (WireReferencia == 7) // Riego suelo 2
  {
    int WireValor = Wire.read();
    Regando2 = true;
    blink_Regar2.setInterval(WireValor * 1000000) ;
    blink_Regar2.reset();
    blink_Regar2.enable();
    Wire.write(WireValor);

  }
  if (WireReferencia == 8)
  {
    int WireValor = Wire.read();// Año
    Fecha[0] = WireValor;
  }
  if (WireReferencia == 9) {
    int WireValor = Wire.read(); // ;Mes
    Fecha[1] = WireValor;
  }
  if (WireReferencia == 10)  {
    int WireValor = Wire.read(); // ;Dia
    Fecha[2] = WireValor;
  }
  if (WireReferencia == 11) {
    int WireValor = Wire.read(); // ;Hora
    Fecha[3] = WireValor;
  }
  if (WireReferencia == 12) {
    int WireValor = Wire.read(); // ;Minuto
    Fecha[4] = WireValor;
  }
  if (WireReferencia == 13)  {
    int WireValor = Wire.read(); // Segundos
    Fecha[5] = WireValor;
  }

}

void requestEvent() {
  //Wire.write("hello "); // respond with message of 6 bytes
  // as expected by master


  // Si hay dos bytes disponibles
  if (ReferenciaWireGlobal == 1) // DTH11
  {
    if (ValorWireGlobal == 1) {
      Humedad1(); // Tempetatura
    }
    else if (ValorWireGlobal == 2) {
      Riego1(); // Humedad
    }
    else if (ValorWireGlobal == 3) {
      Percepreon1(); // apagar
    }
  }
  if (ReferenciaWireGlobal == 2) // BMP180
  {
    //Valor = Wire.read();
    if (ValorWireGlobal == 1) {
      Humedad1(); // Barometro
    }
    else if (ValorWireGlobal == 2) {
      Riego1(); // Termometro
    }
    else if (ValorWireGlobal == 3) {
      Percepreon1();
    }
  }
  if (ReferenciaWireGlobal == 3) //DS3231
  {
    //Valor = Wire.read();
    if (ValorWireGlobal == 1) {
      Humedad1(); // Hora
    }
    else if (ValorWireGlobal == 2) {
      Riego1(); // ;Minutos
    }
    else if (ValorWireGlobal == 3) {
      Percepreon1(); // Segundos
    }
  }
}


void setup () {
  delay(100);
  pinMode(PinS1, OUTPUT);
  pinMode(PinS2, OUTPUT);
  pinMode(PinS3, OUTPUT);
  pinMode(PinS8, INPUT);
  //  //inputString.reserve(200);
  //  bitWrite(ADCSRA, ADPS2, 1);
  //  bitWrite(ADCSRA, ADPS1, 0);
  //  bitWrite(ADCSRA, ADPS0, 1);
  //  //ADPS2 - ADPS1 - ADPS0 - Division Factor
  //  //0        - 0       - 0        ->2
  //  //0        - 0       - 1        ->2
  //  //0        - 1       - 0        ->4
  //  //0        - 1       - 1        ->8
  //  //1        - 0       - 0        ->16
  //  //1        - 0       - 1        ->32
  //  //1        - 1       - 0        ->64
  //  //1        - 1       - 1        ->128

  Serial.begin(57600);
  //Wire.begin();
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  //
  //  NeuralNetwork NN(layers, NumberOf(layers)); // Creating a NeuralNetwork with default learning-rates
  //  //Trains the NeuralNetwork for 8000 epochs = Training loops
  //  for (int i = 0; i < 8000; i++)
  //  {
  //    for (int j = 0; j < NumberOf(inputs); j++)
  //    {
  //      NN.FeedForward(inputs[j]); // Feeds-Forward the inputs to the first layer of the NN and Gets the output.
  //      NN.BackProp(expectedOutput[j]); // Tells to the NN if the output was right/the-expectedOutput and then, teaches it.
  //    }
  //  }
  //  //Goes through all inputs
  //  for (int i = 0; i < NumberOf(inputs); i++)
  //  {
  //    outputs = NN.FeedForward(inputs[i]); // Feeds-Forward the inputs[i] to the first layer of the NN and Gets the output
  //    Serial.println(outputs[0], 7); // prints the first 7 digits after the comma.
  //  }
  //  NN.print(); // prints the weights and biases of each layer

  prediccion();
  delay(1000);
  prediccion();
  EnviarDatos();


}

void loop () {
  blink_DatosEnviar.check();

  // blink_Predecir.check();
  blink_Regar1.check();
  blink_Regar2.check();
  //  blink_DatosEnviar.disable();
  //  blink_DatosEnviar.enable();
  //  blink_DatosEnviar.setInterval(40000) ;
  delay(50);

}
