#ifndef CRANE_HPP
#define CRANE_HPP

#include <ik-algorithms-3d/Skeleton3.hpp>

#include "Tracer.hpp"

#include "IKSolver.h"
#include "Utils.hpp"
#include "Skeleton.h"
#include "threepp/objects/Mesh.hpp"

class Crane : public threepp::Object3D{
public:
  std::shared_ptr<Tracer> tracer;

  Crane(const std::vector<std::shared_ptr<Bone3>> bones);

  void update(float const dt);

private:
  std::vector<std::shared_ptr<Bone3>> _bones;
  std::vector<std::shared_ptr<Object3D>> _childChain;

  void addTracerPoint();
  void setupBoneMeshes(const std::vector<std::shared_ptr<Bone3>>& bones);
  std::shared_ptr<threepp::Mesh> createMesh(const Bone3& bone);
};

#endif //CRANE_HPP
