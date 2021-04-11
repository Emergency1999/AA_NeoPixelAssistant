#ifndef AA_NeoPixelEffect
#define AA_NeoPixelEffect

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <Assistant.h>
#include <NeoPixelAssistant.h>
#include <Timer.h>

class NeoPixelEffect : public Assistant {
   public:
    NeoPixelEffect(NeoPixelAssistant& assistant);
    NeoPixelEffect(NeoPixelAssistant& assistant, unsigned long time);
    virtual void update() = 0;

   protected:
    // void _setup() override;
    // void _loop() override;
    NeoPixelAssistant& assistant;
    Timer T;
};

class NeoPixelEffectFlush : public NeoPixelEffect {
   public:
    NeoPixelEffectFlush(NeoPixelAssistant& assistant, unsigned long time, float start, float end, RGBW color);
    void update() override;

   private:
    void _setup() override;
    void _loop() override;

    float last;
    float start;
    float length;  //end - start
    const RGBW color;
};

#endif
