#ifndef SB_SYSTEMS
#define SB_SYSTEMS

#include "components.h"
#include <entt/entt.hpp>

using namespace components;

namespace systems {
struct Orbiting {
  static void update(std::shared_ptr<entt::registry> &registry) {
    auto time = registry->ctx<Time>();
    auto orbit_view = registry->view<Position, Orbit>();
    orbit_view.each([&time, &registry](auto &position, auto &orbit) {
      const auto parentPosition = registry->get<Position>(orbit.orbitingAround);
      orbit.currentAngle +=
          2 * constants::math::PI * time.secondsLastTick() / orbit.period;
      position.x =
          std::sin(orbit.currentAngle) * orbit.radius + parentPosition.x;
      position.y =
          std::cos(orbit.currentAngle) * orbit.radius + parentPosition.y;
    });
  }
};

struct Timing {
  static void init(std::shared_ptr<entt::registry> &registry) {
    registry->set<Time>(Time{.year=2200, .month=1, .day=1, .hour=0, .minutes=0, .seconds=0, .updatesPerSecond=60, .currentSecondsPerTickIndex=4});
  }

  static void update(std::shared_ptr<entt::registry> &registry) {
    auto &time = registry->ctx<Time>();
    time.nextTick();
  }
};

struct UserInput {

  UserInput(std::shared_ptr<entt::registry> registry,
            std::shared_ptr<entt::dispatcher> dispatcher)
      : _registry(registry), _dispatcher(dispatcher){};

  void processKeyPress(events::key_pressed &key_pressed) {
    using namespace components;
    if (key_pressed.key == "q") {
      auto &state = _registry->ctx<GameState>();
      state.running = false;
    }
    if (key_pressed.key == "+") {
        auto &time = _registry->ctx<Time>();
        time.updatesPerSecond *= 2;
    }
    if (key_pressed.key == "-") {
        auto &time = _registry->ctx<Time>();
        if (time.updatesPerSecond > 1){
          time.updatesPerSecond /= 2;
        }
    }
    if (key_pressed.key == "]") {
        auto &time = _registry->ctx<Time>();
        time.increaseSecondsPerTick();
    }
    if (key_pressed.key == "[") {
        auto &time = _registry->ctx<Time>();
        time.decreaseSecondsPerTick();
    }
  }

  void update() { _dispatcher->update(); }

private:
  std::shared_ptr<entt::registry> _registry;
  std::shared_ptr<entt::dispatcher> _dispatcher;
};

} // namespace systems
#endif