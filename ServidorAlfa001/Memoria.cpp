


#include <SPI.h> //for the SD card module
#include <SD.h> // for the SD card

#include "classDatos.h"
extern classDatos ArchivoDatos;

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



void SetMemoriaDias(String Linea, int DiaIdice) {
  int PosicionALas7 = Linea.indexOf("Hora=7");

  String DiaPresionH7, DiaHumedadH7, DiaTemperaturaH7;
  int DiaPresionH7pos, DiaHumedadH7pos, DiaTemperaturaH7pos;

  if (PosicionALas7 != -1) {
    DiaHumedadH7pos =  Linea.indexOf("HumedadAmbi=", PosicionALas7 );
    //Serial.print(" DhSS"); Serial.print(DiaHumedadH7pos);
    DiaHumedadH7 =  Linea.substring(DiaHumedadH7pos + 12, Linea.indexOf(' ', DiaHumedadH7pos)); //.toDouble();
    //Serial.print(" Dh"); Serial.print(DiaHumedadH7);

    DiaTemperaturaH7pos = Linea.indexOf("TemperaAmbi=", DiaHumedadH7pos );
    //Serial.print(" DtSS"); Serial.print(DiaTemperaturaH7pos);
    DiaTemperaturaH7 = Linea.substring(DiaTemperaturaH7pos + 12, Linea.indexOf(' ', DiaTemperaturaH7pos)); //.toDouble();
    //Serial.print(" Dt"); Serial.print(DiaTemperaturaH7);

    DiaPresionH7pos =  Linea.indexOf("PresionAmbi=", DiaTemperaturaH7pos );
    //Serial.print(" DpSS"); Serial.print(DiaPresionH7pos);
    DiaPresionH7 =  Linea.substring(DiaPresionH7pos + 12, Linea.indexOf(' ', DiaPresionH7pos)); //.toDouble();
    //Serial.print(" Dp"); Serial.print(DiaPresionH7);

    ArchivoDatos.TemperaturaDias[DiaIdice] = DiaTemperaturaH7.toFloat();
    ArchivoDatos.PresionDias[DiaIdice] = DiaPresionH7.toFloat();
    ArchivoDatos.HumedadDias[DiaIdice] = DiaHumedadH7.toFloat();
  } else {
    Serial.print(" Error_0XX1");
    Serial.print(DiaIdice);
    Serial.print("---- ");
    Serial.print(Linea);
  }
}

