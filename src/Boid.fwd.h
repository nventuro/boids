#ifndef _BOID_FWD_H
#define _BOID_FWD_H

#include <string>

class Boid;

namespace BoidMisc {
    enum Type {
        REGULAR,
        PREDATOR
    };

    std::string typeToTypename(Type type);
    Type typenameToType(std::string type_name);
}

#endif // _BOID_FWD_H
