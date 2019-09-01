//
// Created by AsTeFu on 02.08.2019.
//

#include "game/Systems/MovementSystem.h"
#include <game/Components/EnvironmentComponents/WallComponent.h>
#include <game/Components/MovementEvent.h>
#include <game/Components/PositionsComponent.h>
#include "ecs/EntityManager.h"
#include "game/Components/BaseComponent/Collider.h"
#include "game/Components/BaseComponent/Movement.h"
#include "game/Components/BaseComponent/Transform.h"

void MovementSystem::preUpdate(Entity* entity) {
  auto transform = entity->getComponent<Transform>();
  auto movement = entity->getComponent<Movement>();

  if (getEntityManager()->getByTag("player")[0]->getComponent<Movement>()->direction == Vector2::ZERO) return;

  if (canMove(entity, transform, movement) && movement->direction != Vector2::ZERO) {
    transform->position += movement->direction;
    getEntityManager()
        ->createEntity("movementEvent")
        ->addComponent<MovementEvent>(entity->getID(), movement->direction);
  }
}
bool MovementSystem::filter(Entity* entity) const {
  return entity->hasComponent<Movement>() && entity->hasComponent<Transform>();
}

bool MovementSystem::canMove(Entity* entity, Transform* transform, Movement* movement) {
  if (!entity->hasComponent<Collider>()) return true;

  Vector2 posEntity = transform->position + movement->direction;
  auto posWalls = getEntityManager()->getByTag("walls")[0]->getComponent<PositionsComponent>();
  if (posWalls->wallPositions.count(posEntity.getX() + posEntity.getY() * posWalls->width)) return false;

  bool canMove = true;
  getEntityManager()->ForEach([entity, &canMove, &transform, &movement](Entity* coll) {
    if (!coll->hasComponent<Collider>() || coll->getID() == entity->getID()) return;

    if (transform->position + movement->direction == coll->getComponent<Transform>()->position) {
      canMove = false;
      return;
    }
  });
  return canMove;
}
void MovementSystem::postUpdate(Entity* entity) {
  if (getEntityManager()->isTag("movementEvent")) {
    if (!getEntityManager()->getByTag("movementEvent").empty()) {
      for (auto& movement : getEntityManager()->getByTag("movementEvent")) {
        getEntityManager()->deleteEntity(movement->getID());
      }
    }
  }
}
