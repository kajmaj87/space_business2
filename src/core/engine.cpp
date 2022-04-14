#include "engine.h"
#include <chrono>

Engine::Engine(UIScreen &screen) {
  _screen = &screen;
  for (auto i = 0; i < 100; i++) {
    const auto planet = _registry.create();
    _registry.emplace<Position>(planet, 50, 50);
  }
}

void Engine::loop() {
  // 60 updates per second. We divide 1000 by 60 instead of 1 because sdl
  // operates on milliseconds not nanoseconds.
  const constexpr double dt = 1000.0;

  // This is a fixed-step gameloop.
  // See https://gafferongames.com/post/fix_your_timestep/
  // For an explanation.
  double time = 0.0;
  double accumulator = 0.0;
  auto current_time = std::chrono::high_resolution_clock::now();
  auto new_time = std::chrono::high_resolution_clock::now();
  while (true) {
    // new_time = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double, std::milli> frame_time =
    //     new_time - current_time;
    // current_time = new_time;

    // accumulator += frame_time.count();

    // while (accumulator >= dt) {
    //   update(accumulator);

    //   accumulator -= dt;
    //   time += dt;
    // }
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(100ms);
    update(1000);
    // std::cout << "Engine update";
  }
}

void Engine::update(double time) { OrbitingSystem::update(time, _registry); }
auto Engine::get_registry() -> entt::registry & { return _registry; }