#include <cmath>
#include "orbiting.h"
#include "../constants.h"

void OrbitingSystem::update(entt::registry &registry) {
  using namespace components;
  auto time = registry.ctx<Time>();
  auto orbit_view = registry.view<Position, Orbit>();
  orbit_view.each([&time, &registry](auto &position, auto &orbit) {
    const auto parentPosition = registry.get<Position>(orbit.orbitingAround);
    orbit.currentAngle += 2 * constants::math::PI * time.secondsLastTick()/orbit.period;
    position.x = std::sin(orbit.currentAngle) * orbit.radius + parentPosition.x;
    position.y = std::cos(orbit.currentAngle) * orbit.radius + parentPosition.y;
  });
}