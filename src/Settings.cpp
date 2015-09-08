#include "Settings.h"

#include "ofxXmlSettings.h"
#include <sstream>
#include <utility>

const std::string configFile = "config.xml";

void Settings::load(void) {
    ofxXmlSettings xml;
    if (!xml.loadFile(configFile)) {
        std::stringstream msg;
        msg << "Could not load configuration file at path " << configFile << std::endl;
        throw std::invalid_argument(msg.str());
    }

    xml.pushTag("config");

    width = xml.getValue("width", 1280);
    height = xml.getValue("height", 720);
    fps = xml.getValue("fps", 60);

    xml.pushTag("graphics");
    graphics.backgroundColor = Settings::stringToColor(xml.getValue("backgroundColor", "0, 0, 0"));
    xml.popTag(); // exit graphics

    boidsByType.clear();
    behavioursByType.clear();

    int numBoidTypes = xml.getNumTags("boids");
    for (int type_idx = 0; type_idx < numBoidTypes; ++type_idx) {
        BoidMisc::Type boid_type = BoidMisc::typenameToType(xml.getAttribute("boids", "type", "", type_idx));
        xml.pushTag("boids", type_idx);

        Settings::Boid type_data;
        type_data.amount = xml.getValue("amount", 100);
        type_data.maxDist = xml.getValue("maxDist", 100);
        type_data.period = xml.getValue("period", 1);
        type_data.maxSpeed = xml.getValue("maxSpeed", 8.0);

        xml.pushTag("graphics");
        type_data.graphics.color = Settings::stringToColor(xml.getValue("color", "0, 0, 0"));
        type_data.graphics.size = xml.getValue("size", 2);
        xml.popTag(); // exit graphics

        boidsByType.insert(std::make_pair(boid_type, type_data));

        // Behaviours for boids of this type
        std::vector<Settings::Behaviour> type_behaviours;
        int numBehaviours = xml.getNumTags("behaviour");
        for (int beh_idx = 0; beh_idx < numBehaviours; ++beh_idx) {
            xml.pushTag("behaviour", beh_idx);

            Settings::Behaviour behaviour_data;
            behaviour_data.typeName = xml.getValue("typeName", "");
            behaviour_data.weight = xml.getValue("weight", 1.0);
            behaviour_data.influencerType = BoidMisc::typenameToType(xml.getValue("influencerType", ""));

            // Separation
            behaviour_data.nearnessSelectivity = xml.getValue("nearnessSelectivity", 1.0);

            type_behaviours.push_back(behaviour_data);

            xml.popTag(); // exit behaviour
        }

        behavioursByType.insert(std::make_pair(boid_type, type_behaviours));

        xml.popTag(); // exit boids
    }
}

void Settings::save(void) {
    ofxXmlSettings xml;

    xml.addTag("config");
    xml.pushTag("config");

    xml.addValue("width", width);
    xml.addValue("height", height);
    xml.addValue("fps", fps);

    xml.addTag("graphics");
    xml.pushTag("graphics");
    xml.addValue("backgroundColor", colorToString(graphics.backgroundColor));
    xml.popTag(); // exit graphics

    for (auto &type_boid_pair : boidsByType) {
        int b_idx = xml.addTag("boids");
        xml.addAttribute("boids", "type", BoidMisc::typeToTypename(type_boid_pair.first), b_idx);
        xml.pushTag("boids", b_idx);

        xml.addValue("amount", type_boid_pair.second.amount);
        xml.addValue("maxDist", type_boid_pair.second.maxDist);
        xml.addValue("period", type_boid_pair.second.period);
        xml.addValue("maxSpeed", type_boid_pair.second.maxSpeed);

        xml.addTag("graphics");
        xml.pushTag("graphics");

        xml.addValue("color", colorToString(type_boid_pair.second.graphics.color));
        xml.addValue("size", type_boid_pair.second.graphics.size);

        xml.popTag(); // exit graphics

        // Check whether this boid type has behaviours
        auto &behaviours = behavioursByType[type_boid_pair.first];
        for (auto &behaviour : behaviours) {
            int beh_idx = xml.addTag("behaviour");
            xml.pushTag("behaviour", beh_idx);

            xml.addValue("typeName", behaviour.typeName);
            xml.addValue("weight", behaviour.weight);
            xml.addValue("influencerType", BoidMisc::typeToTypename(behaviour.influencerType));
            xml.addValue("nearnessSelectivity", behaviour.nearnessSelectivity);

            xml.popTag(); // exit the current behaviour
        }

        xml.popTag(); // exit the current boids
    }

    xml.save(configFile);
}

ofColor Settings::stringToColor(std::string str) {
    std::stringstream ss;
    ss << str;
    ofColor ret;
    ss >> ret;
    return ret;
}

std::string Settings::colorToString(ofColor color) {
    std::stringstream ss;
    ss << color;
    return ss.str();
}

int Settings::width;
int Settings::height;
int Settings::fps;
Settings::Graphics Settings::graphics;

std::map<BoidMisc::Type, Settings::Boid> Settings::boidsByType;
std::map<BoidMisc::Type, std::vector<Settings::Behaviour> > Settings::behavioursByType;
