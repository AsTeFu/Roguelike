//
// Created by  on 07.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_ATTACKSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_ATTACKSYSTEM_H_

#include "ecs/ISystem.h"

class AttackSystem : public ISystem {
 private:
  static void attack(Entity *entity, Entity *target);

 protected:
  void preUpdate(Entity *entity) override;

 public:
  AttackSystem(EntityManager *const entityManager, SystemManager *const systemManager, SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_ATTACKSYSTEM_H_
