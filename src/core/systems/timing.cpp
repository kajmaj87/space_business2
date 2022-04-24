#include "timing.h"

void TimingSystem::init(entt::registry &registry) {
  registry.set<components::Time>(0, 2200, 1, 1, 0);
}

void TimingSystem::update(entt::registry &registry) {
  auto &time = registry.ctx<components::Time>();
  time.nextTick();
}