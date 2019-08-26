//
// Created by  on 07.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_AIMOVEMENTSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_AIMOVEMENTSYSTEM_H_

#include <game/Utility/Vector2.h>
#include "ecs/ISystem.h"

class AIMovementSystem : public ISystem {
 protected:
  void preUpdate(Entity *entity) override;

 public:
  AIMovementSystem(EntityManager *const entityManager, SystemManager *const systemManager,
                   SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
  bool brezenham(const Vector2 &start, const Vector2 &end) const;
};

#endif  // INCLUDE_GAME_SYSTEMS_AIMOVEMENTSYSTEM_H_
