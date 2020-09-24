

float ObtenerSensores(int Variable) {
	float valor = 0;
	return valor;
}
float prediccionPresion(float presure_Var[5]) {
	float presure[5];
	presure[0] = presure_Var[5] / 100;
	presure[1] = presure_Var[4] / 100;
	presure[2] = presure_Var[3] / 100;
	presure[3] = presure_Var[2] / 100;
	presure[4] = presure_Var[1] / 100;
	presure[5] = presure_Var[0] / 100;
	float a, b, c, d, m; //Variables de calculo

	a = 6 * ((1 * presure[0]) + (2 * presure[1]) + (3 * presure[2]) + (4 * presure[3]) + (5 * presure[4]) + (6 * presure[5]));
	b = (720) * (presure[0] + presure[1] + presure[2] + presure[3] + presure[4] + presure[5]);
	c = 546;
	d = 441;
	m = (a - b) / (c - d);
	//  if (m < 0) {
	//    return 6; //Si m menor que cero, BORRASCA
	//  } else {
	//    return 7; //Si m mayor que cero, ANTICICLON
	//  }
	return m;
}

float prediccionDias(float presure_Var[6], float temperature_Var[6], float moisture_Var[6]) {
	return 1;
}

float RedimensionarPresion(float presure) {
	//return (presure - 50000) / (150000 - 50000)
	return (presure - 50000) / (50000);
}
float RedimensionarTemperatura(float temture) {
	//return (temture - 100) / (100 - (-100))
	return (temture - 100) / (200);
}
float RedimensionarHumedad(float moisture) {
	//return (moisture - 100) / (100 - 0)
	return (moisture - 100) / (100);
}

float prediccionPTH(float presure_Var[5], float temperature_Var[5], float moisture_Var[5]) {
	float presure[6];
	float temperature[6];
	float moisture[6];
	presure[0] = RedimensionarPresion(presure_Var[0]);
	presure[1] = RedimensionarPresion(presure_Var[1]);
	presure[2] = RedimensionarPresion(presure_Var[2]);
	presure[3] = RedimensionarPresion(presure_Var[3]);
	presure[4] = RedimensionarPresion(presure_Var[4]);
	presure[5] = RedimensionarPresion(presure_Var[5]);

	temperature[0] = RedimensionarTemperatura(temperature_Var[0]);
	temperature[1] = RedimensionarTemperatura(temperature_Var[1]);
	temperature[2] = RedimensionarTemperatura(temperature_Var[2]);
	temperature[3] = RedimensionarTemperatura(temperature_Var[3]);
	temperature[4] = RedimensionarTemperatura(temperature_Var[4]);
	temperature[5] = RedimensionarTemperatura(temperature_Var[5]);


	moisture[0] = RedimensionarHumedad(moisture_Var[0]);
	moisture[1] = RedimensionarHumedad(moisture_Var[1]);
	moisture[2] = RedimensionarHumedad(moisture_Var[2]);
	moisture[3] = RedimensionarHumedad(moisture_Var[3]);
	moisture[4] = RedimensionarHumedad(moisture_Var[4]);
	moisture[5] = RedimensionarHumedad(moisture_Var[5]);

	float a1 = ((presure[0] - presure[1]) * -1) + (((moisture[0] - moisture[1]) / 4) + (temperature[0] - temperature[1]));
	float a2 = ((presure[1] - presure[2]) * -1) + (((moisture[1] - moisture[2]) / 4) + (temperature[1] - temperature[2]));
	float a3 = ((presure[2] - presure[3]) * -1) + (((moisture[2] - moisture[3]) / 4) + (temperature[2] - temperature[3]));
	float a4 = ((presure[3] - presure[4]) * -1) + (((moisture[3] - moisture[4]) / 4) + (temperature[3] - temperature[4]));
	float a5 = ((presure[4] - presure[5]) * -1) + (((moisture[4] - moisture[5]) / 4) + (temperature[4] - temperature[5]));




	float a, b, c, d, m; //Variables de calculo

	a = 5 * ((1 * a5) + (2 * a4) + (3 * a3) + (4 * a2) + (5 * a1));
	b = (600) * (a1 + a2 + a3 + a4 + a5);
	c = 546;
	d = 441;
	m = (a - b) / 87.5; //(a - b) / (c - d);
	//  if (m < 0) {
	//    return 6; //Si m menor que cero, BORRASCA
	//  } else {
	//    return 7; //Si m mayor que cero, ANTICICLON
	//  }
	return m;
}



float GetPuntoRocio(float HumedadRelativa, float Tempetatura) {
	return ((sqrt(sqrt(sqrt(HumedadRelativa / 100))) * (110 + Tempetatura)) - 110);
}


double MyNormalize(double v) {
	v = v - floor(v);
	if (v < 0)
	v = v + 1;
	return v;
}
float GetPhase(int nYear, int nMonth, int nDay) // calculate the current phase of the moon
{
	float phase;
	double AG, IP;
	long YY, MM, K1, K2, K3, JD;
	YY = nYear - floor((12 - nMonth) / 10);
	MM = nMonth + 9;
	if (MM >= 12)
	{
		MM = MM - 12;
	}
	K1 = floor(365.25 * (YY + 4712));
	K2 = floor(30.6 * MM + 0.5);
	K3 = floor(floor((YY / 100) + 49) * 0.75) - 38;
	JD = K1 + K2 + nDay + 59;
	if (JD > 2299160)
	{
		JD = JD - K3;
	}
	IP = MyNormalize((JD - 2451550.1) / 29.530588853);
	AG = IP * 29.53;
	phase = 0;
	if ((AG < 1.84566) && (phase == 0))
	{
		phase = 0; //new; 0% illuminated
	}
	if ((AG < 5.53699) && (phase == 0))
	{
		phase = .25; //Waxing crescent; 25% illuminated
	}
	if ((AG < 9.922831) && (phase == 0))
	{
		phase = .50; //First quarter; 50% illuminated
	}
	if ((AG < 12.91963) && (phase == 0))
	{
		phase = .75; //Waxing gibbous; 75% illuminated
	}
	if ((AG < 16.61096) && (phase == 0))
	{
		phase = 1; //Full; 100% illuminated
	}
	if ((AG < 20.30228) && (phase == 0))
	{
		phase = .75; //Waning gibbous; 75% illuminated
	}
	if ((AG < 23.99361) && (phase == 0))
	{
		phase = .50; //Last quarter; 50% illuminated
	}
	if ((AG < 27.68493) && (phase == 0))
	{
		phase = .25; //Waning crescent; 25% illuminated
	}
	if (phase == 0)
	{
		phase = 0; //default to new; 0% illuminated
	}
	return phase;
}
