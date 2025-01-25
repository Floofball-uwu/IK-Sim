#include "Simulation.hpp"

Simulation::Simulation(threepp::Canvas& canvas, threepp::GLRenderer &renderer, std::shared_ptr<threepp::PerspectiveCamera> camera,
                       threepp::OrbitControls &controls) : _canvas(canvas), _renderer(renderer), _camera(camera), _controls(controls) {
}

threepp::Scene& Simulation::getScene() {
    return _scene;
}


void Simulation::setupUi() {
    _capture.preventMouseEvent = [] {
        return ImGui::GetIO().WantCaptureMouse;
    };
    _canvas.setIOCapture(&_capture);
}

void Simulation::setupWindow(std::function<void()> f) {
    _canvas.onWindowResize([&](threepp::WindowSize size) {
        _camera->aspect = size.aspect();
        _camera->updateProjectionMatrix();
        _renderer.setSize(size);

        f();
    });

    auto camera = threepp::PerspectiveCamera::create(60, _canvas.aspect(), 0.01, 100);
    camera->position.z = 5;
}

void Simulation::setupDefaultScene() {
    _scene.background = threepp::Color(0.5f, 0.5f, 0.5f);
}


void Simulation::update(std::function<void()> f) {
    _canvas.animate([&] {
        f();

        _renderer.render(_scene, *_camera);
    });
}
