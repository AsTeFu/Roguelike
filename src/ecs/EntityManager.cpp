//
// Created by AsTeFu on 01.08.2019.
//

#include "ecs/EntityManager.h"
#include <algorithm>
#include <string>
#include <vector>

Entity* EntityManager::createEntity() {
  auto id = _lastEntityID++;
  _entities.emplace(id, std::make_unique<Entity>(id));
  return _entities.at(id).get();
}
Entity* EntityManager::createEntity(const string& tag) {
  auto entity = createEntity();
  _entitiesByTag[tag].push_back(entity);
  return entity;
}
EntityManager* EntityManager::deleteEntity(size_t id) {
  for (auto& pair : _entitiesByTag) {
    int i = 0;
    for (auto& entity : pair.second) {
      if (entity->getID() == id) {
        pair.second.erase(pair.second.begin() + i);
      }
      i++;
    }
  }
  _entities.erase(id);
  return this;
}
EntityManager* EntityManager::deleteAll() {
  _entities.clear();
  _entitiesByTag.clear();
  return this;
}
Entity* EntityManager::getByID(size_t id) const {
  if (_entities.count(id) == 0) {
    std::cout << "[WARNING] there is no entity with roomID = " << id << std::endl;
    return nullptr;
  }
  return _entities.at(id).get();
}
vector<Entity*> EntityManager::getByTag(const string& tag) const {
  if (_entitiesByTag.count(tag) == 0) {
    std::cout << "[WARNING] wrong tag = " << tag << std::endl;
    return {};
  }

  return _entitiesByTag.at(tag);
}

void EntityManager::deleteTag(const string& tag) {
  if (_entitiesByTag.count(tag)) _entitiesByTag.erase(tag);
}
bool EntityManager::isTag(const string& tag) const {
  return _entitiesByTag.count(tag);
}
