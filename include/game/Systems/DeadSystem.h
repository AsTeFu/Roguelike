//
// Created by  on 08.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_DEADSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_DEADSYSTEM_H_

#include <game/Components/ChestComponent.h>
#include "ecs/ISystem.h"

class DeadSystem : public ISystem {
 protected:
  void update(Entity *entity) override;

 public:
  DeadSystem(EntityManager *const entityManager, SystemManager *const systemManager, SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
  void addItems(ChestComponent *chest, Entity *enemy, int playerLuck);
};

#endif  // INCLUDE_GAME_SYSTEMS_DEADSYSTEM_H_
