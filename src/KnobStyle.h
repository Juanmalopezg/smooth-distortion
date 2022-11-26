//
// Created by juanmalpzg on 16/11/2022.
//

#include <JuceHeader.h>

class KnobStyle : public juce::LookAndFeel_V4
{
public:
    //==============================================================================
    KnobStyle ();
    ~KnobStyle () override ;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void KnobStyle::drawRotarySlider(juce::Graphics& g,
                                           int x, int y, int width, int height, float sliderPos,
                                           float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    juce::Image imageKnobJuanma;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KnobStyle)
};
