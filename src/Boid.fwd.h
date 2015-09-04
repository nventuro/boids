#ifndef _BOID_FWD_H
#define _BOID_FWD_H

#include <string>

class Boid;

namespace BoidMisc {
    enum Type {
        REGULAR,
        PREDATOR
    };

    std::string TypeToTypename(Type type);
    Type TypenameToType(std::string type_name);
}

#endif // _BOID_FWD_H
