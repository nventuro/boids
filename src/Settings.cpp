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

    boidType.clear();
    behaviourType.clear();

    int numBoidTypes = xml.getNumTags("boids");
    for (int type_idx = 0; type_idx < numBoidTypes; ++type_idx) {
        BoidMisc::Type boid_type = BoidMisc::typenameToType(xml.getAttribute("boids", "type", "", type_idx));
        xml.pushTag("boids", type_idx);

        Settings::Boid typeData;
        typeData.amount = xml.getValue("amount", 100);
        typeData.maxDist = xml.getValue("maxDist", 100);
        typeData.period = xml.getValue("period", 1);
        typeData.maxSpeed = xml.getValue("maxSpeed", 8.0);

        xml.pushTag("graphics");
        typeData.graphics.color = Settings::stringToColor(xml.getValue("color", "0, 0, 0"));
        typeData.graphics.size = xml.getValue("size", 2);
        xml.popTag(); // exit graphics

        boidType.insert(std::make_pair(boid_type, typeData));

        // Behaviours for boids of this type
        std::vector<Settings::Behaviour> type_behaviours;
        int numBehaviours = xml.getNumTags("behaviour");
        for (int beh_idx = 0; beh_idx < numBehaviours; ++beh_idx) {
            xml.pushTag("behaviour", beh_idx);

            Settings::Behaviour beh;
            beh.typeName = xml.getValue("typeName", "");
            beh.weight = xml.getValue("weight", 1.0);
            beh.influencerType = BoidMisc::typenameToType(xml.getValue("influencerType", ""));

            // Separation
            beh.nearnessSelectivity = xml.getValue("nearnessSelectivity", 1.0);

            type_behaviours.push_back(beh);

            xml.popTag(); // exit behaviour
        }

        behaviourType.insert(std::make_pair(boid_type, type_behaviours));

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

    for (std::map<BoidMisc::Type, Settings::Boid>::iterator b_it = boidType.begin(); b_it != boidType.end(); ++b_it) {
        int b_idx = xml.addTag("boids");
        xml.addAttribute("boids", "type", BoidMisc::typeToTypename(b_it->first), b_idx);
        xml.pushTag("boids", b_idx);

        xml.addValue("amount", b_it->second.amount);
        xml.addValue("maxDist", b_it->second.maxDist);
        xml.addValue("period", b_it->second.period);
        xml.addValue("maxSpeed", b_it->second.maxSpeed);

        xml.addTag("graphics");
        xml.pushTag("graphics");

        xml.addValue("color", colorToString(b_it->second.graphics.color));
        xml.addValue("size", b_it->second.graphics.size);

        xml.popTag(); // exit graphics

        // Check whether this boid type has behaviours
        std::vector<Settings::Behaviour> &behaviours = behaviourType[b_it->first];
        for (std::vector<Settings::Behaviour>::iterator beh_it = behaviours.begin(); beh_it != behaviours.end(); ++beh_it) {
            int beh_idx = xml.addTag("behaviour");
            xml.pushTag("behaviour", beh_idx);

            xml.addValue("typeName", beh_it->typeName);
            xml.addValue("weight", beh_it->weight);
            xml.addValue("influencerType", BoidMisc::typeToTypename(beh_it->influencerType));
            xml.addValue("nearnessSelectivity", beh_it->nearnessSelectivity);

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

std::map<BoidMisc::Type, Settings::Boid> Settings::boidType;
std::map<BoidMisc::Type, std::vector<Settings::Behaviour> > Settings::behaviourType;
