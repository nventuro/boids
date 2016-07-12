#include "Config.h"

#include "ofxXmlSettings.h"
#include <sstream>
#include <utility>

const std::string configFile = "config.xml";

void Config::load(void)
{
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
    graphics.bkgnd_color = Config::stringToColor(xml.getValue("bkgnd_color", "0, 0, 0"));
    xml.popTag(); // exit graphics

    boids_by_type.clear();
    behaviours_by_type.clear();

    int numBoidTypes = xml.getNumTags("boids");
    for (int type_idx = 0; type_idx < numBoidTypes; ++type_idx) {
        BoidMisc::Type boid_type = BoidMisc::typenameToType(xml.getAttribute("boids", "type", "", type_idx));
        xml.pushTag("boids", type_idx);

        Config::Boid type_data;
        type_data.amount = xml.getValue("amount", 100);
        type_data.infl_max_dist = xml.getValue("infl_max_dist", 100);
        type_data.period = xml.getValue("period", 1);
        type_data.max_speed = xml.getValue("max_speed", 8.0);

        xml.pushTag("graphics");
        type_data.graphics.color = Config::stringToColor(xml.getValue("color", "0, 0, 0"));
        type_data.graphics.size = xml.getValue("size", 2);
        type_data.graphics.draw_head = xml.getValue("draw_head", true);
        xml.popTag(); // exit graphics

        boids_by_type.insert(std::make_pair(boid_type, type_data));

        // Behaviours for boids of this type
        std::vector<Config::Behaviour> type_behaviours;
        int numBehaviours = xml.getNumTags("behaviour");
        for (int beh_idx = 0; beh_idx < numBehaviours; ++beh_idx) {
            xml.pushTag("behaviour", beh_idx);

            Config::Behaviour behaviour_data;
            behaviour_data.type_name = xml.getValue("type_name", "");
            behaviour_data.weight = xml.getValue("weight", 1.0);
            behaviour_data.influencer_type = BoidMisc::typenameToType(xml.getValue("influencer_type", ""));

            // Separation
            behaviour_data.nearness_selectivity = xml.getValue("nearness_selectivity", 1.0);

            type_behaviours.push_back(behaviour_data);

            xml.popTag(); // exit behaviour
        }

        behaviours_by_type.insert(std::make_pair(boid_type, type_behaviours));

        xml.popTag(); // exit boids
    }
}

void Config::save(void)
{
    ofxXmlSettings xml;

    xml.addTag("config");
    xml.pushTag("config");

    xml.addValue("width", width);
    xml.addValue("height", height);
    xml.addValue("fps", fps);

    xml.addTag("graphics");
    xml.pushTag("graphics");
    xml.addValue("bkgnd_color", colorToString(graphics.bkgnd_color));
    xml.popTag(); // exit graphics

    for (auto &type_boid_pair : boids_by_type) {
        int b_idx = xml.addTag("boids");
        xml.addAttribute("boids", "type", BoidMisc::typeToTypename(type_boid_pair.first), b_idx);
        xml.pushTag("boids", b_idx);

        xml.addValue("amount", type_boid_pair.second.amount);
        xml.addValue("infl_max_dist", type_boid_pair.second.infl_max_dist);
        xml.addValue("period", type_boid_pair.second.period);
        xml.addValue("max_speed", type_boid_pair.second.max_speed);

        xml.addTag("graphics");
        xml.pushTag("graphics");

        xml.addValue("color", colorToString(type_boid_pair.second.graphics.color));
        xml.addValue("size", type_boid_pair.second.graphics.size);
        xml.addValue("draw_head", type_boid_pair.second.graphics.draw_head);

        xml.popTag(); // exit graphics

        // Check whether this boid type has behaviours
        auto &behaviours = behaviours_by_type[type_boid_pair.first];
        for (auto &behaviour : behaviours) {
            int beh_idx = xml.addTag("behaviour");
            xml.pushTag("behaviour", beh_idx);

            xml.addValue("type_name", behaviour.type_name);
            xml.addValue("weight", behaviour.weight);
            xml.addValue("influencer_type", BoidMisc::typeToTypename(behaviour.influencer_type));
            xml.addValue("nearness_selectivity", behaviour.nearness_selectivity);

            xml.popTag(); // exit the current behaviour
        }

        xml.popTag(); // exit the current boids
    }

    xml.save(configFile);
}

ofColor Config::stringToColor(std::string str)
{
    std::stringstream ss;
    ss << str;
    ofColor ret;
    ss >> ret;
    return ret;
}

std::string Config::colorToString(ofColor color)
{
    std::stringstream ss;
    ss << color;
    return ss.str();
}

int Config::width;
int Config::height;
int Config::fps;
Config::Graphics Config::graphics;

std::map<BoidMisc::Type, Config::Boid> Config::boids_by_type;
std::map<BoidMisc::Type, std::vector<Config::Behaviour> > Config::behaviours_by_type;
