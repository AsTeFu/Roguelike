//
// Created by  on 03.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_COLLISIONSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_COLLISIONSYSTEM_H_

#include "ecs/ISystem.h"

class CollisionSystem : public ISystem {
 protected:
  void preUpdate(Entity *entity) override;
  void update(Entity *entity) override;

 public:
  CollisionSystem(EntityManager *const entityManager, SystemManager *const systemManager,
                  SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_COLLISIONSYSTEM_H_
