//
// Created by  on 03.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_BASECOMPONENT_CAMERACOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_BASECOMPONENT_CAMERACOMPONENT_H_

#include "Utilities/Vector2.h"
#include "ecs/IComponent.h"
#include "game/Utility/Config.h"

class CameraComponent : public IComponent {
 public:
  Vector2 size;
  Vector2 border;
  Vector2 offset;

  CameraComponent()
      : size(Config::getInstance().sizeTerminal.getX() * Config::getInstance().area.getX() / 200,
             Config::getInstance().sizeTerminal.getY() * Config::getInstance().area.getX() / 200),
        border(Config::getInstance().borderSize) {}
};

#endif  // INCLUDE_GAME_COMPONENTS_BASECOMPONENT_CAMERACOMPONENT_H_
