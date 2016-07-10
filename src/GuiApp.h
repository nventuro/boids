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
    void colorPickerEvent(ofxDatGuiColorPickerEvent e, BoidMisc::Type type);
};

#endif // _BOID_H
