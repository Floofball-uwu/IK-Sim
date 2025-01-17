#ifndef UTILS_HPP
#define UTILS_HPP
#include "threepp/core/Object3D.hpp"
#include "threepp/math/Vector3.hpp"

enum Axis {
        X,
        Y,
        Z};

static threepp::Vector3 axisToVector(Axis axis) {
        switch (axis) {
                default:
                        return threepp::Vector3(1, 0, 0);
                case Y:
                        return threepp::Vector3(0, 1, 0);
                case Z:
                        return threepp::Vector3(0, 0, 1);
        }
}

#endif //UTILS_HPP
