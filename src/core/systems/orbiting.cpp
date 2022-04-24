#include "orbiting.h"
#include "../components/orbiter.h"
#include "../components/position.h"

void OrbitingSystem::update(entt::registry &registry) {
  auto orbit_view = registry.view<Position>();
  orbit_view.each([](auto &position) {
    position.x += rand() % 3 - 1;
    position.y += rand() % 3 - 1;
  });
}