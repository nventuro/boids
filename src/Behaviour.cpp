#include "Behaviour.h"

#include "Boid.h"

#include <cmath>
#include <stdexcept>

// Base class

Behaviour::Behaviour(void) {
    weight = 1;
    influencerType = BoidMisc::REGULAR;
}

Behaviour* Behaviour::createFromName(std::string behaviour_name) {
    if (behaviour_name == "separation") {
        return new Separation;
    }
    else if (behaviour_name == "alignment") {
        return new Alignment;
    }
    else if (behaviour_name == "cohesion") {
        return new Cohesion;
    }
    else {
        std::stringstream msg;
        msg << "Behaviour::createFromName: unknown behaviour name: " << behaviour_name << std::endl;
        throw std::invalid_argument(msg.str());
    }
}

Behaviour::~Behaviour(void) {
}

void Behaviour::setWeight(float weight) {
    this->weight = weight;
}

void Behaviour::setInfluencerType(BoidMisc::Type type) {
    influencerType = type;
}

BoidMisc::Type Behaviour::getInfluencerType(void) {
    return influencerType;
}

ofVec2f Behaviour::apply(Boid *influencee, std::vector<Boid*> &influencers) {
    if (influencers.size() == 0) {
        return influencee->getAccel(); // Reinforce the current acceleration
    }
    else {
        return applyBehaviour(influencee, influencers) * weight;
    }
}

// Separation

Separation::Separation(void) {
    nearnessSelectivity = 1;
}

std::string Separation::getBehaviourName(void) {
    return "separation";
}

void Separation::setNearnessSelectivity(float selectivity) {
    nearnessSelectivity = selectivity;
}

ofVec2f Separation::applyBehaviour(Boid *influencee, std::vector<Boid*> &influencers) {
    ofVec2f desire;

    for (std::vector<Boid*>::iterator inf_it = influencers.begin(); inf_it != influencers.end(); ++inf_it) {
        ofVec2f direction = influencee->getPos() - (*inf_it)->getPos(); // Move away from the influencers
        float repulsion = 1 / influencee->getPos().squareDistance((*inf_it)->getPos()); // Proportionally to their nearness

        // repulsion will usually be smaller than 1 (equal to one for two boids one pixel apart). Therefore, a high
        // nearnessSelectivity will not increase repulsion that much for nearby boids, but instead reduce it greatly
        // for those that are far away.
        desire += direction.getNormalized() * powf(repulsion, nearnessSelectivity);
    }

    return desire;
}

// Alignment

std::string Alignment::getBehaviourName(void) {
    return "alignment";
}

ofVec2f Alignment::applyBehaviour(Boid *influencee, std::vector<Boid*> &influencers) {
    ofVec2f flockSpeed(0, 0);

    for (std::vector<Boid*>::iterator inf_it = influencers.begin(); inf_it != influencers.end(); ++inf_it) {
        flockSpeed += (*inf_it)->getSpeed();
    }

    return flockSpeed - influencee->getSpeed();
}

// Cohesion

std::string Cohesion::getBehaviourName(void) {
    return "cohesion";
}

ofVec2f Cohesion::applyBehaviour(Boid *influencee, std::vector<Boid*> &influencers) {
    ofVec2f flockCenter(0, 0);

    for (std::vector<Boid*>::iterator inf_it = influencers.begin(); inf_it != influencers.end(); ++inf_it) {
        flockCenter += (*inf_it)->getPos();
    }
    flockCenter /= influencers.size();

    return flockCenter - influencee->getPos();
}