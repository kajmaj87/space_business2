#include "engine.h"
#include <chrono>

Engine::Engine(UIScreen &screen) {
  TimingSystem::init(_registry);
  _screen = &screen;
  for (auto i = 0; i < 100; i++) {
    const auto planet = _registry.create();
    _registry.emplace<Position>(planet, 50, 50);
  }
}

void Engine::loop() {
  while (true) {
    using namespace std::chrono_literals;
    // std::this_thread::sleep_for(42ms);
    update();
  }
}

void Engine::update() { 
  TimingSystem::update(_registry);
  OrbitingSystem::update(_registry); 
}
auto Engine::get_registry() -> entt::registry & { return _registry; }