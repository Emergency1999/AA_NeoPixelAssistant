#include <NeoPixelAssistant.h>

// -------------------------------------------------------------------------------- RGB
bool RGB::operator==(RGB other) {
    return R == other.R && G == other.G && B == other.B;
}
bool RGB::operator!=(RGB other) {
    return !(operator==(other));
}

// -------------------------------------------------------------------------------- RGBW
RGBW::RGBW() {
    R = 0;
    G = 0;
    B = 0;
    W = 0;
}
RGBW::RGBW(RGB& other) {
    R = other.R;
    G = other.G;
    B = other.B;
    W = 0;
};
RGBW::RGBW(byte R, byte G, byte B, byte W) {
    this->R = R;
    this->G = G;
    this->B = B;
    this->W = W;
};
bool RGBW::operator==(RGBW other) {
    return R == other.R && G == other.G && B == other.B && W == other.W;
}
bool RGBW::operator!=(RGBW other) {
    return !(operator==(other));
}

// -------------------------------------------------------------------------------- PixelAssistant

void PixelAssistant::set(RGBW color) {
    set(color, 0, count());
}
void PixelAssistant::set(RGBW color, uint16_t n1, uint16_t n2) {
    for (uint16_t i = n1; i < n2; i++) {
        set(color, i);
    }
}

void PixelAssistant::setPercent(RGBW color, float p1, float p2) {
    if (p2 < p1) {
        float pt = p2;
        p2 = p1;
        p1 = pt;
    }
    if (p1 < 0) p1 = 0;
    if (p2 > 1) p2 = 1;
    uint16_t n1 = count() * p1;
    uint16_t n2 = count() * p2;
    set(color, n1, n2);
}

// -------------------------------------------------------------------------------- PartPixelAssistant
PartPixelAssistant::PartPixelAssistant(PixelAssistant* strip, uint16_t n1, uint16_t n2)
    : _strip(strip), _backwards(n1 > n2), _first(n1), _count(_backwards ? n1 - n2 : n2 - n1) {
    ASSERT_ERR(n1 != n2, "need to have more pixels than 0");
}

void PartPixelAssistant::_setup() {}

void PartPixelAssistant::_loop() {}

uint16_t PartPixelAssistant::count() {
    return _count;
}

RGBW PartPixelAssistant::get(uint16_t n) {
    ASSERT_ERR(n < count(), "n<count()");
    return _strip->get(_first + _backwards ? -n - 1 : n);
}

void PartPixelAssistant::set(RGBW color, uint16_t n) {
    ASSERT_WARN(n < count(), "n<count()", return );
    return _strip->set(color, _first + _backwards ? -n - 1 : n);
}

// -------------------------------------------------------------------------------- MultiPixelAssistant
MultiPixelAssistant::MultiPixelAssistant(PixelAssistant* stripA, PixelAssistant* stripB) {
    MultiPixelAssistant(
        new PixelAssistant* [2] { stripA, stripB }, 2);
}
MultiPixelAssistant::MultiPixelAssistant(PixelAssistant* stripA, PixelAssistant* stripB, PixelAssistant* stripC) {
    MultiPixelAssistant(
        new PixelAssistant* [3] { stripA, stripB, stripC }, 3);
}
MultiPixelAssistant::MultiPixelAssistant(PixelAssistant* stripA, PixelAssistant* stripB, PixelAssistant* stripC, PixelAssistant* stripD) {
    MultiPixelAssistant(
        new PixelAssistant* [4] { stripA, stripB, stripC, stripD }, 4);
}
MultiPixelAssistant::MultiPixelAssistant(PixelAssistant** strips, byte count) : _strips(strips), _stripcount(count) {}
MultiPixelAssistant::~MultiPixelAssistant() { delete[] _strips; }

void MultiPixelAssistant::_setup() {}

void MultiPixelAssistant::_loop() {}

uint16_t MultiPixelAssistant::count() {
    uint16_t s = 0;
    for (byte i = 0; i < _stripcount; i++)
        s += _strips[i]->count();
    return s;
}

RGBW MultiPixelAssistant::get(uint16_t n) {
    for (byte i = 0; i < _stripcount; i++) {
        uint16_t c = _strips[i]->count();
        if (n < c)
            return _strips[i]->get(n);
        else
            n -= c;
    }
    ASSERT_ERR(false, "n<count()");
    return {0, 0, 0, 0};
}

void MultiPixelAssistant::set(RGBW color, uint16_t n) {
    for (byte i = 0; i < _stripcount; i++) {
        uint16_t c = _strips[i]->count();
        if (n < c) {
            _strips[i]->set(color, n);
            return;
        } else
            n -= c;
    }
    ASSERT_WARN(false, "n<count()", return );
}

// -------------------------------------------------------------------------------- NeoPixelAssistant
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

RGBW NeoPixelAssistant::get(uint16_t n) {
    ASSERT_WARN(n < count(), "n<count()", n = 0);
    union {
        uint32_t value;
        struct {
            byte B;
            byte G;
            byte R;
            byte W;
        } byte;
    } r;
    r.value = _strip->getPixelColor(n);
    return {r.byte.R, r.byte.G, r.byte.B, r.byte.W};
}

void NeoPixelAssistant::set(RGBW color, uint16_t n) {
    ASSERT_WARN(n < count(), "n<count()", n = 0);
    _strip->setPixelColor(n, color.R, color.G, color.B, color.W);
    changed = true;
}

// void NeoPixelAssistant::setHue(uint16_t hue) {
//     setHue(hue, 0, _strip->numPixels());
// }
// void NeoPixelAssistant::setHue(uint16_t hue, uint16_t n) {
//     _strip->setPixelColor(n, _strip->gamma32(_strip->ColorHSV(hue)));
//     changed = true;
// }
// void NeoPixelAssistant::setHue(uint16_t hue, uint16_t n1, uint16_t n2) {
//     for (uint16_t i = n1; i < n2; i++) {
//         setHue(hue, i);
//     }
// }
