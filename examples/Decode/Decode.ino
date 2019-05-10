/*
  Decode.ino

  This code create a CayenneLPP package and decode to Json.

  Updated: 
    02-04-2019 - Update to ArduinoJson v6

  created 18 October 2018
  by Luiz H. Cassettari
*/

#include <CayenneLPPDecode.h>

void setup()
{
  DynamicJsonDocument jsonBuffer(512);
  CayenneLPP lpp(64);
  CayenneLPPDecode lppd;

  JsonObject root = jsonBuffer.to<JsonObject>();

  Serial.begin(115200);
  Serial.println();

  lpp.reset();
  lpp.addDigitalInput(1, 0);
  lpp.addDigitalOutput(2, 1);
  lpp.addAnalogInput(3, 1.23f);
  lpp.addAnalogOutput(4, 3.45f);
  lpp.addLuminosity(5, 20304);
  lpp.addPresence(6, 1);
  lpp.addTemperature(7, 26.5f);
  lpp.addRelativeHumidity(8, 86.6f);
  lpp.addAccelerometer(9, 1.234f, -1.234f, 0.567f);
  lpp.addBarometricPressure(10, 1023.4f);
  lpp.addGyrometer(1, -12.34f, 45.56f, 89.01f);
  lpp.addGPS(1, -12.34f, 45.56f, 9.01f);

  lppd.write(lpp.getBuffer(), lpp.getSize());
  if (lppd.isValid())
  {
    lppd.decode(root);
    serializeJsonPretty(root, Serial);
    Serial.println();
  }
}

void loop()
{
}