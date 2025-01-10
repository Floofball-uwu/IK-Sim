#ifndef WRAPPERS_HPP
#define WRAPPERS_HPP

//REPLACE INCLUDE BASED OFF AVAILABILITY ON SYSTEM
#include <cmath>

namespace IkLib {
    float sin(float x) { return std::sin(x); }
    float cos(float x) { return std::cos(x); }
    float tan(float x) { return std::tan(x); }

}

#endif //WRAPPERS_HPP
