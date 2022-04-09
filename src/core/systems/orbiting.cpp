#include "orbiting.h"
#include "../components/orbiter.h"
#include "../components/position.h"

void OrbitingSystem::update(double time, entt::registry &registry) {
  auto orbit_view = registry.view<Position>();
  orbit_view.each([&time](auto &position) {
    position.x += time;
    position.y += time;
  });
}