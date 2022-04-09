#include "core/engine.h"
#include "ui/screen.h"

auto main() -> int {

  UIScreen uiScreen;
  uiScreen.initialize();

  Engine engine = Engine(uiScreen);
  engine.loop();

  return 0;
}