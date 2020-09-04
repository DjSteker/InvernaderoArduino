byte prediccionPresion(float presure[5]) {
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
