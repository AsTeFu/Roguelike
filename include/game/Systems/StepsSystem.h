//
// Created by  on 08.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_STEPSSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_STEPSSYSTEM_H_

#include <game/Components/PlayerComponents/StepsComponent.h>
#include "ecs/ISystem.h"

class StepsSystem : public ISystem {
 protected:
  void update(Entity *entity) override;

 public:
  StepsSystem(EntityManager *const entityManager, SystemManager *const systemManager,
              SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_STEPSSYSTEM_H_
