#include "Boid.fwd.h"
#include <sstream>
#include <stdexcept>

static const std::string typenames[BoidMisc::LAST_TYPE - BoidMisc::FIRST_TYPE] = {
    [BoidMisc::REGULAR] = "regular",
    [BoidMisc::PREDATOR] = "predator",
};

const std::string& BoidMisc::typeToTypename(BoidMisc::Type type)
{
    if ((type >= BoidMisc::FIRST_TYPE) && (type < BoidMisc::LAST_TYPE)) {
        return typenames[type];
    } else {
        std::stringstream msg;
        msg << "BoidMisc::TypeToTypename: unknown type: " << type << std::endl;
        throw std::invalid_argument(msg.str());
    }
}

BoidMisc::Type BoidMisc::typenameToType(const std::string &type_name)
{
    for (int i = BoidMisc::FIRST_TYPE; i < BoidMisc::LAST_TYPE; ++i) {
        if (typenames[i] == type_name) {
            return (BoidMisc::Type) i;
        }
    }

    std::stringstream msg;
    msg << "BoidMisc::TypenameToType: unknown typename: " << type_name << std::endl;
    throw std::invalid_argument(msg.str());
}
