//
// Created by  on 08.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_DEADSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_DEADSYSTEM_H_

#include <game/Components/BaseComponent/Transform.h>
#include <game/Components/EnvironmentComponents/ChestComponent.h>
#include "ecs/ISystem.h"

class DeadSystem : public ISystem {
 private:
  Entity *findDeadEnemy(Transform *const transform);

 protected:
  void update(Entity *entity) override;

 public:
  DeadSystem(EntityManager *const entityManager, SystemManager *const systemManager, SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
  void fillChest(ChestComponent *chest, Entity *enemy, int playerLuck);
  Entity *createChest(const Entity *entity) const;
};

#endif  // INCLUDE_GAME_SYSTEMS_DEADSYSTEM_H_
