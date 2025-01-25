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

int main() {
    threepp::Canvas canvas{};
    threepp::GLRenderer renderer{canvas.size()};
    threepp::HUD hud(canvas.size());

    auto camera = threepp::PerspectiveCamera::create(60, canvas.aspect(), 0.01, 100);
    threepp::OrbitControls controls(*camera, canvas);

    Simulation sim = Simulation(canvas, renderer, camera, controls);
    sim.setupWindow([&]{ hud.setSize(canvas.size());});
    sim.setupDefaultScene();

    //FABRIK NaNs out when something out of reach
    auto solver = std::make_unique<CCD>();
    Crane crane = Crane(createSkeleton(4));
    crane.position.y = -2;
    sim.getScene().add(crane);

    threepp::Vector3 targetVec;
    Vector2 target = Vector2(0, 0.5f);
    Vector2 oldTarget;
    float accum = 0.0f;

    ImguiFunctionalContext ui(canvas.windowPtr(), [&] {
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

    threepp::IOCapture capture{};
    capture.preventMouseEvent = [] {
        return ImGui::GetIO().WantCaptureMouse;
    };
    canvas.setIOCapture(&capture);

    threepp::Clock clock;
    sim.update([&]{
        crane.moveTo(target, Z, *solver);
    });
}
