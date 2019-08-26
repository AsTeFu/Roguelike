//
// Created by AsTeFu on 22.08.2019.
//

#include <ecs/EntityManager.h>
#include <game/Utility/Input.h>
#include <game/Utility/MathUtility.h>
#include <game/Utility/Utility.h>
#include <roomcreator/Components/BrushComponent.h>
#include <roomcreator/Components/ColorComponent.h>
#include <roomcreator/Components/StructureComponent.h>
#include <roomcreator/CreatorUtility.h>
#include <roomcreator/FileUtility.h>
#include <roomcreator/Systems/StructureSystem.h>
#include <vector>

bool StructureSystem::filter(Entity* entity) const {
  return entity->hasComponent<StructureComponent>();
}

void StructureSystem::update(Entity* entity) {
  if (Input::isPressed(TK_C) && terminal_check(TK_CONTROL)) {
    CreatorUtility::createEmptyStructure(entity);
  }

  if (Input::mouseLeft() && terminal_check(TK_SHIFT)) {
    Vector2 mousePosition = getMousePosition();
    auto structure = entity->getComponent<StructureComponent>();

    if (isActiveTable(mousePosition, structure->size)) return;

    if (linePos.getX() == -1) {
      linePos = mousePosition;
    } else {
      brezenham(structure, linePos, mousePosition);
      linePos.set(-1, -1);
    }
    return;
  }

  if (Input::mouseLeft()) {
    linePos.set(-1, -1);
    Vector2 mousePosition = getMousePosition();

    auto structure = entity->getComponent<StructureComponent>();
    if (isActiveTable(mousePosition, structure->size)) return;

    auto brushComponent = getEntityManager()->getByTag("brush")[0];
    auto brush = brushComponent->getComponent<BrushComponent>();
    auto color = brushComponent->getComponent<ColorComponent>();

    structure->objects[mousePosition.getX()][mousePosition.getY()] = Tile(brush->graphic, color->color);
  }

  if (Input::mouseRight()) {
    linePos.set(-1, -1);
    Vector2 mousePosition = getMousePosition();

    auto structure = entity->getComponent<StructureComponent>();
    if (isActiveTable(mousePosition, structure->size)) return;

    structure->objects[mousePosition.getX()][mousePosition.getY()] = Tile();
  }
}
void StructureSystem::postUpdate(Entity* entity) {
  auto component = entity->getComponent<StructureComponent>();

  Vector2 size(component->size.getX() + _left * 2, component->size.getY() + _top * 2 + 1);

  terminal_layer(1);
  terminal_crop(_position.getX(), _position.getY(), size.getX(), size.getY());
  terminal_clear_area(_position.getX(), _position.getY(), size.getX(), size.getY());

  terminal_color("white");
  Utility::drawBorder(_position, size);

  for (size_t x = 0; x < component->objects.size(); ++x) {
    for (size_t y = 0; y < component->objects[x].size(); ++y) {
      terminal_color(component->objects[x][y].color);
      terminal_put(_position.getX() + x + _left, _position.getY() + y + _top, component->objects[x][y].graphic);
    }
  }

  Vector2 mousePosition = getMousePosition();
  if (!isActiveTable(mousePosition, component->size)) {
    auto brushComponent = getEntityManager()->getByTag("brush")[0];
    auto brush = brushComponent->getComponent<BrushComponent>();
    auto color = brushComponent->getComponent<ColorComponent>();

    terminal_color(color_from_argb(120, color->argb.r, color->argb.g, color->argb.b));
    terminal_put(mousePosition.getX() + _position.getX() + _left, mousePosition.getY() + _position.getY() + _top,
                 brush->graphic);
  }

  if (linePos.getX() != -1) {
    brezenhamPosible(component, linePos, mousePosition);
  }
}

Vector2 StructureSystem::getMousePosition() const {
  int x = terminal_state(TK_MOUSE_X) - _left - _position.getX();
  int y = terminal_state(TK_MOUSE_Y) - _top - _position.getY();

  return {x, y};
}

// TODO(ATF): переименовать
bool StructureSystem::isActiveTable(const Vector2& point, const Vector2& sizeTable) const {
  return point.getX() >= sizeTable.getX() || point.getY() >= sizeTable.getY() || point.getX() < 0 || point.getY() < 0;
}

// TODO(ATF): снова два брезенхама
void StructureSystem::brezenham(StructureComponent* structure, const Vector2& start, const Vector2& end) const {
  int x, y, dx, dy, incx, incy, pdx, pdy, es, el, err;

  auto brushComponent = getEntityManager()->getByTag("brush")[0];
  auto brush = brushComponent->getComponent<BrushComponent>();
  auto color = brushComponent->getComponent<ColorComponent>();

  structure->objects[start.getX()][start.getY()] = Tile(brush->graphic, color->color);

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

    structure->objects[x][y] = Tile(brush->graphic, color->color);
  }
}
void StructureSystem::brezenhamPosible(StructureComponent* structure, const Vector2& start, const Vector2& end) const {
  int x, y, dx, dy, incx, incy, pdx, pdy, es, el, err;

  if (isActiveTable(end, structure->size)) return;

  auto brushComponent = getEntityManager()->getByTag("brush")[0];
  auto brush = brushComponent->getComponent<BrushComponent>();
  auto color = brushComponent->getComponent<ColorComponent>();

  terminal_color(color_from_argb(120, color->argb.r, color->argb.g, color->argb.b));
  terminal_put(start.getX() + _position.getX() + _left, start.getY() + _position.getY() + _top, brush->graphic);

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

    terminal_put(x + _position.getX() + _left, y + _position.getY() + _top, brush->graphic);
  }
}
