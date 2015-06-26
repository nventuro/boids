#ifndef _BOID_H
#define _BOID_H

#include "Boid.fwd.h"
#include "Behaviour.fwd.h"

#include <vector>
#include "ofVec2f.h"

class Boid {
public:
    /*enum Type {
        REGULAR,
        PREDATOR
    };*/

    Boid(void);

    void setup(int w, int h, BoidMisc::Type = BoidMisc::REGULAR, float maxDist = 60, int behaviourPeriod = 5);
    void update(std::vector<Boid> &flock);
    void draw(void);
    void exit(void);

    ofVec2f getPos(void);
    ofVec2f getSpeed(void);
    ofVec2f getAccel(void);
    
    BoidMisc::Type getType(void);

    int getMaxX(void);
    int getMaxY(void);

    int getId(void);

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
    
    BoidMisc::Type type;

    int id;

    static int getNextID(void);
    static int idGen;
};

#endif // _BOID_H
