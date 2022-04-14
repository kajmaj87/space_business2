#ifndef SB_UISCREEN
#define SB_UISCREEN

#include <entt/entt.hpp>
#include "ftxui/component/captured_mouse.hpp" // for ftxui
#include "ftxui/component/component.hpp" // for Renderer, ResizableSplitBottom, ResizableSplitLeft, ResizableSplitRight, ResizableSplitTop
#include "ftxui/component/component_base.hpp"     // for ComponentBase
#include "ftxui/component/screen_interactive.hpp" // for UIScreenInteractive
#include "ftxui/dom/canvas.hpp"
#include "ftxui/dom/elements.hpp" 

#include "../core/components/position.h"

class UIScreen {
private:
  const int CANVAS_WITDH = 100, CANVAS_HEIGHT = 100, GRID_SIZE = 10;
  ftxui::ScreenInteractive _screen = ftxui::ScreenInteractive::Fullscreen();
public:
  UIScreen() = default;
  ~UIScreen() = default;
  void initialize(entt::registry& registry);
  void render();
};


#endif