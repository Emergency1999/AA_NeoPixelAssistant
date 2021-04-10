#include <NeoPixelEffect.h>

NeoPixelEffect::NeoPixelEffect(NeoPixelAssistant& assistant)
    : assistant(assistant), T() {
}

NeoPixelEffect::NeoPixelEffect(NeoPixelAssistant& assistant, unsigned long time)
    : assistant(assistant), T(time) {
}

NeoPixelEffectFlush::NeoPixelEffectFlush(NeoPixelAssistant& assistant, unsigned long time, float start, float end, const RGBW color)
    : NeoPixelEffect(assistant, time),
      last(0),
      start(start),
      length(end - start),
      color(color) {
    setup();
}

void NeoPixelEffectFlush::_setup() {
}
void NeoPixelEffectFlush::_loop() {
    update();
}

void NeoPixelEffectFlush::update() {
    float now = T.percent();
    assistant.setPercent(color, start + length * last, start + length * now);
    last = now;
    if (now >= 1) delete this;
}
