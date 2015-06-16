#ifndef _BOID_H
#define _BOID_H

#include "Boid.fwd.h"
#include "Behaviour.fwd.h"

#include <vector>
#include "ofVec2f.h"

class Boid {
public:
    void setup(int w, int h, float maxDist = 60, int behaviourPeriod = 5);
    void update(std::vector<Boid> &flock);
    void draw(void);
    void exit(void);

    ofVec2f getPos(void);
    ofVec2f getSpeed(void);
    ofVec2f getAccel(void);

private:
    int maxX;
    int maxY;

    float maxDist;

    int behaviourPeriod;
    int noBehaviourUpdates;

    ofVec2f pos;
    ofVec2f speed;
    ofVec2f accel;

    std::vector<Behaviour*> behaviours;

    int id;

    static int getNextID(void);
    static int idGen;
};

#endif // _BOID_H
