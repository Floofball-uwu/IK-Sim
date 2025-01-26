#include <simulation/Simulation.hpp>

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
    auto solver = std::make_unique<CCD>();
    Crane crane = Crane(createSkeleton(4));
    crane.position = {0, 0, 0};
    sim.getScene()->add(crane);
    sim.getScene()->add(createGrid());

    threepp::Vector3 targetVec;
    Vector2 target = Vector2(0, 0.5f);
    Vector2 oldTarget;
    float accum = 0.0f;

    auto ui = std::make_unique<ImguiFunctionalContext>(sim.getCanvas().windowPtr(), [&] {
        ImGui::SetNextWindowPos({}, 0, {});
        ImGui::SetNextWindowSize({460, 0}, 0);
        ImGui::Begin("Mesh settings");

        if(ImGui::SliderFloat("X", &targetVec.x, crane.getMaxReach() + 5, -crane.getMaxReach() - 5)) {
            target = Vector2(targetVec.x, targetVec.y);
        }

        if(ImGui::SliderFloat("Y", &targetVec.y, crane.getMaxReach() + 5, -crane.getMaxReach() - 5)) {
            target = Vector2(targetVec.x, targetVec.y);
        }

        ImGui::SliderFloat("Z", &targetVec.z, crane.getMaxReach() + 5, -crane.getMaxReach() - 5);

        ImGui::End();
    });
    sim.setupUi(std::move(ui));

    threepp::Clock clock;
    sim.update([&] {
        const auto dt = clock.getDelta();

        crane.moveTo(target, Z, *solver);
    });
}
