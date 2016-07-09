#include "GuiApp.h"
#include "GuiTheme.h"
#include "Settings.h"
#include "Boid.fwd.h"

void GuiApp::setup(void)
{
    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
    auto theme = new GuiTheme();
    gui->setTheme(theme);

    gui->addHeader("boids");
    gui->getHeader()->setDraggable(false);

    gui->addFRM(0.1);

    for (auto &type_boid_pair : Settings::boidsByType) {
        auto brk = gui->addBreak();
        brk->setHeight(100.0f);

        cout << brk->getHeight() << endl;

        auto boids_folder = gui->addFolder(BoidMisc::typeToTypename(type_boid_pair.first), type_boid_pair.second.graphics.color);
        boids_folder->addColorPicker("color", type_boid_pair.second.graphics.color);
        boids_folder->addSlider("max speed", 1, 10, type_boid_pair.second.maxSpeed);
    }

    ofBackground(theme->color.guiBackground);
    ofSetVerticalSync(false);
}

void GuiApp::update(void)
{
}

void GuiApp::draw(void)
{
}

void GuiApp::exit(void)
{
}
