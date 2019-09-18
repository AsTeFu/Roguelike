//
// Created by AsTeFu on 01.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_RENDERSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_RENDERSYSTEM_H_

#include <utilities/Vector2.h>
#include "ecs/ISystem.h"

class RenderSystem : public ISystem {
 private:
  bool brezenham(const Vector2& start, const Vector2& end) const;

 protected:
  void postUpdate(Entity* entity) override;

 public:
  RenderSystem(EntityManager* const entityManager, SystemManager* const systemManager, SceneManager* const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity* entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_RENDERSYSTEMS_RENDERSYSTEM_H_