void SetMemoriaHoraParametros(String Registro, int HoraIndice) {
  Serial.println("");
  Serial.print(" Registro"); Serial.println(Registro);
  int posicion1 = Registro.indexOf("PresionAmbi=");
  int posicion2 = Registro.indexOf(" ", posicion1);
  //String Texto;
  //"PresionAmbi"
  //"TemperaAmbi"
  //"HumedadAmbi"
  if (posicion1 > -1) {
    //    Texto += Registro.substring(posicion1, posicion2).toFloat();
    //    Texto += "\n";
    ArchivoDatos.PresionHoras[HoraIndice] = Registro.substring(posicion1 + 12, posicion2).toFloat();
    Serial.print("indice"); Serial.print(HoraIndice); Serial.print( ArchivoDatos.PresionHoras[HoraIndice]); Serial.println(Registro.substring(posicion1, posicion2));
  }
  posicion1 = Registro.indexOf("TemperaAmbi=");
  posicion2 = Registro.indexOf(" ", posicion1);
  if (posicion1 > -1) {
    //    Texto += Registro.substring(posicion1, posicion2).toFloat();
    //    Texto += "\n";
    ArchivoDatos.TemperaturaHoras[HoraIndice] = Registro.substring(posicion1 + 12, posicion2).toFloat();
    Serial.print(Registro.substring(posicion1 + 12, posicion2).toFloat()); Serial.println(Registro.substring(posicion1, posicion2));
  }
  posicion1 = Registro.indexOf("HumedadAmbi=");
  posicion2 = Registro.indexOf(" ", posicion1);
  if (posicion1 > -1) {
    //    Texto += Registro.substring(posicion1, posicion2).toFloat();
    //    Texto += "\n";
    Serial.println(Registro.substring(posicion1, posicion2));
  }



  // DiaHumedadH7pos =  Linea.indexOf("HumedadAmbi=", PosicionALas7 );

  //  ArchivoDatos.PresionHoras[HoraIndice] = Registro.substring(PosicionHora,  Linea.indexOf(' ', PosicionHora)).toFloat();
  //  ArchivoDatos.TemperaturaHoras[HoraIndice] = Linea.substring(PosicionHora,  Linea.indexOf(' ', PosicionHora)).toFloat();



  //String Datos1 = ProcesarLineaRestauracion("");

  //
  //  int posicion = 0;
  //  int posicion2 = Lineas[0].lastIndexOf('=', posicion);
  //  int posicion3 = Lineas[0].lastIndexOf(' ', posicion);
  //  int posicion4 = Lineas[0].lastIndexOf(')', posicion);
  //  Serial.print("posicion3"); Serial.print( posicion3); Serial.print(" posicion4"); Serial.print(posicion4);
  //  Serial.println(Lineas[0].substring(posicion3, posicion4));
  //  if (Lineas[0].substring(posicion3, posicion2) == "HumedadSue2") {
  //    Texto += Lineas[0].substring(posicion3, posicion4);
  //    Texto += "\n";
  //    Serial.println(Lineas[0].substring(posicion3, posicion4));
  //  }
  //  posicion = 1;
  //  posicion2 = Lineas[0].lastIndexOf('=', posicion);
  //  posicion4 = posicion3;
  //  posicion3 = Lineas[0].lastIndexOf(' ', posicion);
  //  if (Lineas[0].substring(posicion2, posicion3) == "HumedadSue1") {
  //    Texto += Lineas[0].substring(posicion3, posicion4);
  //    Texto += "\n";
  //    Serial.println(Lineas[0].substring(posicion3, posicion4));
  //  }
  //  posicion = 2;
  //  posicion2 = Lineas[0].lastIndexOf('=', posicion);
  //
  //  posicion3 = Lineas[0].lastIndexOf(' ', posicion);
  //  if (Lineas[0].substring(posicion2, posicion3) == "PresionAmbi") {
  //    Texto += Lineas[0].substring(posicion3, posicion4);
  //    Texto += "\n";
  //    Serial.println(Lineas[0].substring(posicion3, posicion4));
  //  }
  //  posicion = 3;
  //  posicion2 = Lineas[0].lastIndexOf('=', posicion);
  //  posicion4 = posicion3;
  //  posicion3 = Lineas[0].lastIndexOf(' ', posicion);
  //  if (Lineas[0].substring(posicion2, posicion3) == "TemperaAmbi") {
  //    Texto += Lineas[0].substring(posicion3, posicion4);
  //    Texto += "\n";
  //    Serial.println(Lineas[0].substring(posicion3, posicion4));
  //  }
  //  posicion = 4;
  //  posicion2 = Lineas[0].lastIndexOf('=', posicion);
  //  posicion4 = posicion3;
  //  posicion3 = Lineas[0].lastIndexOf(' ', posicion);
  //  if (Lineas[0].substring(posicion2, posicion3) == "HumedadAmbi") {
  //    Texto += Lineas[0].substring(posicion3, posicion4);
  //    Texto += "\n";
  //    Serial.println(Lineas[0].substring(posicion3, posicion4));
  //  }
  //  posicion = 5;
  //  posicion2 = Lineas[0].lastIndexOf('=', posicion);
  //  posicion4 = posicion3;
  //  posicion3 = Lineas[0].lastIndexOf(' ', posicion);
  //  if (Lineas[0].substring(posicion2, posicion3) == "Hora") {
  //    Texto += Lineas[0].substring(posicion3, posicion4);
  //    Texto += "\n";
  //    Serial.println(Lineas[0].substring(posicion3, posicion4));
  //  }
  //
  //  LineaPos = 1;
}


