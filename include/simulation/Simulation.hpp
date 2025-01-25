#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"

class Simulation {
public:
    Simulation(threepp::Canvas& canvas, threepp::GLRenderer& renderer, std::shared_ptr<threepp::PerspectiveCamera> camera, threepp::OrbitControls& controls);

    [[nodiscard]] threepp::Scene& getScene();

    void setupWindow(std::function<void()>);

    void setupUi();

    void setupDefaultScene();

    void update(std::function<void()> f);

private:
    threepp::Canvas& _canvas;
    threepp::GLRenderer& _renderer;
    threepp::Scene _scene;
    std::shared_ptr<threepp::PerspectiveCamera> _camera;
    threepp::OrbitControls& _controls;
    threepp::IOCapture _capture;
};

#endif //SIMULATION_HPP
