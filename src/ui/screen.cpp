#include "screen.h"
#include "../core/components.h"
#include <fmt/chrono.h>
#include <fmt/core.h>
#include <string>

using namespace ftxui;
using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;

const auto TOP = 2, LEFT = 0, RIGHT = 20, BOTTOM = 5;

void UIScreen::initialize(Engine &engine) {
  using namespace components;
  int mouse_x = 0;
  int mouse_y = 0;

  auto middle = Renderer([&] {
    auto c = ftxui::Canvas(CANVAS_WITDH, CANVAS_HEIGHT);
    auto view = engine.registry->view<Position>();
    view.each([&](const auto &pos) {
      c.DrawPointOff(std::round(pos.x), std::round(pos.y));
      c.DrawPoint(std::round(pos.x), std::round(pos.y), true, Color::White);
    });

    return canvas(std::move(c));
  });
  auto left = Renderer([&] {
    return vbox(
                text("+ / - Change ticks per second (TPS)"),
                text("[ / ] Change seconds per tick (SPT)")) | center;
  });
  auto right = Renderer([&] { return text(fmt::format("({},{}): {}", mouse_x, mouse_y, "nothing")) | center; });
  auto top = Renderer([&] {
    auto &time = engine.registry->ctx<Time>();
    auto &timeStats = engine.registry->ctx<TimeStats>();
    auto days = timeStats.simulationSpeed / 86400;
    auto rest = timeStats.simulationSpeed % 86400;
    return vbox(text(fmt::format("{}.{:02}.{:02} {:02}:{:02}", time.year, time.month,
                            time.day, time.hour, time.minutes)) | align_right,
                text(fmt::format("Game time advances {} days and {:%Hh%Mm%Ss} every second", days, std::chrono::seconds{rest})),
                text(fmt::format("Efficiency: {:.3}%", 100*timeStats.simulationEfficiency(time))),
                text(fmt::format("Requested TPS: {}", time.updatesPerSecond)),
                text(fmt::format("Requested SPT: {}", time.secondsLastTick())),
                text(fmt::format("Requested Speed: {}X", time.updatesPerSecond * time.secondsLastTick())),
                text(fmt::format("Real Speed: {}X", timeStats.simulationSpeed)),
                text(fmt::format("Best Speed: {}X", timeStats.bestSimulationSpeed))
                ) | align_right;
  });
  auto bottom = Renderer([] { return text("bottom") | center; });

  int left_size = LEFT;
  int right_size = RIGHT;
  int top_size = TOP;
  int bottom_size = BOTTOM;

  auto container = middle;
  container = ResizableSplitLeft(left, container, &left_size);
  container = ResizableSplitRight(right, container, &right_size);
  container = ResizableSplitTop(top, container, &top_size);
  container = ResizableSplitBottom(bottom, container, &bottom_size);

  auto renderer =
      Renderer(container, [&] { return container->Render() | border; });

  renderer = CatchEvent(renderer, [&](Event event) {
    if (event.is_character()) {
      engine.dispatcher->enqueue<events::key_pressed>(event.character());
    }
    if (event.is_mouse()) {
      mouse_x = event.mouse().x * 2;
      mouse_y = event.mouse().y * 4;
    }
    return false;
  });
  _screen.Loop(renderer);
}

void UIScreen::render() { _screen.PostEvent(Event::Custom); }