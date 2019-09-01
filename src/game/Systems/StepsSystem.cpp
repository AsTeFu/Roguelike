//
// Created by AsTeFu on 08.08.2019.
//

#include "game/Systems/StepsSystem.h"
#include <game/Components/BaseComponent/Movement.h>
#include <game/Components/MovementEvent.h>
#include <algorithm>
#include "ecs/EntityManager.h"

bool StepsSystem::filter(Entity* entity) const {
  return entity->hasComponent<StepsComponent>() && entity->hasComponent<Movement>();
}
void StepsSystem::update(Entity* entity) {
  if (getEntityManager()->isTag("movementEvent")) {
    auto movements = getEntityManager()->getByTag("movementEvent");

    for (const auto& movement : movements)
      if (movement->getComponent<MovementEvent>()->idEntity == entity->getID()) {
        auto stepsComponent = entity->getComponent<StepsComponent>();
        stepsComponent->currentSteps++;
      }
  }
}
