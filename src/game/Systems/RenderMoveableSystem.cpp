//
// Created by AsTeFu on 24.08.2019.
//

#include <ecs/EntityManager.h>
#include <game/Components/Graphic.h>
#include <game/Components/Movement.h>
#include <game/Components/PositionsComponent.h>
#include <game/Components/SpecialComponent.h>
#include <game/Components/Transform.h>
#include <game/Systems/RenderMoveableSystem.h>
#include <game/Utility/MathUtility.h>

bool RenderMoveableSystem::filter(Entity* entity) const {
  return entity->hasComponent<Graphic>() && entity->hasComponent<Transform>() && entity->hasComponent<Movement>();
}
void RenderMoveableSystem::postUpdate(Entity* entity) {
  auto transform = entity->getComponent<Transform>();
  auto graphic = entity->getComponent<Graphic>();

  auto player = getEntityManager()->getByTag("player")[0];
  auto playerTransform = player->getComponent<Transform>();

  // TODO(AsTeFu): special
  auto special = player->getComponent<SpecialComponent>();
  int perseption = special->getValue(PERCEPTION) + 1;

  if ((playerTransform->position - graphic->renderPos).len2() < perseption * perseption &&
      brezenham(playerTransform->position, graphic->renderPos)) {
    graphic->visible = false;
  }

  if ((playerTransform->position - transform->position).len2() < perseption * perseption &&
      brezenham(playerTransform->position, transform->position)) {
    terminal_color(graphic->display.color);
    graphic->visible = true;
    graphic->renderPos = transform->position;
  } else {
    if (graphic->visible) {
      terminal_color(ConfigTerminal::disableColor);
    } else {
      return;
    }
  }

  terminal_put(graphic->renderPos.getX() + graphic->offset.getX(), graphic->renderPos.getY() + graphic->offset.getY(),
               graphic->display.graphic);
}

bool RenderMoveableSystem::brezenham(const Vector2& start, const Vector2& end) const {
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
