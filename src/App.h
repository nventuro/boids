#pragma once

#include "ofMain.h"
#include "GuiApp.h"

#include "Boid.h"
#include "Behaviour.h"

#include <vector>
#include <map>

class App : public ofBaseApp
{
public:
    void setup(void);
    void update(void);
    void draw(void);

    std::vector<Boid> flock;
    std::map<BoidMisc::Type, std::vector<Behaviour*> > behaviours;

    std::shared_ptr<GuiApp> gui;
};
