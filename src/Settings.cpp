#include "Settings.h"

#include "ofxXmlSettings.h"
#include <sstream>

const std::string configFile = "config.xml";

void Settings::load() {
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

    boidType.clear();
    behaviourType.clear();

    int numBoidTypes = xml.getNumTags("boids");
    for (int type_idx = 0; type_idx < numBoidTypes; ++type_idx) {
        BoidMisc::Type boid_type = BoidMisc::TypenameToType(xml.getAttribute("boids", "type", "", type_idx));
        xml.pushTag("boids", type_idx);

        Settings::Boid typeData;
        typeData.amount = xml.getValue("amount", 100);
        typeData.maxDist = xml.getValue("maxDist", 100);
        typeData.period = xml.getValue("period", 1);
        typeData.maxSpeed = xml.getValue("maxSpeed", 8.0);

        boidType.insert(std::make_pair<BoidMisc::Type, Settings::Boid> (boid_type, typeData));

        std::vector<Settings::Behaviour> type_behaviours;
        int numBehaviours = xml.getNumTags("behaviour");
        for (int beh_idx = 0; beh_idx < numBehaviours; ++beh_idx) {
            xml.pushTag("behaviour", beh_idx);

            Settings::Behaviour beh;
            beh.typeName = xml.getValue("typeName", "");
            beh.weight = xml.getValue("weight", 1.0);
            beh.influencerType = BoidMisc::TypenameToType(xml.getValue("influencerType", ""));

            // Separation
            beh.nearnessSelectivity = xml.getValue("nearnessSelectivity", 1.0);

            type_behaviours.push_back(beh);

            xml.popTag(); // exit behaviour
        }

        behaviourType.insert(std::make_pair<BoidMisc::Type, std::vector<Settings::Behaviour> > (boid_type, type_behaviours));

        xml.popTag(); // exit boids
    }
}

int Settings::width;
int Settings::height;
int Settings::fps;

std::map<BoidMisc::Type, Settings::Boid> Settings::boidType;
std::map<BoidMisc::Type, std::vector<Settings::Behaviour> > Settings::behaviourType;