#include "Behaviour.h"

#include "Boid.h"

#include <cmath>

// Base class

Behaviour::Behaviour(void) {
    weight = 1;
}

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

// Separation

Separation::Separation() {
    repulsionBoost = 1;
}

void Separation::setRepulsionBoost(int boost) {
    repulsionBoost = boost;
}

ofVec2f Separation::applyBehaviour(Boid *influencee, std::vector<Boid*> &influencers) {
    ofVec2f desire;

    for (std::vector<Boid*>::iterator inf_it = influencers.begin(); inf_it != influencers.end(); ++inf_it) {
        ofVec2f direction = influencee->getPos() - (*inf_it)->getPos(); // Move away from the influencers
        float repulsion = 1 / influencee->getPos().squareDistance((*inf_it)->getPos()); // Proportionally to their nearness
        desire += direction * powf(repulsion, repulsionBoost);
    }
    desire /= influencers.size();

    return desire;
}

// Alignment

ofVec2f Alignment::applyBehaviour(Boid *influencee, std::vector<Boid*> &influencers) {
    ofVec2f flockSpeed(0, 0);

    for (std::vector<Boid*>::iterator inf_it = influencers.begin(); inf_it != influencers.end(); ++inf_it) {
        flockSpeed += (*inf_it)->getSpeed();
    }
    flockSpeed /= influencers.size();

    return flockSpeed - influencee->getSpeed();
}

// Cohesion

ofVec2f Cohesion::applyBehaviour(Boid *influencee, std::vector<Boid*> &influencers) {
    ofVec2f flockCenter(0, 0);

    for (std::vector<Boid*>::iterator inf_it = influencers.begin(); inf_it != influencers.end(); ++inf_it) {
        flockCenter += (*inf_it)->getPos();
    }
    flockCenter /= influencers.size();

    return flockCenter - influencee->getPos();
}

// Cage

Cage::Cage() {
    threshold = 50;
}

void Cage::setThreshold(int threshold) {
    this->threshold = threshold;
}

ofVec2f Cage::applyBehaviour(Boid *influencee, std::vector<Boid*> &influencers) {
    // Cage limits (along with the lines correspoding to x = 0 and y = 0)
    int maxX = influencee->getMaxX();
    int maxY = influencee->getMaxY();

    // Threshold is assumed to be smaller than both maxX / 2 and maxY / 2

    float xDesire;

    if (influencee->getPos().x < threshold) {
        xDesire = 1 / influencee->getPos().x;
    }
    else if ((maxX - influencee->getPos().x) < threshold) {
        xDesire = -1 / (maxX - influencee->getPos().x);
    }
    else {
        xDesire = influencee->getAccel().x;
    }

    float yDesire;

    if (influencee->getPos().y < threshold) {
        yDesire = 1 / influencee->getPos().y;
    }
    else if ((maxY - influencee->getPos().y) < threshold) {
        yDesire = -1 / (maxY - influencee->getPos().y);
    }
    else {
        yDesire = influencee->getAccel().y;
    }

    return ofVec2f(xDesire, yDesire);
}

// Escape

ofVec2f Escape::applyBehaviour(Boid *influencee, std::vector<Boid*> &influencers) {
    ofVec2f desire(0, 0);

    int predatorCount = 0;
    for (std::vector<Boid*>::iterator inf_it = influencers.begin(); inf_it != influencers.end(); ++inf_it) {
        if ((*inf_it)->getType() == Boid::PREDATOR) {
            ++predatorCount;
            
            ofVec2f direction = influencee->getPos() - (*inf_it)->getPos(); // Move away from the predators
            float repulsion = 1 / influencee->getPos().distance((*inf_it)->getPos()); // Proportionally to their nearness
            desire += direction * repulsion;
        }
    }
    
    if (predatorCount == 0) {
        return influencee->getAccel();
    }
    else {
        desire /= predatorCount;

        return desire;
    }
}