void SetMemoriaHoras(String Linea) {


  int Posicion = Linea.length() - 1;
  for (int indice = 0; indice < 24; indice++) {

    int PosicionUltima = Linea.lastIndexOf(")", Posicion);
    int PosicionInicio = Linea.lastIndexOf("(", Posicion) ;
    Serial.print(" PosicionUltima "); Serial.print(PosicionUltima); Serial.print(" PosicionInicio "); Serial.print(PosicionInicio);




    String TextoRegistro = Linea.substring(PosicionInicio,  PosicionUltima + 1);



    int PosicionHora = TextoRegistro.lastIndexOf("Hora=", Posicion) + 5; //Linea.indexOf("Hora=7");
    Serial.print(" h "); Serial.print(TextoRegistro.substring(PosicionHora,  TextoRegistro.indexOf(' ', PosicionHora)));
    int HoraTexto = TextoRegistro.substring(PosicionHora,  Linea.indexOf(' ', PosicionHora)).toInt();


    //Serial.print(" h "); Serial.print(HoraTexto); Serial.print(" _ "); Serial.println(TextoRegistro);
    if ((PosicionUltima != -1) && (PosicionInicio != -1)) {
      Serial.print(" hX"); Serial.print(HoraTexto); Serial.print("X "); Serial.print(ArchivoDatos.Hora); Serial.print("X ");

      if (ArchivoDatos.Hora == HoraTexto) {
        SetMemoriaHoraParametros(TextoRegistro, 0);
        ArchivoDatos.HoraGruadado = ArchivoDatos.Hora;
        Serial.print(" h_0 ");
      }
      else if ((ArchivoDatos.Hora - 1) == HoraTexto) {
        SetMemoriaHoraParametros(TextoRegistro, 1);
        Serial.print(" h_1 ");
      }
      else if ((ArchivoDatos.Hora - 2) == HoraTexto) {
        SetMemoriaHoraParametros(TextoRegistro, 2);
        Serial.print(" h_2 ");
      }
      else if ((ArchivoDatos.Hora - 3) == HoraTexto) {
        SetMemoriaHoraParametros(TextoRegistro, 3);
        Serial.print(" h_3 ");
      }
      else if ((ArchivoDatos.Hora - 4) == HoraTexto) {
        SetMemoriaHoraParametros(TextoRegistro, 4);
        Serial.print(" h_4 ");
      }
      else if ((ArchivoDatos.Hora - 5) == HoraTexto) {
        SetMemoriaHoraParametros(TextoRegistro, 5);
        Serial.print(" h_5 ");
        indice = 24;
      }
      else {
        Serial.print(" Error_0XX2");
        Serial.print(" ---- ");
      }
    } else {
      Serial.print(" Error_0XX3");
    }
    Posicion = PosicionInicio - 1;
  }
}


