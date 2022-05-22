#include "core/engine.h"
#include "ui/screen.h"
#include <csignal>
#include <chrono>

auto main() -> int {
  UIScreen uiScreen;

  Engine engine = Engine();
  std::thread game_loop([&engine]() { 
    engine.loop(); 
  });
  std::thread render_loop([&engine, &uiScreen]() { 
    while(engine.registry->ctx<GameState>().running){
      using namespace std::chrono_literals;
      uiScreen.render(); 
      std::this_thread::sleep_for(60ms);
    }
  });
  
  uiScreen.initialize(engine);
  engine.registry->ctx<GameState>().running = false;
  game_loop.join();
  render_loop.join();
  return 0;
}