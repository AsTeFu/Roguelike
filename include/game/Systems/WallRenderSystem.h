//
// Created by  on 06.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_WALLRENDERSYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_WALLRENDERSYSTEM_H_

#include "ecs/ISystem.h"

class WallRenderSystem : public ISystem {
 private:
  bool pickDot(int x, int y) const;
  bool isVisibleWall(int x, int y) const;

 protected:
  void postUpdate(Entity *entity) override;

 public:
  WallRenderSystem(EntityManager *const entityManager, SystemManager *const systemManager,
                   SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_WALLRENDERSYSTEM_H_
