#ifndef CCD3_HPP
#define CCD3_HPP

#include "IKSolver3.hpp"

class CCD3 : IKSolver3 {
    bool solve(std::array<Skeleton, 3> &skeletons, const threepp::Vector3 &targetPos, int maxIterations, float epsilon) override;
};

#endif //CCD3_HPP
