#include <PixelEffect.h>

PixelEffect::PixelEffect(PixelAssistant& assistant)
    : assistant(assistant), T() {
}

PixelEffect::PixelEffect(PixelAssistant& assistant, unsigned long time)
    : assistant(assistant), T(time) {
}

PixelEffectFlush::PixelEffectFlush(PixelAssistant& assistant, unsigned long time, float start, float end, const RGBW color)
    : PixelEffect(assistant, time),
      last(0),
      start(start),
      length(end - start),
      color(color) {
    setup();
}

void PixelEffectFlush::_setup() {
}
void PixelEffectFlush::_loop() {
    update();
}

void PixelEffectFlush::update() {
    float now = T.percent();
    assistant.setPercent(color, start + length * last, start + length * now);
    last = now;
    if (now >= 1) delete this;
}
