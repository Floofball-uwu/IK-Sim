#include <ik-algorithms-3d/CCD3.hpp>
#include <simulation/Simulation.hpp>
#include <simulation/Tracer.hpp>

#include "CCD.h"
#include "FABRIK.h"
#include "Skeleton.h"
#include "include/simulation/Crane.hpp"
#include "threepp/threepp.hpp"

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

    //FABRIK NaNs out when something out of reach
    auto solver = std::make_unique<CCD3>();
    Crane crane = Crane(createSkeleton(4));
    crane.position = {0, 0, 0};
    sim.getScene()->add(crane);
    sim.getScene()->add(createGrid());

    crane.tracer = std::make_shared<Tracer>();
    sim.getScene()->add(crane.tracer->getPathMesh());

    threepp::Vector3 targetVec;

    auto ui = std::make_unique<ImguiFunctionalContext>(sim.getCanvas().windowPtr(), [&] {
        ImGui::SetNextWindowPos({}, 0, {});
        ImGui::SetNextWindowSize({460, 0}, 0);
        ImGui::Begin("Mesh settings");

        if(ImGui::SliderFloat("X", &targetVec.x, crane.getMaxReach() + 5, -crane.getMaxReach() - 5)) {
            crane.solveAngles3(threepp::Vector3(targetVec.x, targetVec.y, targetVec.z), *solver);
        }

        if(ImGui::SliderFloat("Y", &targetVec.y, crane.getMaxReach() + 5, -crane.getMaxReach() - 5)) {
            crane.solveAngles3(threepp::Vector3(targetVec.x, targetVec.y, targetVec.z), *solver);
        }

        if(ImGui::SliderFloat("Z", &targetVec.z, crane.getMaxReach() + 5, -crane.getMaxReach() - 5)) {
            crane.solveAngles3(threepp::Vector3(targetVec.x, targetVec.y, targetVec.z), *solver);
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
