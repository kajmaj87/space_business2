#ifndef SB_UISCREEN
#define SB_UISCREEN

#include <entt/entt.hpp>
#include "../core/engine.h"
#include "ftxui/component/captured_mouse.hpp" // for ftxui
#include "ftxui/component/component.hpp" // for Renderer, ResizableSplitBottom, ResizableSplitLeft, ResizableSplitRight, ResizableSplitTop
#include "ftxui/component/component_base.hpp"     // for ComponentBase
#include "ftxui/component/screen_interactive.hpp" // for UIScreenInteractive
#include "ftxui/dom/canvas.hpp"
#include "ftxui/dom/elements.hpp" 

class UIScreen {
private:
  const int CANVAS_WITDH = 600, CANVAS_HEIGHT = 600;
  ftxui::ScreenInteractive _screen = ftxui::ScreenInteractive::Fullscreen();
public:
  UIScreen() = default;
  ~UIScreen() = default;
  void initialize(Engine& engine);
  void render();
  void exit(){
    auto exitClosure = _screen.ExitLoopClosure();
    exitClosure();
  }
};


#endif