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

//TODO: Add pivot children which are rotated instead of the meshes for ebtter visuals
void Crane::moveTo(const Vector2& pos, const Axis axis, IKSolver& solver) const {
    if(pos.length() > getMaxReach()) return;

    solver.solve(*_skeleton, pos, maxIkIterations, posEpsilon);
    auto& bones = _skeleton->getBones();
    for (int i = 0; i < bones.size(); i++) {
        auto& b = bones[i];
        threepp::Euler e;
        e.setFromVector3(axisToVector(axis) * b->angle);
        _childChain[i]->setRotationFromEuler(e);
    }
}

void Crane::parseIkData(const std::vector<float>& angles, const std::vector<Axis>& axis) {
    unsigned long long its = std::min(angles.size(), axis.size());
    for(int i = 0; i < its; i++) {
        Object3D* c = children[i];
        if(c == nullptr) continue;
        c->rotateOnAxis(axisToVector(axis[i]), angles[i]);
    }
}

void Crane::setupBoneMeshes(const std::vector<std::unique_ptr<Bone>>& bones) {
    _maxReach = 0.0f;
    Object3D* lastChild = this;
    for (const auto& bone : bones) {
        auto m = createMesh(*bone);
        lastChild->add(m);
        lastChild = m.get();
        _childChain.emplace_back(lastChild);
        _maxReach += bone->length;
    }
}

std::shared_ptr<threepp::Mesh> Crane::createMesh(const Bone &bone) {
    const float gWidth = 0.2f;
    auto material = threepp::MeshPhongMaterial::create();
    material->color = threepp::Color::grey;

    float height = bone.length;
    auto geometry = threepp::BoxGeometry::create(gWidth, height, gWidth);
    geometry->translate(0, height / 2.0f, 0);
    auto m = threepp::Mesh::create(geometry, material);

    m->position.y += height;
    return m;
}

