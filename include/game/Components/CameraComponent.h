//
// Created by  on 03.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_CAMERACOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_CAMERACOMPONENT_H_

#include "ecs/IComponent.h"
#include "game/Utility/ConfigTerminal.h"
#include "game/Utility/Vector2.h"

class CameraComponent : public IComponent {
 public:
  Vector2 size;
  Vector2 border;
  Vector2 offset;

  CameraComponent()
      : size(ConfigTerminal::sizeTerminal.getX() * ConfigTerminal::areaX / 200,
             ConfigTerminal::sizeTerminal.getY() * ConfigTerminal::areaY / 200),
        border(ConfigTerminal::borderSize) {}
};

#endif  // INCLUDE_GAME_COMPONENTS_CAMERACOMPONENT_H_
