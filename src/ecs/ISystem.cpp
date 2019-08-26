//
// Created by AsTeFu on 01.08.2019.
//

#include "ecs/ISystem.h"
#include <algorithm>
#include "ecs/EntityManager.h"

ISystem::ISystem(EntityManager *const entityManager, SystemManager *const systemManager,
                 SceneManager *const sceneManager)
    : _entityManager(entityManager), _systemManager(systemManager), _sceneManager(sceneManager) {}

SystemManager *ISystem::getSystemManager() const {
  return _systemManager;
}
EntityManager *ISystem::getEntityManager() const {
  return _entityManager;
}

SceneManager *ISystem::getSceneManager() {
  return _sceneManager;
}

void ISystem::executePreUpdate() {
  for (const auto &entity : _entities) preUpdate(entity);
}
void ISystem::executeUpdate() {
  for (const auto &entity : _entities) update(entity);
}
void ISystem::executePostUpdate() {
  for (const auto &entity : _entities) postUpdate(entity);
}

void ISystem::updateComponents() {
  _entities.clear();
  getEntityManager()->ForEach([this](Entity *entity) {
    if (filter(entity)) _entities.push_back(entity);
  });
}
void ISystem::deleteEntity(size_t id) {
  int i = 0;
  for (const auto &entity : _entities) {
    if (entity->getID() == id) {
      _entities.erase(_entities.begin() + i);
      return;
    }
    i++;
  }
}
void ISystem::addEntity(Entity *entity) {
  if (filter(entity)) _entities.push_back(entity);
}
