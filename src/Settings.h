#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <string>
#include <map>
#include <vector>

#include "ofColor.h"

#include "Boid.fwd.h"

class Settings {
public:
    static int width;
    static int height;
    static int fps;

    struct Graphics {
        ofColor backgroundColor;
    };
    static Graphics graphics;

    struct Boid {
        int amount;
        int maxDist;
        int period;
        float maxSpeed;
        struct {
            ofColor color;
            int size;
        } graphics;
    };

    static std::map<BoidMisc::Type, Settings::Boid> boidsByType;

    struct Behaviour {
        std::string typeName; // Used to call the corresponding constructor
        float weight;
        BoidMisc::Type influencerType;

        // Rather ugly, but we must put all possible configuration values here (for
        // all Behaviours), since we don't know the Behaviour's type

        // Separation
        float nearnessSelectivity;
    };
    static std::map<BoidMisc::Type, std::vector<Settings::Behaviour> > behavioursByType;

    static void load(void);
    static void save(void);

    static ofColor stringToColor(std::string str);
    static std::string colorToString(ofColor color);
};

#endif // _SETTINGS_H
