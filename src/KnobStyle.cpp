//
// Created by juanmalpzg on 16/11/2022.
//

#include "KnobStyle.h"

KnobStyle::KnobStyle() {
    knobImage = juce::ImageCache::getFromMemory(BinaryData::knob_png, BinaryData::knob_pngSize);
}

KnobStyle::~KnobStyle() {

}

//==============================================================================

void KnobStyle::drawRotarySlider(juce::Graphics &g,
                                 int x, int y, int width, int height, float sliderPos,
                                 float rotaryStartAngle, float rotaryEndAngle, juce::Slider &slider) {

    if (knobImage.isValid()) {
        const double rotation = (slider.getValue()
                                 - slider.getMinimum())
                                / (slider.getMaximum()
                                   - slider.getMinimum());

        const int frames = knobImage.getHeight() / knobImage.getWidth();
        const int frameId = (int) ceil(rotation * ((double) frames - 1.0));
        const float radius = jmin(width / 2.0f, height / 2.0f);
        const float centerX = x + width * 0.5f;
        const float centerY = y + height * 0.5f;
        const float rx = centerX - radius - 1.0f;
        const float ry = centerY - radius;


        g.drawImage(knobImage, (int) rx, (int) ry, 2 * (int) radius, 2 * (int) radius, 0,
                    frameId * knobImage.getWidth(), knobImage.getWidth(), knobImage.getWidth());
    }


}