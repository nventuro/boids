#ifndef _GUIAPP_H
#define _GUIAPP_H

#include "ofMain.h"
#include "ofxDatGui.h"

class GuiApp : public ofBaseApp
{
public:
    void setup(void);
    void update(void);
    void draw(void);
    void exit(void);

private:
    ofxDatGui *gui;
};

#endif // _BOID_H
