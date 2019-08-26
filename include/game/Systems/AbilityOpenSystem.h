//
// Created by  on 20.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_ABILITYOPENSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_ABILITYOPENSYSTEM_H_

#include "ecs/ISystem.h"

class AbilityOpenSystem : public ISystem {
 protected:
  void update(Entity *entity) override;

 public:
  AbilityOpenSystem(EntityManager *const entityManager, SystemManager *const systemManager,
                SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_ABILITYOPENSYSTEM_H_
