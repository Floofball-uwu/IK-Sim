#ifndef LEG_HPP
#define LEG_HPP

#include <array>

#include "CCD3.hpp"
#include "Skeleton3.hpp"
#include "threepp/math/Vector3.hpp"

class Leg {
public:
    int maxIkIterations = 100;
    float posEpsilon = 0.0001f;

    /// Y        \n
    /// |   Z    \n
    /// | /      \n
    /// |_____X  \n
    /// @param skeletons 2D skeletons in the order of axis of rotations X, Y, Z
    Leg(const std::array<Skeleton, 3> skeletons);

    /// Moves the leg to a target position with a deviation for controllers.
    /// @param position Target position for leg
    /// @return Deviation from target
    threepp::Vector3 moveTo(const threepp::Vector3& position);

    //TODO
    [[nodiscard]] float getMaxReach() const;

private:
    std::array<Skeleton, 3> _skeletons;
    std::unique_ptr<CCD3> _solver;

    [[nodiscard]] threepp::Vector3 getEndEffectorPosition() const;

    bool solveIK(const threepp::Vector3& target, std::array<Skeleton, 3>& skeletons);
};

#endif //LEG_HPP
