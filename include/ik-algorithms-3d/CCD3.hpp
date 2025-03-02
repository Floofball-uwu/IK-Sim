#ifndef CCD3_HPP
#define CCD3_HPP

#include "CCD.h"
#include "IKSolver3.hpp"

class CCD3 : public IKSolver3 {
public:
    CCD3();
    bool solve(std::array<Skeleton, 3> &skeletons, const threepp::Vector3 &targetPos, int maxIterations, float epsilon) override;
};

#endif //CCD3_HPP
