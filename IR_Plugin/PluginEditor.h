/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class IRAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    IRAudioProcessorEditor (IRAudioProcessor&);
    ~IRAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    IRAudioProcessor& audioProcessor;
    juce::TextButton loadButton;
    std::unique_ptr<juce::FileChooser> fileChooser;
    juce::Label irName;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRAudioProcessorEditor)
};

