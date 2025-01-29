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

static float radLerp(double from, double target, float t) {
    float CS = (1 - t) * std::cos(from) + t * std::cos(target);
    float SN = (1 - t) * std::sin(from) + t * std::sin(target);
    return std::atan2(SN, CS);
}

#endif //UTILS_HPP
