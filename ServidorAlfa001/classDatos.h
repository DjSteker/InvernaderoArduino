

class classDatos {

  public:
    double HumedadAmbiente = 0;
    double TemperaturaAmbiente = 0 ;
    double PresionAmbiente = 0;
    double HumedadSuelo1 = 0 ;
    double HumedadSuelo2 = 0 ;
    float PuntoRocio = 0;
    float Altitud = 650;
    int Anio = 0 ;
    int Mes = 0 ;
    int Dia = 0 ;
    int Hora = 0 ;
    int Minuto = 0 ;
    int Segundo = 0 ;
    int Riego1Segundos = 0 ;
    int Riego2Segundos = 0 ;
    int HoraGruadado = -1;
    int DiaGruadado = 0;

    float PresionHoras[6];
    float PresionDias[6];
    float TemperaturaHoras[6];
    float TemperaturaDias[6];
    float HumedadDias[6];
    float PrediccionPresion;
    float PrediccionDias;
    String Texto[6];
    String ArchivoTexto = "";
  private:


};