long ConvierteFechaEnNumero( int year, int mes, int dia) {
  //char  *Day[] = {"","Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
  //int DMes[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  //      unsigned long AAAA, MM, DD;
  //      unsigned long HH, mm, ss, DS;
  int tablaMes[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
  long diaNum;

  diaNum = (year - 2000) * 365 + (year - 2000) / 4 + tablaMes[mes - 1] + dia;
  if (((year - 2000) % 4 == 0) && (mes < 3)) // Es bisiesto y no hemos pasado 29/02
    diaNum--;

  return diaNum;
}


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
    myFile.print(" Hora="); myFile.print(Hora);
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

void Guardar_Dia(int Anio, int Mes, int Dia, int Hora, int Minuto, int Segundo ) {//, double HumedadAmbiente,  double TemperaturaAmbiente, double PresionAmbiente, double HumedadSuelo1, double HumedadSuelo2) {

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

    //    myFile.print("(");
    //    myFile.print(" Hora="); myFile.print(Hora);
    //    myFile.print(" HumedadAmbi="); myFile.print(HumedadAmbiente);
    //    myFile.print(" TemperaAmbi="); myFile.print(TemperaturaAmbiente);
    //    myFile.print(" PresionAmbi="); myFile.print(PresionAmbiente);
    //    myFile.print(" HumedadSue1="); myFile.print(HumedadSuelo1);
    //    myFile.print(" HumedadSue2="); myFile.print(HumedadSuelo2);
    //    myFile.print(")");
    Serial.println(" guardado ");
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
    int cuantaCaracteres = 0;
    bool bucleLectura = myFile.available();
    //int indice = myFile.size() ;
    //while (bucleLectura) {
    //myFile.seek(indice);
    //char caracter = myFile.read();
    //Texto = caracter + Texto;
    //Texto = myFile.read();
    //cuantaCaracteres++;
    //indice--;
    //if ((cuantaCaracteres > 2048) || (myFile.available() == false))
    //{bucleLectura = false; return Texto;}
    //Serial.print(caracter);

    //    if (myFile.available()) {
    //      for (int indiceChars; (indiceChars <  myFile.size()) && (indiceChars < 2048); indiceChars++) {
    //        char caracter = myFile.read();
    //        Texto += caracter;
    //      }
    //    }
    if (myFile.available()) {
      uint8_t i = 0;
      String caracterStr = "";
      int indice = myFile.size() - 1;
      myFile.seek(indice);
      while ( (myFile.peek() != '\n') && (i < 16384) && (indice > 0) )   // note how this also prevents the buffer from overflowing (18 max to leave space for '\0'!)
      {
        myFile.seek(indice);
        //buffer[i] = file.read();
        char caracter = myFile.peek();//myFile.read();
        caracterStr = caracter;
        Texto = caracterStr + Texto;
        i++;
        indice -= 1;
      }
      //buffer[i + 1] = '\0';
      Texto += '\0';
    }
    //    Serial.println(Texto);
    //    Serial.println(" - ");
    myFile.close(); //cerramos el archivo
    digitalWrite(LED_BUILTIN, HIGH);
    //Serial.println(Texto);
  } else {
    Serial.println("Error al abrir el archivo");
    digitalWrite(LED_BUILTIN, HIGH);
  }
  //digitalWrite(LED_BUILTIN, HIGH);
  return Texto;
}

String LeerValoresRestauracion() {
  String TextoSalida = "";
  String Texto = "";
  String Lineas[6];
  int LineaPos = 0;
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
    ArchivoDatos.ArchivoTexto = "";
    int indice = myFile.size() - 1 ;
    //myFile.seek(indice);

    char caracter;


    if (myFile.available()) {
      uint8_t i = 0;
      String caracterStr = "";
      int indice = myFile.size() - 1;
      myFile.seek(indice);
      LineaPos = 0;
      while ((i < 16384) && (indice > -1) && (LineaPos < 6) )   // note how this also prevents the buffer from overflowing (18 max to leave space for '\0'!)
      {
        myFile.seek(indice);
        //buffer[i] = file.read();
        char caracter = myFile.peek();//myFile.read();
        caracterStr = caracter;
        TextoSalida = caracterStr + TextoSalida;
        if ((caracter == '\n') && (sizeof(Texto) > 0)) {
          Lineas[LineaPos] = Texto;
          Texto = "";
          LineaPos++;
        } else {
          caracterStr = caracter;
          Texto = caracterStr + Texto;
        }

        i++;
        indice --;

      }
      //buffer[i + 1] = '\0';
      Texto += '\0';
    }


  }
