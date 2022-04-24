#ifndef SB_SYSTEMS_ORIBITING
#define SB_SYSTEMS_ORIBITING

#include <entt/entt.hpp>
#include "../components.h"

class OrbitingSystem {
private:
public:
  OrbitingSystem() = default;
  ~OrbitingSystem() = default;
  static void update(entt::registry &registry);
};



#endif