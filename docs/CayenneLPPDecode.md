# API Reference

The `CayenneLPPDecode` class enables Arduino devices to decode data with the Cayenne Low Power Payload (LPP). [Read more about Cayenne LPP](https://mydevices.com/cayenne/docs/lora/#lora-cayenne-low-power-payload)

## Class: `CayenneLPPDecode`

Include and instantiate the CayenneLPPDecode class. The constructor takes the size of the allocated buffer.

```c
#include <CayenneLPPDecode.h>

CayenneLPPDecode lppd;
CayenneLPPDecode lppd(uint8_t size);
```

- `uint8_t size`: The maximum payload size to send, default `64`.

## Method: `reset`

Resets the buffer.

```c
void reset(void);
```

## Method: `write`

Writes binary data to the buffer.

```c
size_t write(val);
size_t write(buf, len);
```

## Method: `decode`

Decode buffer to the JsonObject root, check [ArduinoJson](https://github.com/bblanchon/ArduinoJson) library.

```c
void decode(JsonObject &root);
```

## Method: `isValid`

This function checks if the buffer is a CayenneLPP valid payload.

```c
bool isValid();
```

