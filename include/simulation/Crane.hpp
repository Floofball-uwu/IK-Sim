#ifndef CRANE_HPP
#define CRANE_HPP

#include "IKSolver.h"
#include "Utils.hpp"
#include "Skeleton.h"
#include "threepp/objects/Mesh.hpp"

class Crane : public threepp::Object3D{
public:
  float posEpsilon = 0.5f;
  int maxIkIterations = 10;

  Crane(const std::shared_ptr<Skeleton>& skeleton);

  float getMaxReach() const;
  void moveTo(const Vector2& pos, const Axis axis, IKSolver& solver) const;

  /// Sets rotation of each bone appropriately, one by one, around the determined axis
  void parseIkData(const std::vector<float>& angles, const std::vector<Axis>& axis);

private:
  float _maxReach = 0.0f;
  std::shared_ptr<Skeleton> _skeleton;
  std::vector<std::shared_ptr<Object3D>> _childChain;
  void setupBoneMeshes(const std::vector<std::unique_ptr<Bone>>& bones);
  std::shared_ptr<threepp::Mesh> createMesh(const Bone& bone);
};

#endif //CRANE_HPP
