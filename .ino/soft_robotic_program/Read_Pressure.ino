void read_pressure(){

  ADS0.setGain(0);
  ADS1.setGain(0);
  float dPressOut0 = ADS0.readADC(0);
  float dPressOut1 = ADS0.readADC(1);
  float dPressOut2 = ADS0.readADC(2);

  float dPressOut3 = ADS1.readADC(0);
  float dPressOut4 = ADS1.readADC(1);
  float dPressOutRef = ADS1.readADC(2);

  float Vs = 5.09; // Input Voltage

  float f1 = ADS0.toVoltage(1);
  float f4 = ADS1.toVoltage(1);

  float vPressOut0 = dPressOut0 * f1;
  float vPressOut1 = dPressOut1 * f1;
  float vPressOut2 = dPressOut2 * f1;
  float vPressOut3 = dPressOut3 * f4;
  float vPressOut4 = dPressOut4 * f4;
  float vPressRef = dPressOutRef * f4;

  PressureRef = (vPressRef/Vs - 0.04)/0.0012858; // Pressure refrence
  Pressure[0] = ((vPressOut0/Vs - 0.04)/0.0012858 - PressureRef); // pinky
  Pressure[1] = ((vPressOut1/Vs - 0.04)/0.0012858 - PressureRef); // ring
  Pressure[2] = (vPressOut2/Vs - 0.04)/0.0012858 - PressureRef - 0.92; // middle
  Pressure[3] = (vPressOut3/Vs - 0.04)/0.0012858 - PressureRef; // index
  Pressure[4] = (vPressOut4/Vs - 0.04)/0.0012858 - PressureRef; // thumb
  delay(250);
}