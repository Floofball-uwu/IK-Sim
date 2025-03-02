#include <ik-algorithms-3d/Skeleton3.hpp>

#include "CCD.h"
#include "FABRIK.h"
#include "Skeleton.h"

#include "simulation/Crane.hpp"
#include "simulation/Simulation.hpp"
#include "simulation/Tracer.hpp"

#include "threepp/threepp.hpp"
#include "ik-algorithms-3d/Leg.hpp"

#include "threepp/extras/imgui/ImguiContext.hpp"

std::shared_ptr<Skeleton> createSkeleton(int bones) {
    auto skeleton = std::make_shared<Skeleton>();
    for(int i = 0; i < bones; i++) {
        skeleton->addBone(1.0f, 0);
    }
    auto& b = skeleton->getBones();

    b[0]->maxAngle = threepp::math::PI;
    b[0]->minAngle = 0;

    b[1]->maxAngle = threepp::math::PI / 2;
    b[1]->minAngle = 0;

    b[2]->maxAngle = threepp::math::PI / 6;
    b[2]->minAngle = 0;

    b[3]->maxAngle = threepp::math::PI / 2;
    b[3]->minAngle = 0;

    return skeleton;
}

std::shared_ptr<Skeleton3> createSkeleton(int bones, Axis axis) {
    auto skeleton = std::make_shared<Skeleton3>();
    for(int i = 0; i < bones; i++) {
        skeleton->addBone(1.0f, 0, axis);
    }
    auto& b = skeleton->getBones();

    b[0]->maxAngle = threepp::math::PI;
    b[0]->minAngle = 0;

    b[1]->maxAngle = threepp::math::PI / 2;
    b[1]->minAngle = 0;

    b[2]->maxAngle = threepp::math::PI / 6;
    b[2]->minAngle = 0;

    b[3]->maxAngle = threepp::math::PI / 2;
    b[3]->minAngle = 0;

    return skeleton;
}

auto createGrid() {

    unsigned int size = 30;
    auto material = threepp::ShadowMaterial::create();
    auto plane = threepp::Mesh::create(threepp::PlaneGeometry::create(size, size), material);
    plane->rotation.x = -threepp::math::PI / 2;
    plane->receiveShadow = true;

    auto grid = threepp::GridHelper::create(size, size, threepp::Color::lawngreen);
    grid->rotation.x = threepp::math::PI / 2;
    plane->add(grid);

    return plane;
}

int main() {
    Simulation sim = Simulation();
    sim.setupDefaultScene();

    std::vector<std::shared_ptr<Bone3>> planeBones = {
        std::make_shared<Bone3>(nullptr, nullptr, 1, Axis::X, 0),
        std::make_shared<Bone3>(nullptr, nullptr, 1, Axis::Y, 0)
    };

    std::shared_ptr<Skeleton> skeleton = createSkeleton(4);
    Leg leg = Leg(planeBones[0], planeBones[1], skeleton);

    std::vector<std::shared_ptr<Bone3>> craneBones = planeBones;
    craneBones.insert(craneBones.end(), skeleton->getBones().begin(), skeleton->getBones().end());
    Crane crane = Crane(craneBones);

    crane.position = {0, 0, 0};
    sim.getScene()->add(crane);
    sim.getScene()->add(createGrid());

    crane.tracer = std::make_shared<Tracer>();
    sim.getScene()->add(crane.tracer->getPathMesh());

    threepp::Vector3 targetVec;

    float maxReach = 10;
    auto ui = std::make_unique<ImguiFunctionalContext>(sim.getCanvas().windowPtr(), [&] {
        ImGui::SetNextWindowPos({}, 0, {});
        ImGui::SetNextWindowSize({460, 0}, 0);
        ImGui::Begin("Mesh settings");

        if(ImGui::SliderFloat("X", &targetVec.x, maxReach, -maxReach)) {
            leg.moveTo(targetVec);
        }

        if(ImGui::SliderFloat("Y", &targetVec.y, maxReach, -maxReach)) {
            leg.moveTo(targetVec);
        }

        if(ImGui::SliderFloat("Z", &targetVec.z, maxReach, -maxReach)) {
            leg.moveTo(targetVec);
        }

        ImGui::End();
    });
    sim.setupUi(std::move(ui));

    threepp::Clock clock;
    sim.update([&] {
        const auto dt = clock.getDelta();

        crane.update(dt * 4);
    });
}
