#include "Boid.fwd.h"
#include <sstream>
#include <stdexcept>

std::string BoidMisc::TypeToTypename(BoidMisc::Type type) {
    if (type == BoidMisc::REGULAR) {
        return "regular";
    }
    else if (type == BoidMisc::PREDATOR) {
        return "predator";
    }
    else {
        std::stringstream msg;
        msg << "BoidMisc::TypeToTypename: unknown type: " << type << std::endl;
        throw std::invalid_argument(msg.str());
    }
}

BoidMisc::Type BoidMisc::TypenameToType(std::string type_name) {
    if (type_name == "regular") {
        return BoidMisc::REGULAR;
    }
    else if (type_name == "predator") {
        return BoidMisc::PREDATOR;
    }
    else {
        std::stringstream msg;
        msg << "BoidMisc::TypenameToType: unknown typename: " << type_name << std::endl;
        throw std::invalid_argument(msg.str());
    }
}