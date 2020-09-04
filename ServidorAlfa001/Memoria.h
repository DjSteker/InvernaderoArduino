
#include <SPI.h> //for the SD card module
#include <SD.h> // for the SD card



//// Iniciar la SD
//SD.begin(cspin);
//
//// Comprobar si existe un fichero (devuelve true si existe, falso en caso contrario)
//SD.exists(filename);
//
//// Borrar un fichero
//SD.remove(filename);
//
//// Abrir un fichero
//// Mode: FILE_READ para sólo lectura
////        FILE_WRITE para lectura y escritura
//SD.open(filepath, mode);
//
//// Crear un directorio
//SD.mkdir(directory);
//
//// Eliminar un directorio
//SD.rmdir(dirname);
//
//// Obtener el tamaño de un fichero
//file.size()
//
//// Comprobar si quedan bytes por leer
//file.available()
//
//// Leer un byte del fichero
//file.read()
//
//// Escribir un byte en el fichero
//file.write(data)
//
//// Escribir una variable en un fichero (en forma similar a Serial.Print)
//file.print(data)
//
//// Obtener el punto de lectura/escritura actual
//file.position()
//
//// Mover el punto de lectura/escritura actual
//// Pos: Debe estar entre 0 y file.size()
//file.seek(pos)
//
//// Cerrar el fichero
//file.close()

// change this to match your SD shield or module;
// Arduino Ethernet shield and modules: pin 4
// Data loggin SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
const int chipSelect = SS;

// Create a file to store the data
//File myFile;

//void Guardar_1() {
//  digitalWrite(LED_BUILTIN, HIGH);
//  // setup for the SD card
//  Serial.print("Initializing SD card...");
//
//  if (!SD.begin(chipSelect)) {
//    Serial.println("initialization failed!");
//    digitalWrite(LED_BUILTIN, LOW);
//    return;
//  }
//  Serial.println("initialization done.");
//
//  //open file
//  myFile = SD.open("DATA.txt", FILE_WRITE);
//
//  // if the file opened ok, write to it:
//  if (myFile) {
//    Serial.println("File opened ok");
//    // print the headings for our data
//    myFile.println("Date,Time,Temperature ºC");
//  }
//  myFile.close();
//  digitalWrite(LED_BUILTIN, LOW);
//}

void Guardar_Hora(int Hora,  double HumedadAmbiente,  double TemperaturaAmbiente, double PresionAmbiente, double HumedadSuelo1, double HumedadSuelo2) {

  // setup for the SD card
  Serial.print("Initializing SD card...");
  digitalWrite(LED_BUILTIN, LOW);
  File myFile;
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    digitalWrite(LED_BUILTIN, HIGH);
    return;
  }
  Serial.println("initialization done.");

  //open file
  myFile = SD.open("DATA.txt", FILE_WRITE);

  // if the file opened ok, write to it:
  if (myFile) {
    Serial.println("File opened ok");
    // print the headings for our data
    myFile.print(" () Hora="); myFile.print(Hora);
    myFile.print(" Humedad="); myFile.print(HumedadAmbiente);
    myFile.print(" TemperaturaAmbiente="); myFile.print(TemperaturaAmbiente);
    myFile.print(" PresionAmbiente="); myFile.print(PresionAmbiente);
    myFile.print(" HumedadSuelo1="); myFile.print(HumedadSuelo1);
    myFile.print(" HumedadSuelo2="); myFile.print(HumedadSuelo2);
  }
  myFile.close();
  digitalWrite(LED_BUILTIN, HIGH);
}

void Guardar_Dia(int Anio, int Mes, int Dia, int Hora, int Minuto, int Segundo , double HumedadAmbiente,  double TemperaturaAmbiente, double PresionAmbiente, double HumedadSuelo1, double HumedadSuelo2) {

  // setup for the SD card
  Serial.print("Initializing SD card...");
  digitalWrite(LED_BUILTIN, LOW);
  File myFile;
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    digitalWrite(LED_BUILTIN, HIGH);
    return;
  }
  Serial.println("initialization done.");

  //open file
  myFile = SD.open("DATA.txt", FILE_WRITE);

  // if the file opened ok, write to it:
  if (myFile) {
    Serial.println("File opened ok");
    // print the headings for our data
    myFile.println("");


    myFile.print("{");
    myFile.print(Dia); myFile.print("/"); myFile.print(Mes); myFile.print("/"); myFile.print(Anio);
    myFile.print(" - "); myFile.print(Hora); myFile.print(":"); myFile.print(Minuto); myFile.print("."); myFile.print(Segundo);
    myFile.print("}");

    myFile.print("(");
    myFile.print("Hora="); myFile.print(Hora);
    myFile.print(" Humedad="); myFile.print(HumedadAmbiente);
    myFile.print(" TemperaAmbiente="); myFile.print(TemperaturaAmbiente);
    myFile.print(" PresionAmbiente="); myFile.print(PresionAmbiente);
    myFile.print(" HumedadSuelo1="); myFile.print(HumedadSuelo1);
    myFile.print(" HumedadSuelo2="); myFile.print(HumedadSuelo2);
    myFile.print(")");
  }
  myFile.close();
  digitalWrite(LED_BUILTIN, HIGH);
}

String LeerArchivo() {
  String Texto = "";
  digitalWrite(LED_BUILTIN, LOW);
  File myFile;
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    digitalWrite(LED_BUILTIN, HIGH);
    return "";
  }
  myFile = SD.open("DATA.txt");//abrimos  el archivo
  if (myFile) {
    //Serial.println("DATA.txt:");
    while (myFile.available()) {
      //Texto = myFile.read();

    }
    myFile.close(); //cerramos el archivo
    digitalWrite(LED_BUILTIN, HIGH);
    //Serial.println(Texto);
  } else {
    Serial.println("Error al abrir el archivo");
    digitalWrite(LED_BUILTIN, HIGH);
  }
  return Texto;
}

String LeerValores() {
  String Texto = "";
  digitalWrite(LED_BUILTIN, LOW);
  File myFile;
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    digitalWrite(LED_BUILTIN, HIGH);
    return "";
  }
  myFile = SD.open("DATA.txt");//abrimos  el archivo
  if (myFile) {
    //Serial.println("DATA.txt:");
    while (myFile.available()) {
      //Texto = myFile.read();

    }
    myFile.close(); //cerramos el archivo
    digitalWrite(LED_BUILTIN, HIGH);
    //Serial.println(Texto);
  } else {
    Serial.println("Error al abrir el archivo");
    digitalWrite(LED_BUILTIN, HIGH);
  }
  return Texto;
}


bool ExisteArchivo() {
  digitalWrite(LED_BUILTIN, LOW);
  File myFile;
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    digitalWrite(LED_BUILTIN, HIGH);
    return false;
  }
  myFile = SD.open("DATA.txt");//abrimos  el archivo
  if (myFile) {
    myFile.close(); //cerramos el archivo
    digitalWrite(LED_BUILTIN, HIGH);
    return true;
  } else {
    myFile.close(); //cerramos el archivo
    digitalWrite(LED_BUILTIN, HIGH);
    return false;
  }
}
