#ifndef AA_PixelEffect
#define AA_PixelEffect

#include <Arduino.h>
#include <PixelAssistant.h>
#include <Timer.h>

class PixelEffect : public Assistant {
   public:
    PixelEffect(PixelAssistant& assistant);
    PixelEffect(PixelAssistant& assistant, unsigned long time);
    virtual void update() = 0;

   protected:
    // void _setup() override;
    // void _loop() override;
    PixelAssistant& assistant;
    Timer T;
};

class PixelEffectFlush : public PixelEffect {
   public:
    PixelEffectFlush(PixelAssistant& assistant, unsigned long time, float start, float end, RGBW color);
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
