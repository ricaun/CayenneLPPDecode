// Copyright © Luiz Henrique Cassettari. All rights reserved.
// Licensed under the MIT license.

#ifndef _CAYENNE_LPP_DECODE_H_
#define _CAYENNE_LPP_DECODE_H_

#include <Arduino.h>
#include <Stream.h>
#include "CayenneLPP.h"
#include <ArduinoJson.h>

#define CAYENNE_LPP_DECODE_PRINT_DIGIT(p, digit) \
  do                                             \
  {                                              \
    if (digit < 0x10)                            \
      p.print('0');                              \
    p.print(digit, HEX);                         \
  } while (0)

#define CAYENNE_LPP_DECODE_PRINTLN(p, a, b)      \
  do                                             \
  {                                              \
    int32_t i;                                   \
    for (i = 0; i < b; i++)                      \
      CAYENNE_LPP_DECODE_PRINT_DIGIT(p, (a)[i]); \
    p.println();                                 \
  } while (0)

class CayenneLPPDecode : public Stream
{
public:
  CayenneLPPDecode();
  CayenneLPPDecode(uint8_t size);
  ~CayenneLPPDecode();

  virtual size_t write(uint8_t c);
  virtual size_t write(const uint8_t *buffer, size_t size);

  void dumpBuffer(Stream &out);

  void decode(JsonObject &_root);

  void reset();
  bool isValid();

private:
  virtual int available();
  virtual int read();
  virtual int peek();
  virtual void flush();

  uint8_t *buffer();

  int16_t read16();
  int32_t read24();
  int32_t read32();

  String channalField(byte channel, byte type);

  uint8_t *payload_buffer;
  uint8_t payload_length = 0;
  uint8_t payload_position = 0;
  uint8_t payload_sizemax = 64;
};

#endif
