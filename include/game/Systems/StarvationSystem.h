//
// Created by  on 08.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_STARVATIONSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_STARVATIONSYSTEM_H_

#include <vector>
#include "ecs/ISystem.h"

class StarvationSystem : public ISystem {
 protected:
  void update(Entity *entity) override;

 public:
  StarvationSystem(EntityManager *const entityManager, SystemManager *const systemManager,
                   SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_STARVATIONSYSTEM_H_
