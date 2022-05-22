#include "core/engine.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include "ui/screen.h"
#include <csignal>
#include <chrono>
#include <csignal>

void prepare_logger(){
  auto console_logger = spdlog::stderr_color_mt("console");
  auto file_logger = spdlog::basic_logger_st("file-logger", "game.log", true);
  spdlog::set_default_logger(file_logger);
  spdlog::set_pattern("[%H:%M:%S.%F] [thread %t] %v");
  spdlog::info("Game started");
  spdlog::info("Created file logger successfully");
}

auto main() -> int {
  UIScreen uiScreen;

  Engine engine = Engine();
  std::thread game_loop([&engine]() {
    engine.loop();
  });
  
  std::thread render_loop([&engine, &uiScreen]() {
    while (engine.registry->ctx<components::GameState>().running) {
      using namespace std::chrono_literals;
      uiScreen.render();
      std::this_thread::sleep_for(60ms);
    }
  });
  
  uiScreen.initialize(engine);
  engine.registry->ctx<GameState>().running = false;
  game_loop.join();
  render_loop.join();
  spdlog::info("Game exited");
  return 0;
}