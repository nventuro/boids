#ifndef _BEHAVIOUR_H
#define _BEHAVIOUR_H

#include "Boid.fwd.h"
#include "Behaviour.fwd.h"

#include <vector>
#include "ofVec2f.h"

class Behaviour {
public:
    virtual ofVec2f apply(Boid *agent, std::vector<Boid*> &influencing) = 0;
};

#endif //_BEHAVIOUR_H
