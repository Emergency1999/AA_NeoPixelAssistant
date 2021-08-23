#ifndef AA_NeoPixelAssistant
#define AA_NeoPixelAssistant

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <Assistant.h>
#include <Timer.h>

struct RGB {
    byte R, G, B;
    bool operator==(RGB other);
    bool operator!=(RGB other);
};

struct RGBW {
    byte R, G, B, W;
    RGBW();
    RGBW(RGB &other);
    RGBW(byte R, byte G, byte B, byte W);
    bool operator==(RGBW other);
    bool operator!=(RGBW other);
};

class PixelAssistant : public Assistant {
   public:
    PixelAssistant();
    virtual void update(){};

    virtual RGBW get(uint16_t n) = 0;
    virtual void set(RGBW color, uint16_t n) = 0;

    virtual void set(RGBW color);
    virtual void set(RGBW color, uint16_t n1, uint16_t n2);
    virtual void setPercent(RGBW color, float p1, float p2);

    virtual uint16_t count() = 0;
};

class PartPixelAssistant : public PixelAssistant {
   public:
    PartPixelAssistant(PixelAssistant *strip);

    RGBW get(uint16_t n) override;
    void set(RGBW color, uint16_t n) override;
    uint16_t count() override;

   private:
    void _setup() override;
    void _loop() override;
    PixelAssistant *_strip;
    uint16_t _first, _count;
};

class NeoPixelAssistant : public PixelAssistant {
   public:
    NeoPixelAssistant(Adafruit_NeoPixel *strip);
    void update();

    RGBW get(uint16_t n);
    void set(RGBW color, uint16_t n);
    uint16_t count();

    // void setHue(uint16_t hue);
    // void setHue(uint16_t hue, uint16_t n);
    // void setHue(uint16_t hue, uint16_t n1, uint16_t n2);

   private:
    void _setup() override;
    void _loop() override;
    Adafruit_NeoPixel *_strip;
    bool changed = false;
};

#endif
