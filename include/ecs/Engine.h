//
// Created by AsTeFu on 01.08.2019.
//

#ifndef INCLUDE_ECS_ENGINE_H_
#define INCLUDE_ECS_ENGINE_H_

#include <memory>
#include "ecs/EntityManager.h"
#include "ecs/SystemManager.h"
#include "game/Scenes/SceneManager.h"

using std::unique_ptr;

class Engine {
 private:
  unique_ptr<EntityManager> _entityManager;
  unique_ptr<SystemManager> _systemManager;

 public:
  explicit Engine(SceneManager* const sceneManager)
      : _entityManager(std::make_unique<EntityManager>()),
        _systemManager(std::make_unique<SystemManager>(_entityManager.get(), sceneManager)) {}

  EntityManager* getEntityManager() {
    return _entityManager.get();
  }
  SystemManager* getSystemManager() {
    return _systemManager.get();
  }

  void update() const {
    _systemManager->update();
  }
};

#endif  // INCLUDE_ECS_ENGINE_H_