SalidaSD:
  myFile.close(); //cerramos el archivo
  digitalWrite(LED_BUILTIN, HIGH);


  Serial.println("Text;");
  Serial.println(Lineas[0]);



  for (int indiceDias = 0; indiceDias < 6; indiceDias++ )
  {
    int pos_DiaOpen = Lineas[indiceDias].indexOf('{');
    int pos_DiaClose = Lineas[indiceDias].indexOf('}');
    int pos_DiaBarra = Lineas[indiceDias].indexOf('/');
    int pos_Barra2 = 0;
    String DiaPresionH7, DiaHumedadH7, DiaTemperaturaH7;
    int DiaPresionH7pos, DiaHumedadH7pos, DiaTemperaturaH7pos;
    int Anio_m, Mes_m, Dia_m, Hora_m;
    //    Serial.println(Lineas[indiceDias].substring(pos_DiaOpen, pos_DiaClose + 1));
    //    Serial.println(Lineas[indiceDias].substring(pos_DiaOpen + 1, pos_DiaBarra).toInt());
    if ((pos_DiaOpen > -1) && (pos_DiaClose > -1) && (pos_DiaBarra > -1)) {
      Dia_m = Lineas[indiceDias].substring(pos_DiaOpen + 1, pos_DiaBarra).toInt();
      //pos_DiaBarra = Lineas[indiceDias].indexOf('/', pos_DiaBarra + 1);
      pos_Barra2 = Lineas[indiceDias].indexOf('/', pos_DiaBarra + 1);
      Mes_m = Lineas[indiceDias].substring(pos_DiaBarra + 1, pos_Barra2).toInt();
      pos_DiaBarra = Lineas[indiceDias].indexOf(' - ', pos_DiaBarra);
      Anio_m = Lineas[indiceDias].substring(pos_Barra2 + 1, pos_DiaBarra).toInt();
      Hora_m = Lineas[indiceDias].substring(pos_DiaBarra + 1, Lineas[indiceDias].indexOf(':')).toInt();
      //      Serial.println("--------   ");
      //      Serial.print(Dia_m); Serial.print("/"); Serial.print(Mes_m); Serial.print("/"); Serial.print(Anio_m); Serial.print("  -  "); Serial.print(Hora_m);
      //      Serial.println("   --------");


      //{22/9/2020 - 7:0.8}( Hora=7 HumedadAmbi=17.00 TemperaAmbi=24.05 PresionAmbi=93763.00 HumedadSue1=-1.00 HumedadSue2=-1.00)
      //D22 DhSS130 DhumedadAmbi=17.00 DtSS148 DtemperaAmbi=24.00 DpSS166 DpresionAmbi=93789.00
      Serial.print("   D"); Serial.print(Dia_m);


      long DiaNumeroLeectura = ConvierteFechaEnNumero(Anio_m, Mes_m, Dia_m);
      long DiaNumeroActual = ConvierteFechaEnNumero(ArchivoDatos.Anio, ArchivoDatos.Mes, ArchivoDatos.Dia);


      Serial.print(" DiaNumeroActual"); Serial.print(DiaNumeroActual);
      Serial.print(" DiaNumeroLeectura"); Serial.print(DiaNumeroLeectura);

      if (DiaNumeroActual == DiaNumeroLeectura) {
        SetMemoriaDias(Lineas[indiceDias], 0);
        SetMemoriaHoras(Lineas[indiceDias]);
        ArchivoDatos.DiaGruadado = DiaNumeroActual;
      } else if ((DiaNumeroActual - 1) == DiaNumeroLeectura) {
        SetMemoriaDias(Lineas[indiceDias], 1);
      } else if ((DiaNumeroActual - 2) == DiaNumeroLeectura) {
        SetMemoriaDias(Lineas[indiceDias], 2);
      } else if ((DiaNumeroActual - 3) == DiaNumeroLeectura) {
        SetMemoriaDias(Lineas[indiceDias], 3);
      } else if ((DiaNumeroActual - 4) == DiaNumeroLeectura) {
        SetMemoriaDias(Lineas[indiceDias], 4);
      } else if ((DiaNumeroActual - 5) == DiaNumeroLeectura) {
        SetMemoriaDias(Lineas[indiceDias], 5);
      }

      //      int PosicionALas7 = Lineas[indiceDias].indexOf("Hora=7");
      //
      //      DiaHumedadH7pos =  Lineas[indiceDias].indexOf("HumedadAmbi=", PosicionALas7 );
      //      Serial.print(" DhSS"); Serial.print(DiaHumedadH7pos);
      //      DiaHumedadH7 =  Lineas[indiceDias].substring(DiaHumedadH7pos + 12, Lineas[indiceDias].indexOf(' ', DiaHumedadH7pos)); //.toDouble();
      //      Serial.print(" Dh"); Serial.print(DiaHumedadH7.toDouble());
      //
      //      DiaTemperaturaH7pos = Lineas[indiceDias].indexOf("TemperaAmbi=", DiaHumedadH7pos );
      //      Serial.print(" DtSS"); Serial.print(DiaTemperaturaH7pos);
      //      DiaTemperaturaH7 = Lineas[indiceDias].substring(DiaTemperaturaH7pos + 12, Lineas[indiceDias].indexOf(' ', DiaTemperaturaH7pos)); //.toDouble();
      //      Serial.print(" Dt"); Serial.print(DiaTemperaturaH7.toDouble());
      //
      //      DiaPresionH7pos =  Lineas[indiceDias].indexOf("PresionAmbi=", DiaTemperaturaH7pos );
      //      Serial.print(" DpSS"); Serial.print(DiaPresionH7pos);
      //      DiaPresionH7 =  Lineas[indiceDias].substring(DiaPresionH7pos + 12, Lineas[indiceDias].indexOf(' ', DiaPresionH7pos)); //.toDouble();
      //      Serial.print(" Dp"); Serial.print(DiaPresionH7.toDouble());



    }
  }
  Serial.println("---");

  //String Datos1 = ProcesarLineaRestauracion("");

  //
  //  int posicion = 0;
  //  int posicion2 = Lineas[0].lastIndexOf('=', posicion);
  //  int posicion3 = Lineas[0].lastIndexOf(' ', posicion);
  //  int posicion4 = Lineas[0].lastIndexOf(')', posicion);
  //  Serial.print("posicion3"); Serial.print( posicion3); Serial.print(" posicion4"); Serial.print(posicion4);
  //  Serial.println(Lineas[0].substring(posicion3, posicion4));
  //  if (Lineas[0].substring(posicion3, posicion2) == "HumedadSue2") {
  //    Texto += Lineas[0].substring(posicion3, posicion4);
  //    Texto += "\n";
  //    Serial.println(Lineas[0].substring(posicion3, posicion4));
  //  }
  //  posicion = 1;
  //  posicion2 = Lineas[0].lastIndexOf('=', posicion);
  //  posicion4 = posicion3;
  //  posicion3 = Lineas[0].lastIndexOf(' ', posicion);
  //  if (Lineas[0].substring(posicion2, posicion3) == "HumedadSue1") {
  //    Texto += Lineas[0].substring(posicion3, posicion4);
  //    Texto += "\n";
  //    Serial.println(Lineas[0].substring(posicion3, posicion4));
  //  }
  //  posicion = 2;
  //  posicion2 = Lineas[0].lastIndexOf('=', posicion);
  //
  //  posicion3 = Lineas[0].lastIndexOf(' ', posicion);
  //  if (Lineas[0].substring(posicion2, posicion3) == "PresionAmbi") {
  //    Texto += Lineas[0].substring(posicion3, posicion4);
  //    Texto += "\n";
  //    Serial.println(Lineas[0].substring(posicion3, posicion4));
  //  }
  //  posicion = 3;
  //  posicion2 = Lineas[0].lastIndexOf('=', posicion);
  //  posicion4 = posicion3;
  //  posicion3 = Lineas[0].lastIndexOf(' ', posicion);
  //  if (Lineas[0].substring(posicion2, posicion3) == "TemperaAmbi") {
  //    Texto += Lineas[0].substring(posicion3, posicion4);
  //    Texto += "\n";
  //    Serial.println(Lineas[0].substring(posicion3, posicion4));
  //  }
  //  posicion = 4;
  //  posicion2 = Lineas[0].lastIndexOf('=', posicion);
  //  posicion4 = posicion3;
  //  posicion3 = Lineas[0].lastIndexOf(' ', posicion);
  //  if (Lineas[0].substring(posicion2, posicion3) == "HumedadAmbi") {
  //    Texto += Lineas[0].substring(posicion3, posicion4);
  //    Texto += "\n";
  //    Serial.println(Lineas[0].substring(posicion3, posicion4));
  //  }
  //  posicion = 5;
  //  posicion2 = Lineas[0].lastIndexOf('=', posicion);
  //  posicion4 = posicion3;
  //  posicion3 = Lineas[0].lastIndexOf(' ', posicion);
  //  if (Lineas[0].substring(posicion2, posicion3) == "Hora") {
  //    Texto += Lineas[0].substring(posicion3, posicion4);
  //    Texto += "\n";
  //    Serial.println(Lineas[0].substring(posicion3, posicion4));
  //  }
  //
  //  LineaPos = 1;



  return TextoSalida;
}





