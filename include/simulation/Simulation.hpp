#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"

class Simulation {
public:
    Simulation();

    [[nodiscard]] std::shared_ptr<threepp::Scene> getScene();
    [[nodiscard]] threepp::Canvas& getCanvas();

    void setupUi(std::unique_ptr<ImguiFunctionalContext> ui);
    void setupDefaultScene();

    void update(std::function<void()> f);

private:
    std::unique_ptr<threepp::Canvas> _canvas;
    std::unique_ptr<threepp::GLRenderer> _renderer;
    std::unique_ptr<threepp::PerspectiveCamera> _camera;
    std::unique_ptr<threepp::OrbitControls> _controls;
    std::unique_ptr<threepp::HUD> _hud;
    std::shared_ptr<threepp::Scene> _scene;

    std::unique_ptr<threepp::IOCapture> _capture;
    std::unique_ptr<ImguiFunctionalContext> _imgui;

    void setup();
    void setupWindow();
};

#endif //SIMULATION_HPP
