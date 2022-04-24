#include "timing.h"

const auto SECONDS_EACH_TICK = 3600;
const unsigned long long START_DATE_IN_SECONDS = 230*365*24*60*60L;

void TimingSystem::init(entt::registry &registry) {
  registry.set<components::Time>(0, START_DATE_IN_SECONDS);
}

void TimingSystem::update(entt::registry &registry) {
  auto &time = registry.ctx<components::Time>();
  time.ticks++;
  time.seconds+=SECONDS_EACH_TICK;
}