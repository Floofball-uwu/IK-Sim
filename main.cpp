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

    threepp::Canvas canvas;
    threepp::GLRenderer renderer{canvas.size()};

    threepp::PerspectiveCamera camera(60, canvas.aspect(), 0.1, 1000);
    camera.position.z = 5;

    threepp::OrbitControls controls(camera, canvas);

    threepp::Scene scene;
    scene.background = threepp::Color(0.5f, 0.5f, 0.5f);

    ImguiFunctionalContext ui(canvas.windowPtr(), [&] {
        ImGui::SetNextWindowPos({}, 0, {});
               ImGui::SetNextWindowSize({230, 0}, 0);
               ImGui::Begin("Mesh settings");

               ImGui::End();
    });
    // ui.makeDpiAware(); // to increase imgui size on high DPI screens

    //FABRIK NaNs out when something out of reach
    auto solver = std::make_unique<CCD>();
    Crane crane = Crane(createSkeleton(4));
    crane.position.y = -2;
    scene.add(crane);

    Vector2 target = Vector2(1, 0.5f);
    float accum = 0.0f;

    threepp::Clock clock;
    canvas.animate([&] {
        const auto dt = clock.getDelta();

        accum += dt;
        target += Vector2(2*std::sin(4*accum), 0) * dt;
        crane.moveTo(target, X, *solver);

        renderer.render(scene, camera);
        ui.render();
    });
}
