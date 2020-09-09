


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
    //    myFile.print(" () Hora="); myFile.print(Hora);
    //    myFile.print(" Humedad="); myFile.print(HumedadAmbiente);
    //    myFile.print(" TemperaturaAmbiente="); myFile.print(TemperaturaAmbiente);
    //    myFile.print(" PresionAmbiente="); myFile.print(PresionAmbiente);
    //    myFile.print(" HumedadSuelo1="); myFile.print(HumedadSuelo1);
    //    myFile.print(" HumedadSuelo2="); myFile.print(HumedadSuelo2);
    myFile.print("(");
    myFile.print("Hora="); myFile.print(Hora);
    myFile.print(" HumedadAmbi="); myFile.print(HumedadAmbiente);
    myFile.print(" TemperaAmbi="); myFile.print(TemperaturaAmbiente);
    myFile.print(" PresionAmbi="); myFile.print(PresionAmbiente);
    myFile.print(" HumedadSue1="); myFile.print(HumedadSuelo1);
    myFile.print(" HumedadSue2="); myFile.print(HumedadSuelo2);
    myFile.print(")");
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
    myFile.print(" - "); myFile.print(Hora); myFile.print(":"); myFile.print(Minuto); myFile.print(";"); myFile.print(Segundo);
    myFile.print("}");

    myFile.print("(");
    myFile.print("Hora="); myFile.print(Hora);
    myFile.print(" HumedadAmbi="); myFile.print(HumedadAmbiente);
    myFile.print(" TemperaAmbi="); myFile.print(TemperaturaAmbiente);
    myFile.print(" PresionAmbi="); myFile.print(PresionAmbiente);
    myFile.print(" HumedadSue1="); myFile.print(HumedadSuelo1);
    myFile.print(" HumedadSue2="); myFile.print(HumedadSuelo2);
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
      Texto += myFile.read();
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

String* LeerValoresRestauracion() {
  String Texto[] = "";
  //  file.seek(pos) //os ubicamos en una posición específica en el archivo. Pos debe ser un número entre 0 y el tamaño en bytes del archivo
  //  file.position()  // Retorna la posición actual en donde se leerá o escribirá el siguiente byte.
  //  file.size() //Retorna el tamaño en bytes del archivo

  digitalWrite(LED_BUILTIN, LOW);
  File myFile;
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    digitalWrite(LED_BUILTIN, HIGH);
    return Texto;
  }
  myFile = SD.open("DATA.txt");//abrimos  el archivo
  if (myFile) {
    //Serial.println("DATA.txt:");
    int indice = myFile.size() ;
    //myFile.seek(indice);
    int LineaPos = 0;
    char caracter;
    String Lineas[6];
    String FragmentoTemporal = "";
    while (myFile.available()) {
      myFile.seek(indice);
      caracter = myFile.read();
      if (caracter == 10) //ASCII de nueva de línea
      {
        Lineas[LineaPos] = FragmentoTemporal;
        LineaPos++;
        if (LineaPos > 6) {
          goto SalidaSD;
        }
        FragmentoTemporal += caracter;
        // break;
      }
      indice--;
    }
SalidaSD:
    myFile.close(); //cerramos el archivo
    digitalWrite(LED_BUILTIN, HIGH);

    LineaPos = 0;
    FragmentoTemporal = "";
    bool TipoValor = true;
    String ValorTemporal = "";
    int posicion1 = Lineas[6].indexOf('=');
    int posicion2 = Lineas[6].indexOf('=', 1);
    int posicionUltima = Lineas[6].lastIndexOf('=', 1);
    if (caracter == 125) { // }
      int a = 0;
    }
    if (caracter == 123) { //{
      int a = 0;
    }

    if (caracter == 41) { // )
      TipoValor = true;
    }
    if (caracter == 61) { // =
      ValorTemporal = FragmentoTemporal;
      FragmentoTemporal = "";
      TipoValor = false;
    }

    if (TipoValor == true) {
      ValorTemporal += caracter;
    }
    if (TipoValor == false) {
      FragmentoTemporal += caracter;
    }

    if (FragmentoTemporal == "Hora" ) {
      String a = ValorTemporal;
      //    myFile.print("{");
      //    myFile.print(Dia); myFile.print("/"); myFile.print(Mes); myFile.print("/"); myFile.print(Anio);
      //    myFile.print(" - "); myFile.print(Hora); myFile.print(":"); myFile.print(Minuto); myFile.print(";"); myFile.print(Segundo);
      //    myFile.print("}");
    }
    if (FragmentoTemporal == "HumedadAmbi" ) {
      TipoValor = true;
      float a = ValorTemporal.toFloat();
    }
    if ( FragmentoTemporal == "TemperaAmbi" ) {
      TipoValor = true;
      float a = ValorTemporal.toFloat();
    }
    if (FragmentoTemporal == "PresionAmbi" ) {
      TipoValor = true;
      float a = ValorTemporal.toFloat();
    }
    if (FragmentoTemporal == "HumedadSue1" ) {
      TipoValor = true;
      int a = ValorTemporal.toInt();
    }
    if (FragmentoTemporal == "HumedadSue2" ) {
      TipoValor = true;
      int a = ValorTemporal.toInt();
    }

    if (caracter == 40) { // (
      int a = 0;
    }
    if (caracter == 61) { // =
      int a = 0;
    }

    if (caracter == 44) { // ,
      int a = 0;
    }
    //    if (caracter == 61) { // =
    //      break;
    //    }

    FragmentoTemporal += caracter;
    Texto[indice] += caracter;




    //0  null
    //40  (
    //41  )
    //42  *
    //43  +
    //44  ,
    //45  -




    //Serial.println(Texto);
  } else {
    Serial.println("Error al abrir el archivo");
    digitalWrite(LED_BUILTIN, HIGH);
  }


  return Texto;
}



String* LeerValores() {
  String Texto[] = "";
  //  file.seek(pos) //os ubicamos en una posición específica en el archivo. Pos debe ser un número entre 0 y el tamaño en bytes del archivo
  //  file.position()  // Retorna la posición actual en donde se leerá o escribirá el siguiente byte.
  //  file.size() //Retorna el tamaño en bytes del archivo

  digitalWrite(LED_BUILTIN, LOW);
  File myFile;
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    digitalWrite(LED_BUILTIN, HIGH);
    return Texto;
  }
  myFile = SD.open("DATA.txt");//abrimos  el archivo
  if (myFile) {
    //Serial.println("DATA.txt:");
    int indice = 0 ;
    myFile.seek(myFile.size());
    while (myFile.available()) {
      char caracter = myFile.read();
      if (caracter == 10) //ASCII de nueva de línea
      {
        indice++;
        // break;
      }
      if (caracter == 123) { //{
      }
      if (caracter == 125) { // }

      }
      if (caracter == 40) { // (

      }
      if (caracter == 41) { // )

      }
      if (caracter == 44) { // ,

      }
      if (caracter == 61) { // =

      }
      //0  null
      //40  (
      //41  )
      //42  *
      //43  +
      //44  ,
      //45  -
      Texto[indice] += caracter;

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
