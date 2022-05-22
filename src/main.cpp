#include "core/engine.h"
#include "ui/screen.h"
#include <csignal>
#include <chrono>

std::atomic_bool running = true;

auto main() -> int {
  UIScreen uiScreen;

  Engine engine = Engine();
  std::thread game_loop([&engine]() { 
    engine.loop(running); 
  });
  std::thread render_loop([&uiScreen]() { 
    while(running){
      using namespace std::chrono_literals;
      uiScreen.render(); 
      std::this_thread::sleep_for(60ms);
    }
  });
  
  uiScreen.initialize(engine);
  running = false;
  game_loop.join();
  render_loop.join();

  return 0;
}