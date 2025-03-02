#include "Leg.hpp"

#include <algorithm>

#include "Skeleton3.hpp"
#include "CCD.h"
#include "threepp/math/Vector2.hpp"
#include "threepp/math/Vector3.hpp"

Leg::Leg(const std::array<Skeleton, 3> skeletons) : _skeletons(skeletons){
    _solver = std::move(std::make_unique<CCD3>());
}

threepp::Vector3 Leg::moveTo(const threepp::Vector3& position) {
    solveIK(position, _skeletons);
    return getEndEffectorPosition() - position;
}

float Leg::getMaxReach() const {
    return 0;
}

//TODO Needs testing
threepp::Vector3 Leg::getEndEffectorPosition() const {
    threepp::Vector3 result = threepp::Vector3();

    Vector2 x = _skeletons[0].pivotPosition(); //YZ plane
    Vector2 y = _skeletons[1].pivotPosition(); //XZ plane
    Vector2 z = _skeletons[2].pivotPosition(); //XY plane

    result = {y.x() + z.x(), x.x() + z.y(), x.y() + y.y()};

    return result;
}

bool Leg::solveIK(const threepp::Vector3& target, std::array<Skeleton, 3>& skeletons) {
    //Solve first for YZ with atan2, then XZ with atan2, then 2D IK for XY limb
    bool result = false;

    /*float angle = atan2(target.y, target.z);
    yz.angle = std::ranges::clamp(angle, yz.minAngle, yz.maxAngle);
    result = yz.angleReachable(angle);

    angle = atan2(target.x, target.z);
    xz.angle = std::ranges::clamp(angle, xz.minAngle, xz.maxAngle);
    result = xz.angleReachable(angle);*/

    result &= _solver->solve(skeletons, target, maxIkIterations, posEpsilon);

    return result;
}
