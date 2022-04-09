#ifndef SB_ENGINE
#define SB_ENGINE

#include "../ui/screen.h"
#include "components/position.h"
#include "systems/orbiting.h"

class Engine {
private:
  OrbitingSystem _orbiting_system;
  entt::registry _registry;
public:

  UIScreen *_screen;
  explicit Engine(UIScreen &screen);
  ~Engine() = default;
  void loop();
  void update(double time);
};

#endif