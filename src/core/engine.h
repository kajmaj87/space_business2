#ifndef SB_ENGINE
#define SB_ENGINE

#include "components.h"
#include "systems.h"

class Engine {
private:
  void prepareGame();
  void prepareScene();
  void registerListeners();

public:
  std::shared_ptr<entt::registry> registry;
  std::shared_ptr<entt::dispatcher> dispatcher;
  systems::UserInput _userInputSystem;
  Engine()
      : registry(std::make_shared<entt::registry>()),
        dispatcher(std::make_shared<entt::dispatcher>()),
        _userInputSystem(this->registry, this->dispatcher) {
    prepareGame();
    prepareScene();
    registerListeners();
  };
  ~Engine() = default;
  void loop();
  void update();
};

#endif