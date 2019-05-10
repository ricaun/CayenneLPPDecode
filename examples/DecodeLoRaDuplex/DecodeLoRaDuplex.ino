/*
  DecodeLoRaDuplex.ino

  This code uses LoRa library
  https://github.com/sandeepmistry/arduino-LoRa 

  Receive LoRa package and decode the CayenneLPP to Json,
  and Send LoRa package with CayenneLPP format.

  You need two devices to test this example.

  Updated: 
    02-04-2019 - Update to ArduinoJson v6

  created 18 October 2018
  by Luiz H. Cassettari
*/

#include <SPI.h>
#include <LoRa.h>
#include <CayenneLPPDecode.h>

const long frequency = 915E6;

const int csPin = 10;
const int resetPin = 9;
const int irqPin = 2;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  LoRa.setPins(csPin, resetPin, irqPin);

  if (!LoRa.begin(frequency)) {
    Serial.println("LoRa init failed. Check your connections.");
    while (true);
  }

  Serial.println("LoRa init succeeded.");
  Serial.println();

  LoRa.onReceive(onReceive);
  LoRa.receive();
}

void loop() {
  if (runEvery(5000)) {

    LoRa_sendMessage();

    Serial.println("Send Message!");
  }
}

void LoRa_sendMessage() {
  LoRa.idle();

  CayenneLPP lpp(64);
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

  LoRa.beginPacket();
  LoRa.write(lpp.getBuffer(), lpp.getSize());
  LoRa.endPacket();

  LoRa.receive();
}

void onReceive(int packetSize) {

  DynamicJsonDocument jsonBuffer(512);
  CayenneLPPDecode lppd;

  JsonObject root = jsonBuffer.to<JsonObject>();

  while (LoRa.available()) {
    lppd.write(LoRa.read());
  }

  Serial.print("Receive: ");
  Serial.println();

  if (lppd.isValid())
  {
    lppd.decode(root);

    serializeJsonPretty(root, Serial);
    Serial.println();
  }
}

boolean runEvery(unsigned long interval)
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}