#include "Boid.h"

#include "ofMath.h"
#include "ofGraphics.h"
#include "Behaviour.h"

Boid::Boid(BoidMisc::Type type, const std::vector<Behaviour*> &behaviours):
    type(type), config(Config::boids_by_type[type]), behaviours(behaviours)
{
    id = getNextID();

    pos.x = ofRandom(Config::width);
    pos.y = ofRandom(Config::height);

    speed.x = ofRandom(-1, 1);
    speed.y = ofRandom(-1, 1);
    speed = speed.getNormalized() * (config.max_speed / 3);

    accel.x = 0;
    accel.y = 0;
}

void Boid::calculateUpdate(const std::vector<Boid> &flock)
{
    float sq_infl_max_dist = config.infl_max_dist * config.infl_max_dist;

    std::vector<const Boid*> nearby_boids;
    for (const auto &boid : flock) {
        if ((this->id != boid.getId()) && (this->pos.squareDistance(boid.getPos()) < sq_infl_max_dist)) {
            nearby_boids.push_back(&boid);
        }
    }

    next_accel = accel;
    for (const auto &behaviour : behaviours) {
        next_accel += behaviour->apply(this, nearby_boids);
    }
    next_accel /= behaviours.size() + 1; // +1 because we're also taking into account our old acceleration
}

void Boid::update(void)
{
    accel = next_accel;

    speed += accel;
    if (speed.length() > config.max_speed) {
        speed = speed.getNormalized() * config.max_speed;
    }

    pos += speed;

    // Horizontal wrap-around
    if (pos.x > Config::width) {
        pos.x -= Config::width;
    } else if (pos.x < 0) {
        pos.x += Config::width;
    }

    // Vertical wrap-around
    if (pos.y > Config::height) {
        pos.y -= Config::height;
    } else if (pos.y < 0) {
        pos.y += Config::height;
    }
}

void Boid::draw(void) const
{
    ofSetColor(config.graphics.color);
    ofDrawCircle(pos, config.graphics.size);
}

ofVec2f Boid::getPos(void) const
{
    return pos;
}

ofVec2f Boid::getSpeed(void) const
{
    return speed;
}

ofVec2f Boid::getAccel(void) const
{
    return accel;
}

BoidMisc::Type Boid::getType(void) const
{
    return type;
}

int Boid::getId(void) const
{
    return id;
}

int Boid::getNextID(void)
{
    return id_gen++;
}

int Boid::id_gen;
