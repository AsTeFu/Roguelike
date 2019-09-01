//
// Created by AsTeFu on 07.08.2019.
//

#include "game/Systems/AIMovementSystem.h"
#include <Utilities/Random.h>
#include <game/Components/ItemComponents/SpecialComponent.h>
#include <game/Components/PositionsComponent.h>
#include <utilities/MathUtility.h>
#include "ecs/EntityManager.h"
#include "game/Components/AIController.h"
#include "game/Components/BaseComponent/Movement.h"
#include "game/Components/BaseComponent/Transform.h"

bool AIMovementSystem::filter(Entity* entity) const {
  return entity->hasComponent<AIController>() && entity->hasComponent<Transform>() && entity->hasComponent<Movement>();
}
void AIMovementSystem::preUpdate(Entity* entity) {
  auto movement = entity->getComponent<Movement>();
  auto transform = entity->getComponent<Transform>();
  auto special = entity->getComponent<SpecialComponent>();
  auto player = getEntityManager()->getByTag("player")[0]->getComponent<Transform>();

  // TODO(AsTeFu): special
  int distance = special->getValue(PERCEPTION) * special->getValue(PERCEPTION);
  if ((player->position - transform->position).len2() < distance && brezenham(player->position, transform->position)) {
    Vector2 dir = player->position - transform->position;
    Vector2 len{
        (player->position.getX() - transform->position.getX()) * (player->position.getX() - transform->position.getX()),
        (player->position.getY() - transform->position.getY()) *
            (player->position.getY() - transform->position.getY())};

    if (len.getX() > len.getY())
      dir.getX() > 0 ? movement->direction = Vector2::RIGHT : movement->direction = Vector2::LEFT;
    else
      dir.getY() > 0 ? movement->direction = Vector2::DOWN : movement->direction = Vector2::UP;

    if (!Random::random(5) || dir.len2() <= 1) movement->direction = Vector2::ZERO;
  } else {
    int rnd = Random::random(1000);
    if (rnd < 250)
      movement->direction = Vector2::UP;
    else if (rnd < 500)
      movement->direction = Vector2::DOWN;
    else if (rnd < 750)
      movement->direction = Vector2::LEFT;
    else if (rnd < 1000)
      movement->direction = Vector2::RIGHT;
    else
      movement->direction = Vector2::ZERO;
  }
}

bool AIMovementSystem::brezenham(const Vector2& start, const Vector2& end) const {
  int x, y, dx, dy, incx, incy, pdx, pdy, es, el, err;

  auto walls = getEntityManager()->getByTag("walls")[0]->getComponent<PositionsComponent>();

  dx = end.getX() - start.getX();
  dy = end.getY() - start.getY();

  incx = MathUtility::sign(dx);
  incy = MathUtility::sign(dy);

  if (dx < 0) dx = -dx;
  if (dy < 0) dy = -dy;

  if (dx > dy) {
    pdx = incx;
    pdy = 0;
    es = dy;
    el = dx;
  } else {
    pdx = 0;
    pdy = incy;
    es = dx;
    el = dy;
  }

  x = start.getX();
  y = start.getY();
  err = el / 2;

  for (int t = 0; t < el; t++) {
    err -= es;

    if (err < 0) {
      err += el;
      x += incx;
      y += incy;
    } else {
      x += pdx;
      y += pdy;
    }

    if (walls->wallPositions.count(x + walls->width * y)) return false;
  }

  return true;
}
