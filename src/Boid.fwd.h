#ifndef _BOID_FWD_H
#define _BOID_FWD_H

#include <string>

class Boid;

namespace BoidMisc {
    enum Type {
        FIRST_TYPE,
        REGULAR = FIRST_TYPE,
        PREDATOR,
        LAST_TYPE
    };

    const std::string& typeToTypename(Type type);
    Type typenameToType(const std::string &type_name);
}

#endif // _BOID_FWD_H
