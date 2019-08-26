//
// Created by  on 03.08.2019.
//

#ifndef INCLUDE_GAME_SYSTEMS_CAMERASYSTEM_H_
#define INCLUDE_GAME_SYSTEMS_CAMERASYSTEM_H_

#include "ecs/ISystem.h"

class CameraSystem : public ISystem {
 protected:
  void postUpdate(Entity *entity) override;

 public:
  CameraSystem(EntityManager *const entityManager, SystemManager *const systemManager, SceneManager *const sceneManager)
      : ISystem(entityManager, systemManager, sceneManager) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
};

#endif  // INCLUDE_GAME_SYSTEMS_CAMERASYSTEM_H_
