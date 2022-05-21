#include "core/engine.h"
#include "ui/screen.h"
#include <csignal>
#include <chrono>

std::atomic<bool> running = true;
std::function<void()> shutdown_handler;
void signal_handler(int signal) {
    shutdown_handler();
}

auto main() -> int {
  UIScreen uiScreen;

    signal(SIGINT, signal_handler);
  Engine engine = Engine();
  std::thread game_loop([&engine, &uiScreen]() { 
    // signal(SIGINT, signal_handler);
    engine.loop(running); 
    printf("Engine loop exited");
    // uiScreen.exit();
  });
  std::thread render_loop([&engine, &uiScreen]() { 
    // signal(SIGINT, signal_handler);
    while(running){
      using namespace std::chrono_literals;
      uiScreen.render(); 
      std::this_thread::sleep_for(60ms);
    }
    printf("Render loop exited");
  });
  
  shutdown_handler = [&engine, &uiScreen](){
    //  printf("Recieved interrupt signal");
    //  engine.registry->ctx<GameState>().running = false; 
     running = false;
     uiScreen.exit();
  };
  uiScreen.initialize(engine);
  game_loop.join();
  render_loop.join();
  printf("Main exited");

  return 0;
}