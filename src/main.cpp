#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <NeoPixelAssistant.h>
#include <NeoPixelEffect.h>

NeoPixelAssistant AB(new Adafruit_NeoPixel(20, 18, NEO_GRBW + NEO_KHZ800));
NeoPixelAssistant BB(new Adafruit_NeoPixel(20, 18, NEO_GRBW + NEO_KHZ800));
NeoPixelAssistant CA(new Adafruit_NeoPixel(20, 18, NEO_GRBW + NEO_KHZ800));

PartPixelAssistant PA_(&AB, 0, 10);
PartPixelAssistant P_A(&CA, 10, 20);
MultiPixelAssistant A(&PA_, &P_A);

PartPixelAssistant P_B(&AB, 10, 20);
MultiPixelAssistant B(&P_B, &BB);

PartPixelAssistant C(&CA, 0, 10);

void setup() {}
void loop() {}
