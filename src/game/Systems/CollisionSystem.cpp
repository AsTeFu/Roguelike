//
// Created by AsTeFu on 03.08.2019.
//

#include "game/Systems/CollisionSystem.h"
#include <game/Components/BaseComponent/Collider.h>
#include <game/Components/EnvironmentComponents/WallComponent.h>
#include "ecs/EntityManager.h"
#include "game/Components/BaseComponent/Transform.h"
#include "game/Components/BaseComponent/Trigger.h"

void CollisionSystem::preUpdate(Entity* entity) {
  entity->getComponent<Collider>()->colls.clear();
}
void CollisionSystem::update(Entity* entity) {
  auto transform = entity->getComponent<Transform>();
  auto collider = entity->getComponent<Collider>();

  for (const auto& coll : _entities) {
    if ((transform->position - coll->getComponent<Transform>()->position).len2() <= 2) {
      collider->colls.push_back(coll);
    }
  }
}
bool CollisionSystem::filter(Entity* entity) const {
  return entity->hasComponent<Transform>() && entity->hasComponent<Collider>() &&
         !entity->hasComponent<WallComponent>();
}
