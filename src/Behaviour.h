#ifndef _BEHAVIOUR_H
#define _BEHAVIOUR_H

#include "Boid.fwd.h"
#include "Behaviour.fwd.h"

#include <vector>
#include "ofVec2f.h"

class Behaviour {
public:
    void setWeight(float weight);

    ofVec2f apply(Boid *influencee, std::vector<Boid*> &influencers);

    virtual ~Behaviour(); // new and delete are called on Behaviours, since pointers to them will exist (that point to derived instances)
protected:
    virtual ofVec2f applyBehaviour(Boid *influencee, std::vector<Boid*> &influencers) = 0;

private:
    float weight;
};

class Cohesion : public Behaviour {
protected:
    virtual ofVec2f applyBehaviour(Boid *influencee, std::vector<Boid*> &influencers);
};

#endif //_BEHAVIOUR_H
