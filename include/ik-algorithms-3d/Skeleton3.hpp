#ifndef SKELETON3_HPP
#define SKELETON3_HPP

#pragma once

#include "Utils.hpp"
#include "threepp/math/Vector3.hpp"

#include <vector>

/// @brief Represents a bone in a skeleton
struct Bone3
{
    Bone3* parent = nullptr;
    Bone3* child = nullptr;
    float length = 1.0f;
    Axis axisOfRotation = X;
    float angle = 0.0f;
    float maxAngle = std::numeric_limits<float>::infinity();
    float minAngle = -std::numeric_limits<float>::infinity();
};

/// @brief A simple skeletal structure composed of a chain of bones
class Skeleton3
{
public:
    Skeleton3() = default;
    ~Skeleton3() = default;

    /// @brief Adds a bone at the end of the skeleton chain
    Skeleton3& addBone(float length, float angle, Axis axisOfRotation);

    /// @brief Gets all bones. ADDED FUNCTION
    const std::vector<std::unique_ptr<Bone3>>& getBones() const;

    /// @brief Returns the root bone of the skeleton
    Bone3* rootBone() { return m_root; }
    /// @brief Returns the last bone in the skeleton chain at the pivot
    Bone3* pivotBone() { return m_pivot; }

    /// @brief Returns the position at the base of bone
    threepp::Vector3 boneBasePosition(Bone3* bone);

    /// @brief Returns the pivot position of the last bone
    threepp::Vector3 pivotPosition();

    /// @brief Returns the count of bones
    size_t numOfBones() { return m_bones.size(); }

private:
    Bone3* m_root = nullptr;
    Bone3* m_pivot = nullptr;
    std::vector<std::unique_ptr<Bone3>> m_bones;
};


#endif //SKELETON3_HPP
