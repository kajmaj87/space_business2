#include "engine.h"
#include <thread>
#include <chrono>

using namespace components;

void Engine::prepareGame() {
  systems::Timing::init(registry);
  registry->set<GameState>(true);
  registry->set<TimeStats>(TimeStats{});
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
  auto lastSecondStart = std::chrono::high_resolution_clock::now();
  auto simulationSeconds = 0;
  while (registry->ctx<GameState>().running) {
    using namespace std::chrono_literals;
    using Clock = std::chrono::high_resolution_clock;
    auto frameStart = Clock::now();
    auto &timeStats = registry->ctx<TimeStats>();
    auto &time = registry->ctx<Time>();
    auto frameLength = std::chrono::nanoseconds{1000000000 / time.updatesPerSecond};
    update();
    auto frameEnd = Clock::now();
    auto timeSinceLastSecond = frameEnd - lastSecondStart;
    if (timeSinceLastSecond > 1s) {
      lastSecondStart = frameEnd;
      timeStats.simulationSpeed = simulationSeconds + time.secondsLastTick();
      if (timeStats.simulationSpeed > timeStats.bestSimulationSpeed) {
        timeStats.bestSimulationSpeed = timeStats.simulationSpeed;
      }
      simulationSeconds = 0;
    } else {
      simulationSeconds += time.secondsLastTick();
    }
    while (Clock::now() - frameStart < frameLength){
      // wait till we reach frametime
    }
  }
}

void Engine::update() {
  _userInputSystem.update();
  systems::Timing::update(registry);
  systems::Orbiting::update(registry);
}