//
// Created by AsTeFu on 01.08.2019.
//

#ifndef INCLUDE_ECS_SYSTEMMANAGER_H_
#define INCLUDE_ECS_SYSTEMMANAGER_H_

#include <map>
#include <memory>
#include <typeindex>
#include <vector>
#include "ecs/EntityManager.h"
#include "ecs/ISystem.h"

using std::map;
using std::type_index;
using std::unique_ptr;

class SystemManager {
 private:
  // map<type_index, unique_ptr<ISystem>> _systems;
  EntityManager *const _entityManager;
  SceneManager *const _sceneManager;
  std::vector<unique_ptr<ISystem>> _systems;

 public:
  explicit SystemManager(EntityManager *entityManager, SceneManager *sceneManager)
      : _entityManager(entityManager), _sceneManager(sceneManager) {}

  template<typename System, typename... Args>
  SystemManager *addSystem(Args &&... args) {
    // _systems.emplace(typeid(System), std::make_unique<System>(_entityManager, this, std::forward<Args>(args)...));
    _systems.emplace_back(
        std::make_unique<System>(_entityManager, this, _sceneManager, std::forward<Args>(args)...));
    return this;
  }

  template<typename System>
  SystemManager *deleteSystem() {
    // _systems.erase(typeid(System));
    return this;
  }

  SystemManager *deleteAll();
  void update();
  void setComponents();
  void deleteEntity(size_t id) {
    for (const auto &system : _systems) {
      system->deleteEntity(id);
    }
  }
  template<typename Component>
  void deleteComponent(size_t idEntity) {
    for (const auto &system : _systems) {
      system->deleteComponent<Component>(idEntity);
    }
  }
  void addEntity(Entity *pEntity);
};

#endif  // INCLUDE_ECS_SYSTEMMANAGER_H_
