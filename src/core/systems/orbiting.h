#ifndef SB_SYSTEMS_ORIBITING
#define SB_SYSTEMS_ORIBITING

#include <chrono>
#include <entt/entt.hpp>

class OrbitingSystem {
private:
public:
  OrbitingSystem() = default;
  ~OrbitingSystem() = default;
  static void update(double time, entt::registry &registry);
};



#endif