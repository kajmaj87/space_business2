#include "screen.h"
#include "../core/components.h"
#include <fmt/chrono.h>
#include <fmt/core.h>
#include <string>

using namespace ftxui;
using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;

const auto TOP = 1, LEFT = 10, RIGHT = 20, BOTTOM = 5;

void UIScreen::initialize(Engine& engine) {
  using namespace components;
  auto middle = Renderer([&] {
    auto c = ftxui::Canvas(CANVAS_WITDH, CANVAS_HEIGHT);
    auto view = engine.registry->view<Position>();
    view.each([&](const auto &pos) {
      c.DrawPointOff(std::round(pos.x), std::round(pos.y));
      c.DrawPoint(std::round(pos.x), std::round(pos.y), true, Color::White);
    });

    return canvas(std::move(c));
  });
  auto left = Renderer([] { return text("Left") | center; });
  auto right = Renderer([] { return text("right") | center; });
  auto top = Renderer([&] {
    auto &time = engine.registry->ctx<Time>();
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

  renderer = CatchEvent(renderer, [&](Event event) {
    if (event.is_character() && event.character() == "q") {
      engine.dispatcher->enqueue<events::key_pressed>(event.character());
    }
    return true;
  });
  _screen.Loop(renderer);
}

void UIScreen::render() { _screen.PostEvent(Event::Custom); }