//
// Created by AsTeFu on 06.08.2019.
//

#include "game/Systems/PointRenderSystem.h"
#include <game/Components/SpecialComponent.h>
#include <game/Utility/ConfigTerminal.h>
#include <game/Utility/MathUtility.h>
#include "ecs/EntityManager.h"
#include "game/Components/PositionsComponent.h"

bool PointRenderSystem::filter(Entity* entity) const {
  return entity->hasComponent<Transform>() && entity->hasComponent<Graphic>() && entity->hasComponent<PointComponent>();
}
void PointRenderSystem::postUpdate(Entity* entity) {
  auto positionPoint = entity->getComponent<Transform>();

  auto player = getEntityManager()->getByTag("player")[0];
  auto positionPlayer = player->getComponent<Transform>();
  auto graphic = entity->getComponent<Graphic>();

  // TODO(AsTeFu): special
  auto special = player->getComponent<SpecialComponent>();
  int perseption = special->getValue(PERCEPTION) + 1;

  if ((positionPlayer->position - positionPoint->position).len2() < perseption * perseption &&
      brezenham(positionPlayer->position, positionPoint->position)) {
    terminal_color(color_from_argb(255, 180, 180, 180));
    graphic->visible = true;
  } else {
    if (graphic->visible) {
      terminal_color(ConfigTerminal::disableColor);
    } else {
      return;
    }
  }

  terminal_put(positionPoint->position.getX() + graphic->offset.getX(),
               positionPoint->position.getY() + graphic->offset.getY(), graphic->display.graphic);
}

bool PointRenderSystem::brezenham(const Vector2& start, const Vector2& end) const {
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
