#pragma once
//ADDED
#define _USE_MATH_DEFINES
//END

#include "IKSolver.h"

#include <numbers>
#include <cmath>
#include <cassert>

/// @brief Implementation of the Cyclic Coordinated Descend (CCD) algorithm for solving inverse kinematics
class CCD : public IKSolver
{
public:
	/// @brief Trys to set the end effector of the skeleton to the desired target position by rotating the bones of the skeleton
	virtual bool solve(Skeleton& skeleton, const Vector2& targetPos, int maxIterations, float epsilon) override
	{
		for (int i = 0; i < maxIterations; i++)
		{
			Bone* node = skeleton.pivotBone();

			// Adjust rotation of each bone in the skeleton
			while (node != nullptr)
			{
				Vector2 pivotPos = skeleton.pivotPosition();
				Vector2 currrentBasePos = skeleton.boneBasePosition(node);
				Vector2 basePivotVec = (pivotPos - currrentBasePos).normalize();
				Vector2 baseTargetVec = (targetPos - currrentBasePos).normalize();

                if(isnan(baseTargetVec.x())) baseTargetVec = Vector2(0, 0);

				float dot = basePivotVec.dot(baseTargetVec);
				float det = basePivotVec.cross(baseTargetVec);

                float rotateAngle = atan2(det, dot);

				node->angle = node->angle + rotateAngle;
				node = node->parent;
			}

			// Return if pivot is near enought to the target -> success
			if ((targetPos - skeleton.pivotPosition()).length() < epsilon)
				return true;
		}

		// Algorithm finished by reaching max Iterations -> pivot is not near enough to the target
		return false;
	}
};
