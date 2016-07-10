#include "Behaviour.h"

#include "Boid.h"

#include <cmath>
#include <stdexcept>

// Base class

Behaviour::Behaviour(void)
{
    weight = 1;
    influencerType = BoidMisc::REGULAR;
}

Behaviour* Behaviour::createFromName(std::string behaviour_name)
{
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

Behaviour::~Behaviour(void)
{
}

void Behaviour::setWeight(float weight)
{
    this->weight = weight;
}

void Behaviour::setInfluencerType(BoidMisc::Type type)
{
    influencerType = type;
}

BoidMisc::Type Behaviour::getInfluencerType(void)
{
    return influencerType;
}

ofVec2f Behaviour::apply(const Boid *influencee, const std::vector<const Boid*> &influencers)
{
    if (influencers.size() == 0) {
        return influencee->getAccel(); // No influencers, do the same thing we were doing
    }
    else {
        return applyBehaviour(influencee, influencers) * weight;
    }
}

// Separation

Separation::Separation(void)
{
    nearness_selectivity = 1;
}

std::string Separation::getBehaviourName(void)
{
    return "separation";
}

void Separation::setNearnessSelectivity(float selectivity)
{
    nearness_selectivity = selectivity;
}

ofVec2f Separation::applyBehaviour(const Boid *influencee, const std::vector<const Boid*> &influencers)
{
    ofVec2f desire;

    for (const auto &influencer : influencers) {
        ofVec2f direction = influencee->getPos() - influencer->getPos(); // Move away from the influencers
        float repulsion = 1 / influencee->getPos().squareDistance(influencer->getPos()); // Proportionally to their nearness

        // repulsion will usually be smaller than 1 (equal to one for two boids one pixel apart). Therefore, a high
        // nearness_selectivity will not increase repulsion that much for nearby boids, but instead reduce it greatly
        // for those that are far away.
        desire += direction.getNormalized() * powf(repulsion, nearness_selectivity);
    }

    return desire;
}

// Alignment

std::string Alignment::getBehaviourName(void)
{
    return "alignment";
}

ofVec2f Alignment::applyBehaviour(const Boid *influencee, const std::vector<const Boid*> &influencers)
{
    ofVec2f flockSpeed(0, 0);

    for (const auto &influencer : influencers) {
        flockSpeed += influencer->getSpeed();
    }

    return flockSpeed - influencee->getSpeed();
}

// Cohesion

std::string Cohesion::getBehaviourName(void)
{
    return "cohesion";
}

ofVec2f Cohesion::applyBehaviour(const Boid *influencee, const std::vector<const Boid*> &influencers)
{
    ofVec2f flockCenter(0, 0);

    for (const auto &influencer : influencers) {
        flockCenter += influencer->getPos();
    }
    flockCenter /= influencers.size();

    return flockCenter - influencee->getPos();
}
