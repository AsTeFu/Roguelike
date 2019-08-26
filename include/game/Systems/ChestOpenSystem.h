//
// Created by  on 10.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_CHESTOPENSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_CHESTOPENSYSTEM_H_

#include "ecs/ISystem.h"

class ChestOpenSystem : public ISystem {
 protected:
  void update(Entity *entity) override;

 public:
  ChestOpenSystem(EntityManager *const entityManager, SystemManager *const systemManager,
                  SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_CHESTOPENSYSTEM_H_
