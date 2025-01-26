#include "Simulation.hpp"

Simulation::Simulation(){
    _scene = threepp::Scene::create();
    _canvas = std::make_unique<threepp::Canvas>();
    _renderer = std::make_unique<threepp::GLRenderer>(_canvas->size());

    _camera = std::make_unique<threepp::PerspectiveCamera>(60, _canvas->aspect(), 0.01, 100);
    _camera->position.z = 5.0f;
    _camera->lookAt({0, 1, 0});

    _controls = std::make_unique<threepp::OrbitControls>(*_camera, *_canvas);
    _scene = threepp::Scene::create();
    _hud = std::make_unique<threepp::HUD>(_canvas->size());
    setup();
}

std::shared_ptr<threepp::Scene> Simulation::getScene() {
    return _scene;
}

threepp::Canvas& Simulation::getCanvas() {
    return *_canvas;
}

void Simulation::setupUi(std::unique_ptr<ImguiFunctionalContext> imgui) {
    _imgui = std::move(imgui);

    _capture = std::make_unique<threepp::IOCapture>();
    _capture->preventMouseEvent = [] {
        return ImGui::GetIO().WantCaptureMouse;
    };
    _canvas->setIOCapture(_capture.get());
}

void Simulation::setup() {
    _scene->background = threepp::Color(0.5f, 0.5f, 0.5f);

    _canvas->onWindowResize([&](threepp::WindowSize size) {
        _camera->aspect = size.aspect();
        _camera->updateProjectionMatrix();
        _renderer->setSize(size);

        _hud->setSize(size);
    });

}

void Simulation::setupDefaultScene() {
    auto light = threepp::DirectionalLight::create({1.0f, 1.0f, 1.0f});
    light->position = {0, 10, 5};

    _scene->add(light);
}


void Simulation::update(std::function<void()> f) {
    _canvas->animate([&] {
        f();

        _renderer->render(*_scene, *_camera);
        _imgui->render();
    });
}
