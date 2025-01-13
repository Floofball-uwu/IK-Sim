#ifndef WRAPPERS_HPP
#define WRAPPERS_HPP

//REPLACE INCLUDE BASED OFF AVAILABILITY ON SYSTEM
#include <cmath>

namespace IkLib {
    float sqrt(float x) { return std::sqrt(x); };

    float sin(float x) { return std::sin(x); }
    float cos(float x) { return std::cos(x); }
    float tan(float x) { return std::tan(x); }

    float asin(float x) { return std::asin(x); }
    float acos(float x) { return std::acos(x); }
    float atan(float x) { return std::atan(x); }
	float atan2(float y, float x) { return std::atan2(y, x); }
}

#endif //WRAPPERS_HPP
