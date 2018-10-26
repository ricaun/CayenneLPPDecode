/*
  EncodePrintHex.ino

  This code create a CayenneLPP package and print the hex values.

  created 26 October 2018
  by Luiz H. Cassettari
*/


#include <CayenneLPPDecode.h>

void setup() {
  CayenneLPP lpp(64);

  Serial.begin(115200);
  Serial.println();

  lpp.reset();
  lpp.addDigitalInput(1, 0);
  printHex(Serial, lpp.getBuffer(), lpp.getSize());
  Serial.println();

  lpp.reset();
  lpp.addDigitalOutput(2, 1);
  printHex(Serial, lpp.getBuffer(), lpp.getSize());
  Serial.println();

  lpp.reset();
  lpp.addAnalogInput(3, 1.23f);
  printHex(Serial, lpp.getBuffer(), lpp.getSize());
  Serial.println();

  lpp.reset();
  lpp.addAnalogOutput(4, 3.45f);
  printHex(Serial, lpp.getBuffer(), lpp.getSize());
  Serial.println();

  lpp.reset();
  lpp.addLuminosity(5, 20304);
  printHex(Serial, lpp.getBuffer(), lpp.getSize());
  Serial.println();

  lpp.reset();
  lpp.addPresence(6, 1);
  printHex(Serial, lpp.getBuffer(), lpp.getSize());
  Serial.println();

  lpp.reset();
  lpp.addTemperature(7, 26.5f);
  printHex(Serial, lpp.getBuffer(), lpp.getSize());
  Serial.println();

  lpp.reset();
  lpp.addRelativeHumidity(8, 86.6f);
  printHex(Serial, lpp.getBuffer(), lpp.getSize());
  Serial.println();

  lpp.reset();
  lpp.addAccelerometer(9, 1.234f, -1.234f, 0.567f);
  printHex(Serial, lpp.getBuffer(), lpp.getSize());
  Serial.println();

  lpp.reset();
  lpp.addBarometricPressure(10, 1023.4f);
  printHex(Serial, lpp.getBuffer(), lpp.getSize());
  Serial.println();

  lpp.reset();
  lpp.addGyrometer(1, -12.34f, 45.56f, 89.01f);
  printHex(Serial, lpp.getBuffer(), lpp.getSize());
  Serial.println();

  lpp.reset();
  lpp.addGPS(1, -12.34f, 45.56f, 9.01f);
  printHex(Serial, lpp.getBuffer(), lpp.getSize());
  Serial.println();

}

void loop() {

}

void printHex(Stream &p, byte * b, int c)
{
  for (int i = 0; i < c; i++)
  {
    byte d = b[i];
    if (d < 0x10) p.print('0');
    p.print(d, HEX);
  }
}
