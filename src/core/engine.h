#ifndef SB_ENGINE
#define SB_ENGINE

#include "../ui/screen.h"
#include "components.h"
#include "systems/orbiting.h"
#include "systems/timing.h"

class Engine {
private:
  entt::registry _registry;
public:
  UIScreen *_screen;
  explicit Engine(UIScreen &screen);
  ~Engine() = default;
  void loop();
  void update();
  auto get_registry() -> entt::registry&;
};

#endif