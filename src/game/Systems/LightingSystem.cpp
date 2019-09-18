//
// Created by AsTeFu on 18.09.2019.
//

#include <BearLibTerminal.h>
#include <ecs/EntityManager.h>
#include <game/Components/BaseComponent/Lighting.h>
#include <game/Components/BaseComponent/Transform.h>
#include <game/Components/EnvironmentComponents/WallComponent.h>
#include <game/Components/ItemComponents/SpecialComponent.h>
#include <game/Components/PositionsComponent.h>
#include <game/Systems/LightingSystem.h>
#include <utilities/MathUtility.h>

bool LightingSystem::filter(Entity* entity) const {
  return entity->hasComponent<Lighting>();
}

// TODO(AsTeFu): не смог выделить в одну общую функцию, потому что перестает работать. Хз почему
// Надо найти ошибку и выделить это все в 1 общий метод
void LightingSystem::postUpdate(Entity* entity) {
  if (entity->hasComponent<WallComponent>()) {
    auto transform = entity->getComponent<Transform>();
    auto light = entity->getComponent<Lighting>();

    auto player = getEntityManager()->getByTag("player")[0];
    auto playerTransform = player->getComponent<Transform>();

    auto specialComponent = player->getComponent<SpecialComponent>();
    int perception = specialComponent->getValue(PERCEPTION) + 1;

    if ((playerTransform->position - transform->position).len2() < perception * perception &&
        isVisibleWall(transform->position.getX(), transform->position.getY())) {
      light->isLit = true;
      light->visible = true;
      light->renderPos = transform->position;
    } else {
      if (light->visible) {
        light->isLit = false;
      } else {
        return;
      }
    }
  }
}
void LightingSystem::update(Entity* entity) {
  if (!entity->hasComponent<WallComponent>()) lightingProcess(entity);
}
void LightingSystem::lightingProcess(const Entity* entity) {
  auto transform = entity->getComponent<Transform>();
  auto light = entity->getComponent<Lighting>();

  auto player = getEntityManager()->getByTag("player")[0];
  auto playerTransform = player->getComponent<Transform>();

  auto specialComponent = player->getComponent<SpecialComponent>();
  int perception = specialComponent->getValue(PERCEPTION) + 1;

  if ((playerTransform->position - light->renderPos).len2() < perception * perception &&
      brezenham(playerTransform->position, light->renderPos)) {
    light->visible = false;
  }

  if ((playerTransform->position - transform->position).len2() < perception * perception &&
      brezenham(playerTransform->position, transform->position)) {
    light->isLit = true;
    light->visible = true;
    light->renderPos = transform->position;
  } else {
    if (light->visible) {
      light->isLit = false;
    } else {
      return;
    }
  }
}

bool LightingSystem::brezenham(const Vector2& start, const Vector2& end) const {
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
bool LightingSystem::pickDot(int x, int y) const {
  // TODO(AsTeFu): pick тут заменить
  if (!points.count(x + y * width) || x < 0 || y < 0) return false;
  return points.at(x + y * width)->getComponent<Lighting>()->isLit && terminal_pick(x, y, 4) != '#';
}
bool LightingSystem::isVisibleWall(int x, int y) const {
  return pickDot(x + 1, y) || pickDot(x - 1, y) || pickDot(x, y + 1) || pickDot(x, y - 1) || pickDot(x + 1, y + 1) ||
         pickDot(x + 1, y - 1) || pickDot(x - 1, y + 1) || pickDot(x - 1, y - 1);
}
