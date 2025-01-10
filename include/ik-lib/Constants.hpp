#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

//REMOVE IF NEEDED
#include <numbers>

namespace IkLib {
    //Replace as needed with whatever value system uses
    float PI = std::numbers::pi;

    enum Axis {
        X,
        Y,
        Z};
}

#endif //CONSTANTS_HPP
