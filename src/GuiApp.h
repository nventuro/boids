#ifndef _GUIAPP_H
#define _GUIAPP_H

#include "ofMain.h"
#include "DatGui.h"
#include "Boid.fwd.h"

class GuiApp : public ofBaseApp
{
public:
    void setup(void);

private:
    ofxDatGui *gui;

    void fpsCapToggleEvent(ofxDatGuiToggleEvent e);

    void boidTypeAmountChanged(ofxDatGuiSliderEvent e, BoidMisc::Type type);
    void boidTypeMaxSpeedChanged(ofxDatGuiSliderEvent e, BoidMisc::Type type);
    void boidTypeAngleOfViewChanged(ofxDatGuiSliderEvent e, BoidMisc::Type type);
    void boidTypeInflMaxDistChanged(ofxDatGuiSliderEvent e, BoidMisc::Type type);

    void boidTypeSizeChanged(ofxDatGuiSliderEvent e, BoidMisc::Type type);
    void boidTypeColorChanged(ofxDatGuiColorPickerEvent e, BoidMisc::Type type);
    void boidTypeDrawHeadChanged(ofxDatGuiToggleEvent e, BoidMisc::Type type);
};

#endif // _BOID_H
