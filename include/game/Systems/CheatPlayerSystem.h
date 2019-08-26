//
// Created by  on 19.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_CHEATPLAYERSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_CHEATPLAYERSYSTEM_H_

#include "ecs/ISystem.h"

class CheatPlayerSystem : public ISystem {
 protected:
  void update(Entity *entity) override;

 public:
  CheatPlayerSystem(EntityManager *const entityManager, SystemManager *const systemManager,
                    SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }

  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_CHEATPLAYERSYSTEM_H_
