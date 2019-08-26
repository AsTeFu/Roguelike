//
// Created by AsTeFu on 06.08.2019.
//

#include "game/Systems/WallRenderSystem.h"
#include <game/Components/Collider.h>
#include <game/Components/ExitComponent.h>
#include <game/Components/Graphic.h>
#include <game/Components/Transform.h>
#include <game/Components/WallComponent.h>
#include <game/Utility/ConfigTerminal.h>

bool WallRenderSystem::filter(Entity* entity) const {
  return ((entity->hasComponent<Collider>() && entity->hasComponent<WallComponent>()) ||
          entity->hasComponent<ExitComponent>()) &&
         entity->hasComponent<Transform>() && entity->hasComponent<Graphic>();
}
void WallRenderSystem::postUpdate(Entity* entity) {
  auto positionWall = entity->getComponent<Transform>();
  auto graphic = entity->getComponent<Graphic>();

  if (isVisibleWall(positionWall->position.getX() + graphic->offset.getX(),
                    positionWall->position.getY() + graphic->offset.getY())) {
    terminal_color(graphic->display.color);
    graphic->visible = true;
  } else {
    if (graphic->visible) {
      terminal_color(ConfigTerminal::disableColor);
    } else {
      return;
    }
  }

  terminal_put(positionWall->position.getX() + graphic->offset.getX(),
               positionWall->position.getY() + graphic->offset.getY(), graphic->display.graphic);
}

bool WallRenderSystem::pickDot(int x, int y) const {
  // TODO(AsTeFu): pick тут заменить
  return terminal_pick_color(x, y, 0) == color_from_argb(255, 180, 180, 180) && terminal_pick(x, y, 0) != '#';
}
bool WallRenderSystem::isVisibleWall(int x, int y) const {
  return pickDot(x + 1, y) || pickDot(x - 1, y) || pickDot(x, y + 1) || pickDot(x, y - 1) || pickDot(x + 1, y + 1) ||
         pickDot(x + 1, y - 1) || pickDot(x - 1, y + 1) || pickDot(x - 1, y - 1);
}
