#include "engine.h"
#include <thread>
#include <chrono>

using namespace components;

void Engine::prepareGame() {
  systems::Timing::init(registry);
  registry->set<GameState>(true);
}

void Engine::registerListeners() {
  dispatcher->sink<events::key_pressed>()
      .connect<&systems::UserInput::processKeyPress>(_userInputSystem);
}

void Engine::prepareScene() {
  const auto sun = registry->create();
  registry->emplace<Position>(sun, 150.0, 50.0);
  registry->emplace<Mass>(sun, 1000.0);
  const auto mercury = registry->create();
  const auto moon = registry->create();
  const auto earth = registry->create();
  const auto jupiter = registry->create();
  const auto saturn = registry->create();
  registry->emplace<Position>(mercury, 150.0, 42.0);
  registry->emplace<Mass>(mercury, 0.2);
  registry->emplace<Orbit>(mercury, mercury, sun, registry);
  registry->emplace<Position>(earth, 150.0, 32.0);
  registry->emplace<Mass>(earth, 3.0);
  registry->emplace<Orbit>(earth, earth, sun, registry);
  registry->emplace<Position>(moon, 150.0, 30.0);
  registry->emplace<Mass>(moon, 0.5);
  registry->emplace<Orbit>(moon, moon, earth, registry);
  registry->emplace<Position>(jupiter, 150.0, 10.0);
  registry->emplace<Mass>(jupiter, 10.0);
  registry->emplace<Orbit>(jupiter, jupiter, sun, registry);
  registry->emplace<Position>(saturn, 150.0, 0.0);
  registry->emplace<Mass>(saturn, 10.0);
  registry->emplace<Orbit>(saturn, saturn, sun, registry);
}

void Engine::loop() {
  auto secondStart = std::chrono::system_clock::now();
  auto simulationSeconds = 0;
  auto& timeStats = registry->set<TimeStats>(TimeStats{.simulationSpeed = 0});
  while (registry->ctx<GameState>().running) {
    using namespace std::chrono_literals;
    auto &time = registry->ctx<Time>();
    auto frameLength = std::chrono::microseconds {1000000/time.updatesPerSecond};
    std::this_thread::sleep_for(frameLength);
    update();
    auto timeDiff = std::chrono::system_clock::now() - secondStart;
    if(timeDiff > 1s){
      secondStart = std::chrono::system_clock::now();
      timeStats.simulationSpeed = simulationSeconds;
      simulationSeconds = 0;
    } else {
      simulationSeconds += time.secondsLastTick();
    }
  }
}

void Engine::update() {
  _userInputSystem.update();
  systems::Timing::update(registry);
  systems::Orbiting::update(registry);
}