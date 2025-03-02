#ifndef IKSOLVER3_HPP
#define IKSOLVER3_HPP

#include "IKSolver.h"
#include "Skeleton.h"
#include "threepp/math/Vector3.hpp"

class IKSolver3
{
public:
    IKSolver3() = default;
    virtual ~IKSolver3() = default;

    /// @brief Interface to solve the inverse kinematics problem
    /// @param skeletons The skeletons to solve, in the order of [XZ XY YZ] as the plane they move in
    /// @param targetPos The target position to reach
    /// @param maxIterations The maximum number of iterations to solve the problem
    /// @param epsilon The maximum deviation from the target position
    /// @return Returns true if the end effector is within epsilon from the target before max iterations are reached else returns false
    virtual bool solve(std::array<Skeleton, 3>& skeletons, const threepp::Vector3& targetPos, int maxIterations, float epsilon) = 0;

protected:
    std::unique_ptr<IKSolver> _subSolver;

};

#endif //IKSOLVER3_HPP
