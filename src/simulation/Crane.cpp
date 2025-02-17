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

//TODO: Store axis of rotation in the the skellington
void Crane::solveAngles(const Vector2& pos, IKSolver& solver) const {
    solver.solve(*_skeleton, pos, maxIkIterations, posEpsilon);
}

void Crane::update(float const dt) {
    auto& bones = _skeleton->getBones();
    for (int i = 0; i < bones.size(); i++) {
        auto& b = bones[i];
        auto& child = _childChain[i];

        float ang = radLerp(child->rotation.z, b->angle, dt);
        child->setRotationFromAxisAngle(axisToVector(Z), ang);
    }

    //addTracerPoint(); //The stupid threepp line rendering doesnt work like expected
}

void Crane::addTracerPoint() {
    if(_childChain.empty() || tracer == nullptr) return;

    auto& endEffector = _childChain.back();
    threepp::Vector3 point = endEffector->position;
    endEffector->localToWorld(point);
    tracer->addPoint(point);
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
    _childChain[0]->position = position;
}

std::shared_ptr<threepp::Mesh> Crane::createMesh(const Bone &bone) {
    const float gWidth = 0.2f;
    auto material = threepp::MeshPhongMaterial::create();
    material->color = threepp::Color(0.3f, 0.3f, 0.4f);

    float height = bone.length;
    auto geometry = threepp::BoxGeometry::create(height, gWidth, gWidth);
    geometry->translate(height / 2.0f, 0, 0);
    auto m = threepp::Mesh::create(geometry, material);

    m->position.x += height;
    return m;
}

