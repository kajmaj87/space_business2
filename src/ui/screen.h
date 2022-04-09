#ifndef SB_UISCREEN
#define SB_UISCREEN

#include "ftxui/component/captured_mouse.hpp" // for ftxui
#include "ftxui/component/component.hpp" // for Renderer, ResizableSplitBottom, ResizableSplitLeft, ResizableSplitRight, ResizableSplitTop
#include "ftxui/component/component_base.hpp"     // for ComponentBase
#include "ftxui/component/screen_interactive.hpp" // for UIScreenInteractive
#include "ftxui/dom/canvas.hpp"
#include "ftxui/dom/elements.hpp" 

class UIScreen {
private:
  const ftxui::ScreenInteractive& _screen;
public:
  explicit UIScreen(): _screen(ftxui::ScreenInteractive::Fullscreen()) {};
  ~UIScreen() = default;
  void initialize();
  void render();
};


#endif