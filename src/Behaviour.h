#ifndef _BEHAVIOUR_H
#define _BEHAVIOUR_H

#include "Boid.fwd.h"
#include "Behaviour.fwd.h"

#include <vector>
#include "ofVec2f.h"

class Behaviour {
public:
    Behaviour(void);

    void setWeight(float weight);
    void setInfluencerType(BoidMisc::Type type);
    
    BoidMisc::Type getInfluencerType(void);

    ofVec2f apply(Boid *influencee, std::vector<Boid*> &influencers);

    virtual ~Behaviour(); // new and delete are called on Behaviours, since pointers to them will exist (that point to derived instances)
protected:
    virtual ofVec2f applyBehaviour(Boid *influencee, std::vector<Boid*> &influencers) = 0;

private:
    float weight;
    BoidMisc::Type influencerType;
};


class Separation : public Behaviour {
public:
    Separation(void);

    void setNearnessSelectivity(float selectivity);

protected:
    virtual ofVec2f applyBehaviour(Boid *influencee, std::vector<Boid*> &influencers);

private:
    float nearnessSelectivity;
};


class Alignment : public Behaviour {
protected:
    virtual ofVec2f applyBehaviour(Boid *influencee, std::vector<Boid*> &influencers);
};


class Cohesion : public Behaviour {
protected:
    virtual ofVec2f applyBehaviour(Boid *influencee, std::vector<Boid*> &influencers);
};


class Cage : public Behaviour {
public:
    Cage(void);

    void setThreshold(int threshold);

protected:
    virtual ofVec2f applyBehaviour(Boid *influencee, std::vector<Boid*> &influencers);

private:
    int threshold;
};

#endif //_BEHAVIOUR_H
