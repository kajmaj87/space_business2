#include "engine.h"
#include <chrono>

Engine::Engine(UIScreen screen) {
  _screen = screen;
}

void Engine::loop() {
  // 60 updates per second. We divide 1000 by 60 instead of 1 because sdl
  // operates on milliseconds not nanoseconds.
  const constexpr double dt = 1000.0 / 60.0;

  // This is a fixed-step gameloop.
  // See https://gafferongames.com/post/fix_your_timestep/
  // For an explanation.
  double time = 0.0;
  double accumulator = 0.0;
  auto current_time = std::chrono::high_resolution_clock::now();
  auto new_time = std::chrono::high_resolution_clock::now();
  while (true) {
    new_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> frame_time =
        new_time - current_time;
    current_time = new_time;

    accumulator += frame_time.count();

    while (accumulator >= dt) {
      update(accumulator);

      accumulator -= dt;
      time += dt;
    }
    _screen.render();
  }
}

void Engine::update(double time) { _orbiting_system.update(time, _registry); }