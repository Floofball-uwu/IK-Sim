#include "Crane.hpp"

#include "threepp/geometries/BoxGeometry.hpp"
#include "threepp/materials/MeshBasicMaterial.hpp"
#include "threepp/materials/MeshPhongMaterial.hpp"
#include "threepp/materials/MeshStandardMaterial.hpp"

Crane::Crane(const std::shared_ptr<Skeleton>& skeleton) : _skeleton(skeleton) {
    setupBoneMeshes(skeleton->getBones());
}

float Crane::getMaxReach() const {
    return _maxReach;
}

//TODO: Add pivot children which are rotated instead of the meshes for better visuals
void Crane::moveTo(const Vector2& pos, const Axis axis, IKSolver& solver) const {
    solver.solve(*_skeleton, pos, maxIkIterations, posEpsilon);
    auto& bones = _skeleton->getBones();
    for (int i = 0; i < bones.size(); i++) {
        auto& b = bones[i];
        _childChain[i]->setRotationFromAxisAngle(axisToVector(axis), b->angle);
    }
}

void Crane::setupBoneMeshes(const std::vector<std::unique_ptr<Bone>>& bones) {
    _maxReach = 0.0f;
    Object3D* lastChild = this;
    for (const auto& bone : bones) {
        auto m = createMesh(*bone);
        _childChain.emplace_back(m);
        lastChild->add(m);
        lastChild = m.get();
        _maxReach += bone->length;
    }
}

std::shared_ptr<threepp::Mesh> Crane::createMesh(const Bone &bone) {
    const float gWidth = 0.2f;
    auto material = threepp::MeshPhongMaterial::create();
    material->color = threepp::Color::grey;

    float height = bone.length;
    auto geometry = threepp::BoxGeometry::create(height, gWidth, gWidth);
    geometry->translate(height / 2.0f, 0, 0);
    auto m = threepp::Mesh::create(geometry, material);

    m->position.x += height;
    return m;
}

