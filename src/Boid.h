#ifndef _BOID_H
#define _BOID_H

#include "ofVec2f.h"
#include <vector>

class Boid {
public:
    void setup(int w, int h, float maxDist = 60, int behaviourPeriod = 5);
    void update(std::vector<Boid> &flock);
    void draw(void);

private:
    int maxX;
    int maxY;

    float maxDist;
    int behaviourPeriod;

    ofVec2f pos;
    ofVec2f speed;

    int id;

    static int getNextID(void);
    static int idGen;
};

#endif // _BOID_H
