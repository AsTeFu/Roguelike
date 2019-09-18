//
// Created by AsTeFu on 01.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_BASECOMPONENT_GRAPHIC_H_
#define INCLUDE_GAME_COMPONENTS_BASECOMPONENT_GRAPHIC_H_

#include "ecs/IComponent.h"
#include "game/Utility/Display.h"
#include "utilities/Vector2.h"

class Graphic : public IComponent {
 public:
  Display display;
  Vector2 offset;
  int layer{0};

  explicit Graphic(const Display& display) : display(display) {}
  Graphic(char graphic, Color color) : display(graphic, color) {}
  Graphic(char graphic, Color color, int layer) : display(graphic, color), layer(layer) {}
};

#endif  // INCLUDE_GAME_COMPONENTS_BASECOMPONENT_GRAPHIC_H_
