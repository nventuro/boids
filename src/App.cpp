#include "App.h"
#include "Config.h"

App::App(std::shared_ptr<GuiApp> gui) :
    gui(gui)
{
}

void App::setup(void)
{
    ofSetWindowTitle("Boids");

    ofSeedRandom();

    behaviours.clear();
    // For each boid type, there are behaviours
    for (const auto &type_behaviours_pair : Config::behaviours_by_type) {
        behaviours.insert(std::make_pair(type_behaviours_pair.first, std::vector<Behaviour*>()));

        // We create each behaviour, and configure it accordingly
        for (auto &behaviour : type_behaviours_pair.second) {
            behaviours[type_behaviours_pair.first].push_back(Behaviour::createFromName(behaviour.type_name));

            behaviours[type_behaviours_pair.first].back()->setWeight(behaviour.weight);
            behaviours[type_behaviours_pair.first].back()->setInfluencerType(behaviour.influencer_type);

            // Test for the different derived types (some of which have special configuration that needs to be performed)
            Separation* sep = dynamic_cast<Separation*>(behaviours[type_behaviours_pair.first].back());
            if (sep) {
                sep->setNearnessSelectivity(behaviour.nearness_selectivity);
            }
        }
    }

    flock.clear();
    // For each boid type, there are boids with different configuration (but they all are part of the flock)
    for (const auto &type_boid_pair : Config::boids_by_type) {
        for (int i = 0; i < type_boid_pair.second.amount; ++i) {
            flock.push_back(Boid(type_boid_pair.first, behaviours[type_boid_pair.first]));
        }
    }
}

void App::update(void)
{
    for (auto &boid : flock) {
        boid.calculateUpdate(flock);
    }

    for (auto &boid : flock) {
        boid.update(ofGetFrameRate());
    }
}

void App::draw(void)
{
    ofBackground(Config::graphics.bkgnd_color);

    for (const auto &boid : flock) {
        boid.draw();
    }
}
