#include "screen.h"
#include "../core/components.h"
#include <fmt/chrono.h>
#include <fmt/core.h>
#include <string>

using namespace ftxui;
using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;

const auto TOP = 1, LEFT = 10, RIGHT = 20, BOTTOM = 5;

void UIScreen::initialize(entt::registry &registry) {

  auto middle = Renderer([&] {
    auto c = ftxui::Canvas(CANVAS_WITDH, CANVAS_HEIGHT);
    for (auto x = 0; x <= CANVAS_WITDH; x += GRID_SIZE) {
      for (auto y = 0; y <= CANVAS_HEIGHT; y += GRID_SIZE) {
        c.DrawPoint(x, y, true);
      }
    }
    auto view = registry.view<Position>();
    view.each([&](const auto &pos) {
      c.DrawPoint(std::round(pos.x), std::round(pos.y), true);
    });
    return canvas(std::move(c));
  });
  auto left = Renderer([] { return text("Left") | center; });
  auto right = Renderer([] { return text("right") | center; });
  auto top = Renderer([&] {
    auto &time = registry.ctx<components::Time>();
    0/0
    return text(fmt::format("{}.{:02}.{:02} {:02}:00", time.year, time.month,
                            time.day, time.hour)) |
           align_right;
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

  _screen.Loop(renderer);
}

void UIScreen::render() { _screen.PostEvent(Event::Custom); }