//
//void ProcesarLineaRestauracion(String Linea_var) {
//
//String Texto;
//int posicion = 0;
//int posicion2 = Linea_var.lastIndexOf('=', posicion);
//int posicion3 = Linea_var.lastIndexOf(' ', posicion);
//int posicion4 = Linea_var.lastIndexOf(')', posicion);
//Serial.print("posicion3"); Serial.print( posicion3); Serial.print(" posicion4"); Serial.print(posicion4);
//Serial.println(Linea_var.substring(posicion3, posicion4));
//if (Linea_var.substring(posicion3, posicion2) == "HumedadSue2") {
//Texto += Linea_var.substring(posicion3, posicion4);
//Texto += "\n";
//Serial.println(Linea_var.substring(posicion3, posicion4));
//}
//posicion = 1;
//posicion2 = Linea_var.lastIndexOf('=', posicion);
//posicion4 = posicion3;
//posicion3 = Linea_var.lastIndexOf(' ', posicion);
//if (Linea_var.substring(posicion2, posicion3) == "HumedadSue1") {
//Texto += Linea_var.substring(posicion3, posicion4);
//Texto += "\n";
//Serial.println(Linea_var.substring(posicion3, posicion4));
//}
//posicion = 2;
//posicion2 = Linea_var.lastIndexOf('=', posicion);
//
//posicion3 = Linea_var.lastIndexOf(' ', posicion);
//if (Linea_var.substring(posicion2, posicion3) == "PresionAmbi") {
//Texto += Linea_var.substring(posicion3, posicion4);
//Texto += "\n";
//Serial.println(Linea_var.substring(posicion3, posicion4));
//}
//posicion = 3;
//posicion2 = Linea_var.lastIndexOf('=', posicion);
//posicion4 = posicion3;
//posicion3 = Linea_var.lastIndexOf(' ', posicion);
//if (Linea_var.substring(posicion2, posicion3) == "TemperaAmbi") {
//Texto += Linea_var.substring(posicion3, posicion4);
//Texto += "\n";
//Serial.println(Linea_var.substring(posicion3, posicion4));
//}
//posicion = 4;
//posicion2 = Linea_var.lastIndexOf('=', posicion);
//posicion4 = posicion3;
//posicion3 = Linea_var.lastIndexOf(' ', posicion);
//if (Linea_var.substring(posicion2, posicion3) == "HumedadAmbi") {
//Texto += Linea_var.substring(posicion3, posicion4);
//Texto += "\n";
//Serial.println(Linea_var.substring(posicion3, posicion4));
//}
//posicion = 5;
//posicion2 = Linea_var.lastIndexOf('=', posicion);
//posicion4 = posicion3;
//posicion3 = Linea_var.lastIndexOf(' ', posicion);
//if (Linea_var.substring(posicion2, posicion3) == "Hora") {
//Texto += Linea_var.substring(posicion3, posicion4);
//Texto += "\n";
//Serial.println(Linea_var.substring(posicion3, posicion4));
//}
//
//return Texto;
//}

