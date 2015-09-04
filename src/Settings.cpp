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
    int numBoidTypes = xml.getNumTags("boids");
    for (int type_idx = 0; type_idx < numBoidTypes; ++type_idx) {
        std::string type_name = xml.getAttribute("boids", "type", "", type_idx);
        xml.pushTag("boids", type_idx);

        BoidTypeData typeData;
        typeData.amount = xml.getValue("amount", 100);
        typeData.maxDist = xml.getValue("maxDist", 100);
        typeData.period = xml.getValue("period", 1);

        boidType.insert(std::make_pair<BoidMisc::Type, BoidTypeData>(BoidMisc::TypenameToType(type_name), typeData));
        xml.popTag(); // exit boids
    }
}

int Settings::width;
int Settings::height;
int Settings::fps;

std::map<BoidMisc::Type, Settings::BoidTypeData> Settings::boidType;
