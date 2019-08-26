//
// Created by AsTeFu on 11.08.2019.
//

#include "game/Systems/FoodTriggerSystem.h"
#include <game/Components/SpecialComponent.h>
#include <game/Components/StarvationComponent.h>
#include <game/Components/Transform.h>
#include <game/Logs/GameLogger.h>
#include "ecs/EntityManager.h"
#include "ecs/SystemManager.h"

bool FoodTriggerSystem::filter(Entity* entity) const {
  return entity->hasComponent<Trigger>() && entity->hasComponent<FoodItemComponent>();
}
void FoodTriggerSystem::update(Entity* entity) {
  auto food = entity->getComponent<FoodItemComponent>();
  auto transform = entity->getComponent<Transform>();

  auto player = getEntityManager()->getByTag("player")[0];

  int addFood = food->food + player->getComponent<SpecialComponent>()->getValue(LUCK) * 2;
  if (transform->position == player->getComponent<Transform>()->position) {
    if (player->hasComponent<StarvationComponent>())
      player->getComponent<StarvationComponent>()->currentFood += addFood;

    GameLogger::getInstance().add("[color=green]Food[/color] was picked up [color=green](" +
                                  std::to_string(addFood) + ")");
    getEntityManager()->deleteEntity(entity->getID());
    getSystemManager()->deleteEntity(entity->getID());
  }
}