String LeerValoresHtml() {
  String Texto = "";
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
    ArchivoDatos.ArchivoTexto = "";
    int indice = myFile.size() - 1;
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

    for (LineaPos; LineaPos < sizeof(Lineas[LineaPos]); LineaPos++) {

      int Bloque = 0;

      int posicion = 0;
      int posicion_Igual = Lineas[LineaPos].lastIndexOf('=', posicion);
      int posicion_Spara1 = Lineas[LineaPos].lastIndexOf(' ', posicion);
      int posicion_Spara2 = Lineas[LineaPos].lastIndexOf(')', posicion);

      if (Lineas[LineaPos].substring(posicion_Spara1, posicion_Igual) == "HumedadSue2") {
        Texto += Lineas[LineaPos].substring(posicion_Igual, posicion_Spara2);
      }
      posicion = 1;
      posicion_Igual = Lineas[LineaPos].lastIndexOf('=', posicion);
      posicion_Spara2 = posicion_Spara1;
      posicion_Spara1 = Lineas[LineaPos].lastIndexOf(' ', posicion);
      if (Lineas[LineaPos].substring(posicion_Igual, posicion_Spara1) == "HumedadSue1") {
        Texto += Lineas[LineaPos].substring(posicion_Igual, posicion_Spara2);
      }
      posicion = 2;
      posicion_Igual = Lineas[LineaPos].lastIndexOf('=', posicion);
      posicion_Spara2 = posicion_Spara1;
      posicion_Spara1 = Lineas[LineaPos].lastIndexOf(' ', posicion);
      if (Lineas[LineaPos].substring(posicion_Igual, posicion_Spara1) == "PresionAmbi") {
        Texto += Lineas[LineaPos].substring(posicion_Igual, posicion_Spara2);
      }
      posicion = 3;
      posicion_Igual = Lineas[LineaPos].lastIndexOf('=', posicion);
      posicion_Spara2 = posicion_Spara1;
      posicion_Spara1 = Lineas[LineaPos].lastIndexOf(' ', posicion);
      if (Lineas[LineaPos].substring(posicion_Igual, posicion_Spara1) == "TemperaAmbi") {
        Texto += Lineas[LineaPos].substring(posicion_Igual, posicion_Spara2);
      }
      posicion = 4;
      posicion_Igual = Lineas[LineaPos].lastIndexOf('=', posicion);
      posicion_Spara2 = posicion_Spara1;
      posicion_Spara1 = Lineas[LineaPos].lastIndexOf(' ', posicion);
      if (Lineas[LineaPos].substring(posicion_Igual, posicion_Spara1) == "HumedadAmbi") {
        Texto += Lineas[LineaPos].substring(posicion_Igual, posicion_Spara2);
      }
      posicion = 5;
      posicion_Igual = Lineas[LineaPos].lastIndexOf('=', posicion);
      posicion_Spara2 = posicion_Spara1;
      posicion_Spara1 = Lineas[LineaPos].lastIndexOf(' ', posicion);
      if (Lineas[LineaPos].substring(posicion_Igual, posicion_Spara1) == "Hora") {
        Texto += Lineas[LineaPos].substring(posicion_Igual, posicion_Spara2);
      }


    }
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
    //myFile.seek(myFile.size() - 1);
    if (myFile.available()) {
      for (int i_caracteres = 0; i_caracteres < (myFile.size() - 1); i_caracteres++)
      {
        char caracter = myFile.read();
        if (caracter == 10) //ASCII de nueva de línea
        {
          indice++;
          // break;
        } else {
          Texto[indice] += caracter;
        }
      }
      //      if (caracter == 123) { //{
      //      }
      //      if (caracter == 125) { // }
      //
      //      }
      //      if (caracter == 40) { // (
      //
      //      }
      //      if (caracter == 41) { // )
      //
      //      }
      //      if (caracter == 44) { // ,
      //
      //      }
      //      if (caracter == 61) { // =
      //
      //      }
      //0  null
      //40  (
      //41  )
      //42  *
      //43  +
      //44  ,
      //45  -


    }
    myFile.close(); //cerramos el archivo
    digitalWrite(LED_BUILTIN, HIGH);
    //Serial.println(Texto);
  } else {
    Serial.println("Error al abrir el archivo");
    digitalWrite(LED_BUILTIN, LOW);
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
