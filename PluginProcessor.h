/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <juce_dsp/juce_dsp.h>


//==============================================================================
/**
*/
//class ImpulseResponseConvolution
//{
//    ImpulseResponseConvolution() = default;
//    ~ImpulseResponseConvolution() = default;
//    ImpulseResponseConvolution(const ImpulseResponseConvolution& impulseResponse)=default;
//    float ir;
//    public:
//    void performConfolution(float ir, juce::AudioBuffer<float>& buffer)
//    {
//        
//    }
//    void process()
//    {
//        
//    }
//};



class IRAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    IRAudioProcessor();
    ~IRAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    juce::File root, savedFile;
    juce::dsp::Convolution irLoader;

private:
    //==============================================================================
    juce::dsp::ProcessSpec spec;
    std::unique_ptr<juce::FileChooser> fileChooser;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IRAudioProcessor)
};
