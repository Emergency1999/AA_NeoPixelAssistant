#ifndef AA_PixelAssistant
#define AA_PixelAssistant

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <Assistant.h>
#include <Timer.h>
// #include <Vector.h>

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
    PartPixelAssistant(PixelAssistant *strip, uint16_t n1, uint16_t n2);

    RGBW get(uint16_t n) override;
    using PixelAssistant::set;
    void set(RGBW color, uint16_t n) override;
    uint16_t count() override;

   private:
    void _setup() override;
    void _loop() override;
    PixelAssistant *_strip;
    bool _backwards;
    uint16_t _first, _count;
};

class MultiPixelAssistant : public PixelAssistant {
   public:
    MultiPixelAssistant(PixelAssistant *stripA, PixelAssistant *stripB);
    MultiPixelAssistant(PixelAssistant *stripA, PixelAssistant *stripB, PixelAssistant *stripC);
    MultiPixelAssistant(PixelAssistant *stripA, PixelAssistant *stripB, PixelAssistant *stripC, PixelAssistant *stripD);
    MultiPixelAssistant(PixelAssistant **strips, byte count);
    ~MultiPixelAssistant();

    RGBW get(uint16_t n) override;
    using PixelAssistant::set;
    void set(RGBW color, uint16_t n) override;
    uint16_t count() override;

   private:
    void _setup() override;
    void _loop() override;
    PixelAssistant **_strips;
    byte _stripcount;
};

class NeoPixelAssistant : public PixelAssistant {
   public:
    NeoPixelAssistant(Adafruit_NeoPixel *strip);
    NeoPixelAssistant(Adafruit_NeoPixel *strip, unsigned long minUpdateInterval);
    void update();

    RGBW get(uint16_t n) override;
    using PixelAssistant::set;
    void set(RGBW color, uint16_t n) override;
    uint16_t count();

    // void setHue(uint16_t hue);
    // void setHue(uint16_t hue, uint16_t n);
    // void setHue(uint16_t hue, uint16_t n1, uint16_t n2);

   private:
    void _setup() override;
    void _loop() override;
    Adafruit_NeoPixel *_strip;
    Timer T;
    bool changed = false;
};

#endif
