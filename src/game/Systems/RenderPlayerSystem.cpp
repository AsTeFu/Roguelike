//
// Created by AsTeFu on 16.08.2019.
//

#include "game/Systems/RenderPlayerSystem.h"
#include <game/Components/AIController.h>
#include <game/Components/BaseComponent/Graphic.h>
#include <game/Components/BaseComponent/Transform.h>
#include <game/Components/PlayerComponents/PlayerComponent.h>
#include <utilities/Terminal.h>
#include "ecs/EntityManager.h"

bool RenderPlayerSystem::filter(Entity* entity) const {
  return entity->hasComponent<Graphic>() && entity->hasComponent<Transform>() &&
         entity->hasComponent<PlayerComponent>();
}
void RenderPlayerSystem::postUpdate(Entity* entity) {
  auto graphic = entity->getComponent<Graphic>();
  auto transform = entity->getComponent<Transform>();

  Terminal::setColor(graphic->display.color);
  Terminal::put(transform->position.getX() + graphic->offset.getX(),
                transform->position.getY() + graphic->offset.getY(), graphic->display.graphic);
}
