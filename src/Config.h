#ifndef _CONFIG_H
#define _CONFIG_H

#include <string>
#include <map>
#include <vector>

#include "ofColor.h"

#include "Boid.fwd.h"

class Config
{
public:
    static int width;
    static int height;
    static int fps;

    struct Graphics {
        ofColor bkgnd_color;
    };
    static Graphics graphics;

    struct Boid {
        int amount;
        int infl_max_dist;
        int period;
        float max_speed;
        struct {
            ofColor color;
            int size;
            bool draw_head;
        } graphics;
    };

    static std::map<BoidMisc::Type, Config::Boid> boids_by_type;

    struct Behaviour {
        std::string type_name; // Used to call the corresponding constructor
        float weight;
        BoidMisc::Type influencer_type;

        // Rather ugly, but we must put all possible configuration values here (for
        // all Behaviours), since we don't know the Behaviour's type

        // Separation
        float nearness_selectivity;
    };
    static std::map<BoidMisc::Type, std::vector<Config::Behaviour> > behaviours_by_type;

    static void load(void);
    static void save(void);

    static ofColor stringToColor(std::string str);
    static std::string colorToString(ofColor color);
};

#endif // _CONFIG_H
