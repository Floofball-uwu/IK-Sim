#include "Skeleton.h"
#include "threepp/threepp.hpp"

#include "threepp/extras/imgui/ImguiContext.hpp"

int main() {

    threepp::Canvas canvas;
    threepp::GLRenderer renderer{canvas.size()};

    threepp::PerspectiveCamera camera(60, canvas.aspect(), 0.1, 1000);
    camera.position.z = 5;

    threepp::Scene scene;
    scene.background = threepp::Color(0.5f, 0.5f, 0.5f);

    ImguiFunctionalContext ui(canvas.windowPtr(), [&] {
        ImGui::SetNextWindowPos({}, 0, {});
               ImGui::SetNextWindowSize({230, 0}, 0);
               ImGui::Begin("Mesh settings");

               ImGui::End();
    });
    // ui.makeDpiAware(); // to increase imgui size on high DPI screens


    threepp::Clock clock;
    canvas.animate([&] {
        const auto dt = clock.getDelta();

        renderer.render(scene, camera);
        ui.render();
    });
}
