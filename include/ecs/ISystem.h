//
// Created by AsTeFu on 01.08.2019.
//

#ifndef INCLUDE_ECS_ISYSTEM_H_
#define INCLUDE_ECS_ISYSTEM_H_

#include <iostream>
#include <memory>
#include <vector>
#include "ecs/Entity.h"
#include "game/Scenes/SceneManager.h"

using std::unique_ptr;
using std::vector;

class SystemManager;
class EntityManager;
class RoomManager;

class ISystem {
  friend class SystemManager;
  EntityManager *const _entityManager;
  SystemManager *const _systemManager;
  SceneManager *const _sceneManager;

 protected:
  vector<Entity *> _entities;
  virtual void preUpdate(Entity *entity) {}
  virtual void update(Entity *entity) {}
  virtual void postUpdate(Entity *entity) {}

 public:
  ISystem(EntityManager *const entityManager, SystemManager *const systemManager, SceneManager *const sceneManager);
  virtual ~ISystem() = default;
  EntityManager *getEntityManager() const;
  SystemManager *getSystemManager() const;
  SceneManager *getSceneManager();

  void executePreUpdate();
  void executeUpdate();
  void executePostUpdate();
  void updateComponents();
  void deleteEntity(size_t id);

  template<typename Component>
  void deleteComponent(size_t idEntity) {
    for (const auto &entity : _entities) {
      if (entity->getID() == idEntity) {
        entity->removeComponent<Component>();
        return;
      }
    }
  }
  void addEntity(Entity *entity);

  virtual bool filter(Entity *entity) const = 0;
};

#endif  // INCLUDE_ECS_ISYSTEM_H_
