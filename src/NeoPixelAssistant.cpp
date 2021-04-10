#include <NeoPixelAssistant.h>

NeoPixelAssistant::NeoPixelAssistant(Adafruit_NeoPixel* strip) {
    _strip = strip;
}

void NeoPixelAssistant::_setup() {
    _strip->begin();
    _strip->show();
    changed = false;
}

void NeoPixelAssistant::_loop() {
    if (changed) update();
}

void NeoPixelAssistant::update() {
    if (_strip->canShow()) {
        _strip->show();
        changed = false;
    }
}

uint16_t NeoPixelAssistant::count() {
    return _strip->numPixels();
}

void NeoPixelAssistant::setPercent(RGBW color, float p1, float p2) {
    if (p2 < p1) {
        float pt = p2;
        p2 = p1;
        p1 = pt;
    }
    if (p1 < 0) p1 = 0;
    if (p2 > 1) p2 = 1;
    uint16_t n1 = _strip->numPixels() * p1;
    uint16_t n2 = _strip->numPixels() * p2;
    set(color, n1, n2);
}

RGBW NeoPixelAssistant::get(uint16_t n) {
    union COLOR {
        uint32_t value;
        struct {
            byte B;
            byte G;
            byte R;
            byte W;
        } byte;
    };
    COLOR r;
    r.value = _strip->getPixelColor(n);
    return {r.byte.R, r.byte.G, r.byte.B, r.byte.W};
}

void NeoPixelAssistant::set(RGBW color) {
    set(color, 0, _strip->numPixels());
}
void NeoPixelAssistant::set(RGBW color, uint16_t n) {
    _strip->setPixelColor(n, color.R, color.G, color.B, color.W);
    changed = true;
}
void NeoPixelAssistant::set(RGBW color, uint16_t n1, uint16_t n2) {
    for (int i = n1; i < n2; i++) {
        set(color, i);
    }
}

void NeoPixelAssistant::setHue(uint16_t hue) {
    setHue(hue, 0, _strip->numPixels());
}
void NeoPixelAssistant::setHue(uint16_t hue, uint16_t n) {
    _strip->setPixelColor(n, _strip->gamma32(_strip->ColorHSV(hue)));
    changed = true;
}
void NeoPixelAssistant::setHue(uint16_t hue, uint16_t n1, uint16_t n2) {
    for (int i = n1; i < n2; i++) {
        setHue(hue, i);
    }
}
