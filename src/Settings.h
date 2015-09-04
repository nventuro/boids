#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <string>
#include <map>

#include "Boid.fwd.h"

class Settings {
public:
    static int width;
    static int height;
    static int fps;

    struct BoidTypeData {
        int amount;
        int maxDist;
        int period;
    };
    static std::map<BoidMisc::Type, BoidTypeData> boidType;

    static void load(void);
};

#endif // _SETTINGS_H
