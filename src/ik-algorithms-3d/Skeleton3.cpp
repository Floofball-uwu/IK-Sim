#include "Skeleton3.hpp"

#include <iomanip>
#include <iostream>
#include <numbers>

#include "Utils.hpp"
#include "threepp/math/Euler.hpp"
#include "threepp/math/Vector3.hpp"

Skeleton3& Skeleton3::addBone(float length, float angle, Axis axisOfRotation)
{
    m_bones.emplace_back(std::make_unique<Bone3>(m_pivot, nullptr, length, axisOfRotation, angle));
    auto bone = m_bones.back().get();
    if (m_root == nullptr)
    {
        m_root = bone;
        m_pivot = bone;
    }
    else
    {
        m_pivot->child = bone;
        m_pivot = bone;
    }

    return *this;
}

const std::vector<std::unique_ptr<Bone3>>& Skeleton3::getBones() const {
    return m_bones;
}

//TODO
threepp::Vector3 Skeleton3::boneBasePosition(Bone3* node)
{
    auto currentBone = m_root;
    Axis currentAxis = X;
    threepp::Euler angleAccum = threepp::Euler();
    angleAccum.setOrder(threepp::Euler::XYZ);
    threepp::Vector3 basePosition{};
    while (currentBone != node && currentBone != nullptr)
    {
        currentAxis = currentBone->axisOfRotation;
        switch (currentAxis) {
            case X:
                angleAccum.x += currentBone->angle;
            break;
            case Y:
                angleAccum.y += currentBone->angle;
            break;
            case Z:
                angleAccum.z += currentBone->angle;
            break;
        }
        threepp::Vector3 v{};
        v.applyEuler(angleAccum);
        v *= currentBone->length;
        basePosition += v;
        currentBone = currentBone->child;
    }
    return basePosition;
}

threepp::Vector3 Skeleton3::pivotPosition()
{
    auto currentBone = m_root;
    Axis currentAxis = X;
    threepp::Euler angleAccum = threepp::Euler();
    threepp::Vector3 pivotPos{};
    while (currentBone != nullptr)
    {
        currentAxis = currentBone->axisOfRotation;
        switch (currentAxis) {
            case X:
                angleAccum.x += currentBone->angle;
            break;
            case Y:
                angleAccum.y += currentBone->angle;
            break;
            case Z:
                angleAccum.z += currentBone->angle;
            break;
        }
        threepp::Vector3 v{};
        v.applyEuler(angleAccum);
        v *= currentBone->length;
        pivotPos += v;
        currentBone = currentBone->child;
    }
    return pivotPos;
}
