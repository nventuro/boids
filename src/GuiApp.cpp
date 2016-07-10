#include "GuiApp.h"
#include "GuiTheme.h"
#include "Config.h"

#include <functional>

void GuiApp::setup(void)
{
    ofSetWindowTitle("Controls");

    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
    auto theme = new GuiTheme();
    gui->setTheme(theme);

    gui->addHeader("boids");
    gui->getHeader()->setDraggable(false);

    gui->addFRM(0.1);
    auto fps_toggle = gui->addToggle("cap to 30 FPS");
    fps_toggle->onToggleEvent(this, &GuiApp::fpsCapToggleEvent);

    gui->addBreak();
    gui->addLabel("boid controls");
    for (const auto &type_boid_pair : Config::boidsByType) {

        auto boids_folder = gui->addFolder(BoidMisc::typeToTypename(type_boid_pair.first), type_boid_pair.second.graphics.color);

        auto color_picker = boids_folder->addColorPicker("color", type_boid_pair.second.graphics.color);

        color_picker->colorPickerEventCallback = std::bind(&GuiApp::colorPickerEvent, this, std::placeholders::_1, type_boid_pair.first);

        boids_folder->addSlider("max speed", 1, 10, type_boid_pair.second.maxSpeed);
    }

    ofBackground(theme->color.guiBackground);

    ofSetFrameRate(60);
}

void GuiApp::fpsCapToggleEvent(ofxDatGuiToggleEvent e)
{
    if (e.checked) {
        ofSetFrameRate(30);
    } else {
        ofSetFrameRate(60);
    }
}

void GuiApp::colorPickerEvent(ofxDatGuiColorPickerEvent e, BoidMisc::Type type)
{
    Config::boidsByType[type].graphics.color = e.color;
}
