#include "Behaviour.h"

#include "Boid.h"

Behaviour::~Behaviour() {
}

void Behaviour::setWeight(float weight) {
    this->weight = weight;
}

ofVec2f Behaviour::apply(Boid *influencee, std::vector<Boid*> &influencers) {
    if (influencers.size() == 0) {
        return influencee->getAccel();
    }
    else {
        ofVec2f behResult = applyBehaviour(influencee, influencers);
        return behResult.getNormalized() * weight;
    }
}

ofVec2f Cohesion::applyBehaviour(Boid *influencee, std::vector<Boid*> &influencers) {
    ofVec2f flockCenter(0, 0);

    for (std::vector<Boid*>::iterator inf_it = influencers.begin(); inf_it != influencers.end(); ++inf_it) {
        flockCenter += (*inf_it)->getPos();
    }
    flockCenter /= influencers.size();

    return flockCenter - influencee->getPos();
}
