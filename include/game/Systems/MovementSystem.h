//
// Created by AsTeFu on 02.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_MOVEMENTSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_MOVEMENTSYSTEM_H_

#include <game/Components/Movement.h>
#include <game/Components/Transform.h>
#include "ecs/ISystem.h"

class MovementSystem : public ISystem {
 private:
  bool canMove(Entity* entity, Transform* transform, Movement* movement);

 protected:
  void preUpdate(Entity* entity) override;
  void postUpdate(Entity* entity) override;

 public:
  MovementSystem(EntityManager *const entityManager, SystemManager *const systemManager,
                 SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity* entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_MOVEMENTSYSTEM_H_
