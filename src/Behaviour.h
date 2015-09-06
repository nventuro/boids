#ifndef _BEHAVIOUR_H
#define _BEHAVIOUR_H

#include "Boid.fwd.h"
#include "Behaviour.fwd.h"

#include <vector>
#include <string>
#include "ofVec2f.h"

class Behaviour {
public:
    Behaviour(void);

    static Behaviour* createFromName(std::string behaviour_name);
    virtual std::string getBehaviourName(void) = 0;

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
    virtual std::string getBehaviourName(void);

    void setNearnessSelectivity(float selectivity);

protected:
    virtual ofVec2f applyBehaviour(Boid *influencee, std::vector<Boid*> &influencers);

private:
    float nearnessSelectivity;
};


class Alignment : public Behaviour {
public:
    virtual std::string getBehaviourName(void);

protected:
    virtual ofVec2f applyBehaviour(Boid *influencee, std::vector<Boid*> &influencers);
};


class Cohesion : public Behaviour {
public:
    virtual std::string getBehaviourName(void);

protected:
    virtual ofVec2f applyBehaviour(Boid *influencee, std::vector<Boid*> &influencers);
};

#endif //_BEHAVIOUR_H
