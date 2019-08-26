//
// Created by  on 11.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_FOODTRIGGERSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_FOODTRIGGERSYSTEM_H_

#include <game/Components/FoodItemComponent.h>
#include <game/Components/Trigger.h>
#include "ecs/ISystem.h"

class FoodTriggerSystem : public ISystem {
 protected:
  void update(Entity *entity) override;

 public:
  FoodTriggerSystem(EntityManager *const entityManager, SystemManager *const systemManager,
                    SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_FOODTRIGGERSYSTEM_H_
