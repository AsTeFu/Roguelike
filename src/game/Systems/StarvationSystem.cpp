//
// Created by AsTeFu on 08.08.2019.
//

#include "game/Systems/StarvationSystem.h"
#include <game/Components/HealthComponent.h>
#include <game/Components/Movement.h>
#include <game/Components/MovementEvent.h>
#include <game/Components/SpecialComponent.h>
#include <game/Components/StarvationComponent.h>
#include <game/Components/StepsComponent.h>
#include <algorithm>
#include <vector>
#include "ecs/EntityManager.h"

bool StarvationSystem::filter(Entity* entity) const {
  return entity->hasComponent<StarvationComponent>() && entity->getComponent<Movement>();
}
void StarvationSystem::update(Entity* entity) {
  if (getEntityManager()->isTag("movementEvent")) {
    auto movements = getEntityManager()->getByTag("movementEvent");
    for (const auto& movement : movements) {
      if (movement->getComponent<MovementEvent>()->idEntity == entity->getID()) {
        auto starvation = entity->getComponent<StarvationComponent>();

        // TODO(AsTeFu): special
        // Отнимать 1 единицу за ход, если нет этих компонентов
        auto specialComponent = entity->getComponent<SpecialComponent>();
        auto stepsComponent = entity->getComponent<StepsComponent>();

        if (starvation->currentFood <= 0) {
          if (entity->hasComponent<HealthComponent>()) {
            entity->getComponent<HealthComponent>()->health -= 10;
          }
          return;
        }

        if (!(stepsComponent->currentSteps % (specialComponent->getValue(ENDURANCE) / 2 + 1)))
          starvation->currentFood -= 1;
      }
    }
  }
}
