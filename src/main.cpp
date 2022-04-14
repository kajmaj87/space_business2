#include "core/engine.h"
#include "ui/screen.h"
#include <chrono>

auto main() -> int {

  UIScreen uiScreen;

  Engine engine = Engine(uiScreen);
  std::thread game_loop([&engine]() { engine.loop(); });
  std::thread render_loop([&uiScreen]() { 
    while(true){
      using namespace std::chrono_literals;
      uiScreen.render(); 
      std::this_thread::sleep_for(100ms);
      // std::cout << "Render update";
    }
  });
  uiScreen.initialize(engine.get_registry());
  game_loop.join();

  return 0;
}