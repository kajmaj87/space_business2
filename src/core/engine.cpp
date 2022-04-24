#include "engine.h"
#include <chrono>

Engine::Engine(UIScreen &screen) {
  TimingSystem::init(_registry);
  _screen = &screen;
  const auto sun = _registry.create();
  _registry.emplace<components::Position>(sun, 150.0, 100.0);
  _registry.emplace<components::Mass>(sun, 1000.0);
  const auto mercury = _registry.create();
  const auto earth = _registry.create();
  const auto jupiter = _registry.create();
  _registry.emplace<components::Position>(mercury, 150.0, 90.0);
  _registry.emplace<components::Mass>(mercury, 0.1);
  _registry.emplace<components::Orbit>(mercury, mercury, sun, _registry);
  _registry.emplace<components::Position>(earth, 150.0, 50.0);
  _registry.emplace<components::Mass>(earth, 1.0);
  _registry.emplace<components::Orbit>(earth, earth, sun, _registry);
  _registry.emplace<components::Position>(jupiter, 150.0, 10.0);
  _registry.emplace<components::Mass>(jupiter, 10.0);
  _registry.emplace<components::Orbit>(jupiter, jupiter, sun, _registry);
}

void Engine::loop() {
  while (true) {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(4ms);
    update();
  }
}

void Engine::update() { 
  TimingSystem::update(_registry);
  OrbitingSystem::update(_registry); 
}
auto Engine::get_registry() -> entt::registry & { return _registry; }