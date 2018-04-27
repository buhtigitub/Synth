/*
  ==============================================================================

    This file was auto-generated and contains the startup code for a PIP.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthUsingMidiInputTutorial_01.h"

class Application    : public JUCEApplication
{
public:
    //==============================================================================
    Application() {}

    const String getApplicationName() override       { return "SynthUsingMidiInputTutorial"; }
    const String getApplicationVersion() override    { return "1.0.0"; }

    void initialise (const String&) override         { mainWindow = new MainWindow ("SynthUsingMidiInputTutorial", new MainContentComponent()); }
    void shutdown() override                         { mainWindow = nullptr; }

private:
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow (const String& name, Component* c)  : DocumentWindow (name,
                                                                         Desktop::getInstance().getDefaultLookAndFeel()
                                                                                               .findColour (ResizableWindow::backgroundColourId),
                                                                         DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (c, true);

           #if JUCE_ANDROID || JUCE_IOS
            setFullScreen (true);
           #else
            setResizable (true, false);
            setResizeLimits (300, 250, 10000, 10000);
            centreWithSize (getWidth(), getHeight());
           #endif

            setVisible (true);
        }

        void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };
    ScopedPointer<MainWindow> mainWindow;
};

//==============================================================================
START_JUCE_APPLICATION (Application)
