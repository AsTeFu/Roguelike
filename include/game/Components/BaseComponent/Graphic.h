//
// Created by AsTeFu on 01.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_BASECOMPONENT_GRAPHIC_H_
#define INCLUDE_GAME_COMPONENTS_BASECOMPONENT_GRAPHIC_H_

#include "utilities/Vector2.h"
#include "ecs/IComponent.h"
#include "game/Utility/Display.h"

class Graphic : public IComponent {
 public:
  Display display;
  Vector2 offset;
  bool visible;
  Vector2 renderPos{};
  explicit Graphic(const Display& display) : display(display), visible(false) {}
  Graphic(char graphic, Color color) : display(graphic, color), visible(false) {}
};

#endif  // INCLUDE_GAME_COMPONENTS_BASECOMPONENT_GRAPHIC_H_
