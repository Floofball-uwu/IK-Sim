#include "CCD3.hpp"

#include <array>

#include "CCD.h"

CCD3::CCD3() : IKSolver3() {
    _subSolver = CCD();
}

bool CCD3::solve(std::vector<Skeleton>& skeletons, const threepp::Vector3& targetPos, int maxIterations, float epsilon) override {
    std::vector<Vector2> planes = std::vector({Vector2(targetPos.x, targetPos.z), Vector2(targetPos.x, targetPos.y), Vector2(targetPos.y, targetPos.z)});

    bool positionReached = true;
    for(int i = 0; i < skeletons.size(); i++) {
        positionReached &= _subSolver.solve(skeletons[i], planes[i], maxIterations, epsilon);
    }
    return positionReached;
}
