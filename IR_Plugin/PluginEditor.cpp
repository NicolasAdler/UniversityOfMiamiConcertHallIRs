/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
IRAudioProcessorEditor::IRAudioProcessorEditor (IRAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    setSize (400, 300);
    addAndMakeVisible(loadButton);
    loadButton.setButtonText("Load IR");
    loadButton.onClick = [this]()
    {
        fileChooser = std::make_unique<juce::FileChooser>("Choose File",
                                                          audioProcessor.root,
                                                          "*");
        const auto fileChooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles | juce::FileBrowserComponent::canSelectDirectories;
        
        fileChooser->launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
        {
            juce::File result (chooser.getResult());
            
            if (result.getFileExtension() == ".wav" | result.getFileExtension() == ".mp3")
            {
                audioProcessor.savedFile = result;
                audioProcessor.root = result.getParentDirectory().getFullPathName();
                audioProcessor.irLoader.reset();
                audioProcessor.irLoader.loadImpulseResponse(audioProcessor.savedFile, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes, 0);
                irName.setText(result.getFileName(), juce::dontSendNotification);
            }
        });
    };
    
    addAndMakeVisible(irName);
}

IRAudioProcessorEditor::~IRAudioProcessorEditor()
{
}

//==============================================================================
void IRAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("", getLocalBounds(), juce::Justification::centred, 1);
}

void IRAudioProcessorEditor::resized()
{
    const auto buttonX = getWidth() * 0.35;
    const auto buttonY = getHeight() * 0.5;
    const auto buttonWidth = getWidth() * 0.15;
    const auto buttonHeight = buttonWidth * 0.5;
    loadButton.setBounds(buttonX, buttonY, buttonWidth, buttonHeight);
    irName.setBounds(loadButton.getX()+75, loadButton.getY(), buttonWidth,buttonHeight);
    
}
