#include "CCD3.hpp"

#include <array>

bool CCD3::solve(std::array<Skeleton, 3>& skeletons, const threepp::Vector3& targetPos, int maxIterations, float epsilon) override {
    std::array<Vector2,3 > planes = std::array({Vector2(targetPos.x, targetPos.z), Vector2(targetPos.x, targetPos.y), Vector2(targetPos.y, targetPos.z)});

    bool positionReached = true;
    for(int i = 0; i < skeletons.size(); i++) {
        positionReached &= _subSolver.solve(skeletons[i], planes[i], maxIterations, epsilon);
    }
    return positionReached;
}
