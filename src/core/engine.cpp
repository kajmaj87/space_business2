#include "engine.h"
#include <thread>
#include <chrono>

void Engine::prepareGame() {
  systems::Timing::init(registry);
  registry->set<components::GameState>(true);
}

void Engine::registerListeners() {
  dispatcher->sink<events::key_pressed>()
      .connect<&systems::UserInput::processKeyPress>(_userInputSystem);
}

void Engine::prepareScene() {
  const auto sun = registry->create();
  registry->emplace<components::Position>(sun, 150.0, 50.0);
  registry->emplace<components::Mass>(sun, 1000.0);
  const auto mercury = registry->create();
  const auto moon = registry->create();
  const auto earth = registry->create();
  const auto jupiter = registry->create();
  const auto saturn = registry->create();
  registry->emplace<components::Position>(mercury, 150.0, 42.0);
  registry->emplace<components::Mass>(mercury, 0.2);
  registry->emplace<components::Orbit>(mercury, mercury, sun, registry);
  registry->emplace<components::Position>(earth, 150.0, 32.0);
  registry->emplace<components::Mass>(earth, 3.0);
  registry->emplace<components::Orbit>(earth, earth, sun, registry);
  registry->emplace<components::Position>(moon, 150.0, 30.0);
  registry->emplace<components::Mass>(moon, 0.5);
  registry->emplace<components::Orbit>(moon, moon, earth, registry);
  registry->emplace<components::Position>(jupiter, 150.0, 10.0);
  registry->emplace<components::Mass>(jupiter, 10.0);
  registry->emplace<components::Orbit>(jupiter, jupiter, sun, registry);
  registry->emplace<components::Position>(saturn, 150.0, 0.0);
  registry->emplace<components::Mass>(saturn, 10.0);
  registry->emplace<components::Orbit>(saturn, saturn, sun, registry);
}

void Engine::loop() {
  while (registry->ctx<components::GameState>().running) {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(24ms);
    update();
  }
}

void Engine::update() {
  _userInputSystem.update();
  systems::Timing::update(registry);
  systems::Orbiting::update(registry);
}