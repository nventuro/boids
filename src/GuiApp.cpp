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
    for (const auto &type_boid_pair : Config::boids_by_type) {
        const auto &boid_type = type_boid_pair.first;
        const auto &boid_type_config = type_boid_pair.second;

        auto boid_type_folder = gui->addFolder(BoidMisc::typeToTypename(boid_type), boid_type_config.graphics.color);

        auto color_picker = boid_type_folder->addColorPicker("color", boid_type_config.graphics.color);
        color_picker->colorPickerEventCallback = std::bind(&GuiApp::colorPickerEvent, this, std::placeholders::_1, boid_type);

        boid_type_folder->addSlider("max speed", 1, 10, boid_type_config.max_speed);
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
    Config::boids_by_type[type].graphics.color = e.color;
}
