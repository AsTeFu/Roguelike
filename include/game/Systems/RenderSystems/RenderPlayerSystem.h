//
// Created by  on 16.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_RENDERPLAYERSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_RENDERPLAYERSYSTEM_H_

#include "ecs/ISystem.h"

class RenderPlayerSystem : public ISystem {
 protected:
  void postUpdate(Entity *entity) override;

 public:
  RenderPlayerSystem(EntityManager *const entityManager, SystemManager *const systemManager,
                     SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_RENDERPLAYERSYSTEM_H_
