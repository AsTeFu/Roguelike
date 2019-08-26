//
// Created by AsTeFu on 01.08.2019.
//

#include "ecs/SystemManager.h"

void SystemManager::update() {
  for (auto &system : _systems) system->executePreUpdate();
  for (auto &system : _systems) system->executeUpdate();
  for (auto &system : _systems) system->executePostUpdate();
}
SystemManager *SystemManager::deleteAll() {
  _systems.clear();
  return this;
}
void SystemManager::setComponents() {
  for (const auto &sys : _systems) {
    sys->updateComponents();
  }
}
void SystemManager::addEntity(Entity *pEntity) {
  for (const auto &sys : _systems) {
    sys->addEntity(pEntity);
  }
}
