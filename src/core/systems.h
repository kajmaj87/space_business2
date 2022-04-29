#ifndef SB_SYSTEMS
#define SB_SYSTEMS

#include "components.h"
#include <entt/entt.hpp>

namespace systems {
struct Orbiting {
  static void update(std::shared_ptr<entt::registry> &registry) {
    using namespace components;
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
    registry->set<components::Time>(0, 2200, 1, 1, 0);
  }

  static void update(std::shared_ptr<entt::registry> &registry) {
    auto &time = registry->ctx<components::Time>();
    time.nextTick();
  }
};

struct UserInput {

  UserInput(std::shared_ptr<entt::registry> registry,
            std::shared_ptr<entt::dispatcher> dispatcher)
      : _registry(registry), _dispatcher(dispatcher){};

  void processKeyPress(events::key_pressed &key_pressed) {
    if (key_pressed.key == "q") {
      auto &state = _registry->ctx<components::GameState>();
      state.running = false;
    }
  }

  void update() { _dispatcher->update(); }

private:
  std::shared_ptr<entt::registry> _registry;
  std::shared_ptr<entt::dispatcher> _dispatcher;
};

} // namespace systems
#endif