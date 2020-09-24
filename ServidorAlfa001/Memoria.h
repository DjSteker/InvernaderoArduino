


void Guardar_Hora(int Hora,  double HumedadAmbiente,  double TemperaturaAmbiente, double PresionAmbiente, double HumedadSuelo1, double HumedadSuelo2) ;
//
//void Guardar_Dia(int Anio, int Mes, int Dia, int Hora, int Minuto, int Segundo , double HumedadAmbiente,  double TemperaturaAmbiente, double PresionAmbiente, double HumedadSuelo1, double HumedadSuelo2) ;
void Guardar_Dia(int Anio, int Mes, int Dia, int Hora, int Minuto, int Segundo ) ;

String LeerArchivo() ;

String* LeerValores() ;

bool ExisteArchivo();

String LeerValoresHtml();

String LeerValoresRestauracion();

long ConvierteFechaEnNumero( int year, int mes, int dia);

void SetMemoriaDias(String Linea, int DiaIdice);

void SetMemoriaHoras(String Linea);
void SetMemoriaHoraParametros(String Registro, int HoraIndice);

//String ProcesarLineaRestauracion ( String Linea_var );
