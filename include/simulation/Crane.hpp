#ifndef CRANE_HPP
#define CRANE_HPP

#include "IKSolver.h"
#include "Utils.hpp"
#include "Skeleton.h"
#include "threepp/objects/Mesh.hpp"

class Crane : public threepp::Object3D{
public:
  float posEpsilon = 0.001f;
  int maxIkIterations = 100;

  Crane(const std::shared_ptr<Skeleton>& skeleton);

  float getMaxReach() const;
  void solveAngles(const Vector2& pos, IKSolver& solver) const;
  void update(float const dt);

private:
  float _maxReach = 0.0f;
  std::shared_ptr<Skeleton> _skeleton;
  std::vector<std::shared_ptr<Object3D>> _childChain;
  void setupBoneMeshes(const std::vector<std::unique_ptr<Bone>>& bones);
  std::shared_ptr<threepp::Mesh> createMesh(const Bone& bone);
};

#endif //CRANE_HPP
