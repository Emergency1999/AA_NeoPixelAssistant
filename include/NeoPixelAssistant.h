#ifndef AA_NeoPixelAssistant
#define AA_NeoPixelAssistant

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <Assistant.h>
#include <Timer.h>

typedef struct RGB {
    byte R;
    byte G;
    byte B;
    bool operator==(RGB other) {
        return R == other.R && G == other.G && B == other.B;
    }
    bool operator!=(RGB other) { return !(operator==(other)); }
};

typedef struct RGBW {
    byte R;
    byte G;
    byte B;
    byte W;
    RGBW(RGB &other) {
        R = other.R;
        G = other.G;
        B = other.B;
        W = 0;
    };
    RGBW(byte R, byte G, byte B, byte W) {
        this->R = R;
        this->G = G;
        this->B = B;
        this->W = W;
    };
    bool operator==(RGBW other) {
        return R == other.R && G == other.G && B == other.B && W == other.W;
    }
    bool operator!=(RGBW other) { return !(operator==(other)); }
};

class NeoPixelAssistant : public Assistant {
   public:
    NeoPixelAssistant(Adafruit_NeoPixel *strip);
    void update();

    RGBW get(uint16_t n);
    void set(RGBW color);
    void set(RGBW color, uint16_t n);
    void set(RGBW color, uint16_t n1, uint16_t n2);
    void setPercent(RGBW color, float p1, float p2);
    uint16_t count();  //returns pins count

    void setHue(uint16_t hue);
    void setHue(uint16_t hue, uint16_t n);
    void setHue(uint16_t hue, uint16_t n1, uint16_t n2);

   private:
    void _setup() override;
    void _loop() override;
    Adafruit_NeoPixel *_strip;
    bool changed = false;
};

#endif
