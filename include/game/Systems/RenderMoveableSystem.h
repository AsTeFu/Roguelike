//
// Created by  on 24.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_RENDERMOVEABLESYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_RENDERMOVEABLESYSTEM_H_

#include "ecs/ISystem.h"

class RenderMoveableSystem : public ISystem {
 public:
  RenderMoveableSystem(EntityManager *const entityManager, SystemManager *const systemManager,
                       SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
 protected:
  void postUpdate(Entity *entity) override;
  bool brezenham(const Vector2 &start, const Vector2 &end) const;
};

#endif  // INCLUDE_GAME_SYSTEMS_RENDERMOVEABLESYSTEM_H_
