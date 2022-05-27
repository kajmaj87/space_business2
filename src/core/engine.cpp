#include "engine.h"
#include <thread>
#include <chrono>

using namespace components;
using namespace constants::physics;

void Engine::prepareGame() {
  systems::Timing::init(registry);
  registry->set<GameState>(true);
  registry->set<TimeStats>(TimeStats{});
  registry->set<Camera>(0,0, 1.0/(0.1_au));
}

void Engine::registerListeners() {
  dispatcher->sink<events::key_pressed>()
      .connect<&systems::UserInput::processKeyPress>(_userInputSystem);
  dispatcher->sink<events::mouse_drag>()
      .connect<&systems::UserInput::processMouseDrag>(_userInputSystem);
  dispatcher->sink<events::zoom>()
      .connect<&systems::UserInput::processZoom>(_userInputSystem);
}

void Engine::prepareScene() {
  const auto sun = registry->create();
  registry->emplace<Position>(sun, 0.0, 0.0);
  registry->emplace<Mass>(sun, 1.9885e30);
  const auto mercury = registry->create();
  const auto venus = registry->create();
  const auto moon = registry->create();
  const auto earth = registry->create();
  const auto mars = registry->create();
  const auto jupiter = registry->create();
  const auto saturn = registry->create();
  const auto uran = registry->create();
  const auto neptun = registry->create();
  using namespace constants::physics;
  registry->emplace<Position>(mercury, 0.0, 0.387098_au);
  registry->emplace<Mass>(mercury, 3.3011e23);
  registry->emplace<Orbit>(mercury, mercury, sun, registry);

  registry->emplace<Position>(venus, 0.0, 0.723332_au);
  registry->emplace<Mass>(venus, 4.8675e24);
  registry->emplace<Orbit>(venus, venus, sun, registry);

  registry->emplace<Position>(earth, 0.0, 1.0_au);
  registry->emplace<Mass>(earth, 5.97237e24);
  registry->emplace<Orbit>(earth, earth, sun, registry);

  registry->emplace<Position>(moon, 0.0, 1.00257_au);
  registry->emplace<Mass>(moon, 7.342e22);
  registry->emplace<Orbit>(moon, moon, earth, registry);

  registry->emplace<Position>(mars, 0.0, 1.52368055_au);
  registry->emplace<Mass>(mars, 6.4171e23);
  registry->emplace<Orbit>(mars, mars, sun, registry);

  registry->emplace<Position>(jupiter, 0.0, 5.2038_au);
  registry->emplace<Mass>(jupiter, 1.8982e27);
  registry->emplace<Orbit>(jupiter, jupiter, sun, registry);

  registry->emplace<Position>(saturn, 0.0, 9.5826_au);
  registry->emplace<Mass>(saturn, 5.6834e26);
  registry->emplace<Orbit>(saturn, saturn, sun, registry);

  registry->emplace<Position>(uran, 0.0, 19.19126_au);
  registry->emplace<Mass>(uran, 8.681e25);
  registry->emplace<Orbit>(uran, uran, sun, registry);

  registry->emplace<Position>(neptun, 0.0, 30.07_au);
  registry->emplace<Mass>(neptun, 1.02413e26);
  registry->emplace<Orbit>(neptun, neptun, sun, registry);
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
