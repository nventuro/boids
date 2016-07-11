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
    fps_toggle->toggleEventCallback = std::bind(&GuiApp::fpsCapToggleEvent, this, std::placeholders::_1);

    gui->addBreak();
    gui->addLabel("boid controls");
    for (const auto &type_boid_pair : Config::boids_by_type) {
        const auto &boid_type = type_boid_pair.first;
        const auto &boid_type_config = type_boid_pair.second;

        auto boid_type_folder = gui->addFolder(BoidMisc::typeToTypename(boid_type));

        auto amount_slider = boid_type_folder->addSlider("amount", 1, 5000);
        amount_slider->sliderEventCallback = std::bind(&GuiApp::boidTypeAmountChanged, this, std::placeholders::_1, boid_type);
        amount_slider->setPrecision(0);
        amount_slider->setValue(boid_type_config.amount);

        auto infl_max_dist_slider = boid_type_folder->addSlider("infl max dist", 1, 120, boid_type_config.infl_max_dist);
        infl_max_dist_slider->sliderEventCallback = std::bind(&GuiApp::boidTypeInflMaxDistChanged, this, std::placeholders::_1, boid_type);

        auto max_speed_slider = boid_type_folder->addSlider("max speed", 0.5, 10, boid_type_config.max_speed);
        max_speed_slider->sliderEventCallback = std::bind(&GuiApp::boidTypeMaxSpeedChanged, this, std::placeholders::_1, boid_type);

        auto color_picker = boid_type_folder->addColorPicker("color", boid_type_config.graphics.color);
        color_picker->colorPickerEventCallback = std::bind(&GuiApp::boidTypeColorChanged, this, std::placeholders::_1, boid_type);

        auto size_slider = boid_type_folder->addSlider("size", 1, 4);
        size_slider->sliderEventCallback = std::bind(&GuiApp::boidTypeSizeChanged, this, std::placeholders::_1, boid_type);
        size_slider->setPrecision(0);
        size_slider->setValue(boid_type_config.graphics.size); // We need to set this after the precision so that the proper precision is applied
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

void GuiApp::boidTypeAmountChanged(ofxDatGuiSliderEvent e, BoidMisc::Type type)
{
}

void GuiApp::boidTypeMaxSpeedChanged(ofxDatGuiSliderEvent e, BoidMisc::Type type)
{
    Config::boids_by_type[type].max_speed = e.value;
}

void GuiApp::boidTypeInflMaxDistChanged(ofxDatGuiSliderEvent e, BoidMisc::Type type)
{
    Config::boids_by_type[type].infl_max_dist = e.value;
}

void GuiApp::boidTypeColorChanged(ofxDatGuiColorPickerEvent e, BoidMisc::Type type)
{
    Config::boids_by_type[type].graphics.color = e.color;
}

void GuiApp::boidTypeSizeChanged(ofxDatGuiSliderEvent e, BoidMisc::Type type)
{
    Config::boids_by_type[type].graphics.size = e.value;
}
