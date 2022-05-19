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

  int left_size = LEFT;
  int right_size = RIGHT;
  int top_size = TOP;
  int bottom_size = BOTTOM;

  // totally reduced splitter gives -1
  auto canvas_width = [&]() {
    return _screen.dimx() - left_size - 1 - right_size - 1;
  };
  auto canvas_height = [&]() {
    return _screen.dimy() - top_size - 1 - bottom_size - 1;
  };
  auto inside_canvas = [&](int x, int y) {
    return x > (left_size + 1) * 2 &&
           x < (_screen.dimx() - right_size - 1) * 2 &&
           y > (top_size + 1) * 4 && y < (_screen.dimy() - bottom_size - 1) * 4;
  };

  auto middle = Renderer([&] {
    auto c = ftxui::Canvas(canvas_width() * 2, canvas_height() * 4);
    auto view = engine.registry->view<Position>();
    view.each([&](const auto &pos) {
      c.DrawPointOff(std::round(pos.x), std::round(pos.y));
      c.DrawPoint(std::round(pos.x), std::round(pos.y), true, Color::White);
    });
    return canvas(std::move(c));
  });
  auto left = Renderer([&] {
    return vbox(text("+ / - Change ticks per second (TPS)"),
                text("[ / ] Change seconds per tick (SPT)")) |
           center;
  });
  auto right = Renderer([&] {
    return vbox(
        text(fmt::format("({},{}): {}", mouse_x, mouse_y,
                         inside_canvas(mouse_x, mouse_y) ? "canvas"
                                                         : "nothing")) |
            center,
        text(fmt::format("{}, {}, {}, {}", left_size, right_size, top_size,
                         bottom_size)) |
            center,
        text(fmt::format("screen {}, {} ", _screen.dimx(), _screen.dimy())) |
            center,
        text(fmt::format("canvas size w:{}, h:{} ", canvas_width(),
                         canvas_height())) |
            center);
  });
  auto top = Renderer([&] {
    auto &time = engine.registry->ctx<Time>();
    auto &timeStats = engine.registry->ctx<TimeStats>();
    auto days = timeStats.simulationSpeed / 86400;
    auto rest = timeStats.simulationSpeed % 86400;
    return vbox(text(fmt::format("{}.{:02}.{:02} {:02}:{:02}", time.year,
                                 time.month, time.day, time.hour,
                                 time.minutes)) |
                    align_right,
                text(fmt::format(
                    "Game time advances {} days and {:%Hh%Mm%Ss} every second",
                    days, std::chrono::seconds{rest})),
                text(fmt::format("Efficiency: {:.3}%",
                                 100 * timeStats.simulationEfficiency(time))),
                text(fmt::format("Requested TPS: {}", time.updatesPerSecond)),
                text(fmt::format("Requested SPT: {}", time.secondsLastTick())),
                text(fmt::format("Requested Speed: {}X",
                                 time.updatesPerSecond *
                                     time.secondsLastTick())),
                text(fmt::format("Real Speed: {}X", timeStats.simulationSpeed)),
                text(fmt::format("Best Speed: {}X",
                                 timeStats.bestSimulationSpeed))) |
           align_right;
  });
  auto bottom = Renderer([] { return text("bottom") | center; });

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