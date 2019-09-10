//
// Created by AsTeFu on 22.08.2019.
//

#include <ecs/EntityManager.h>
#include <editor/Components/BrushComponent.h>
#include <editor/Components/ColorComponent.h>
#include <editor/Components/StructureComponent.h>
#include <editor/EditorUtility.h>
#include <editor/Systems/StructureSystem.h>
#include <game/Scenes/SceneRenderUtility.h>
#include <game/Utility/Input.h>
#include <game/Utility/Utility.h>
#include <utilities/FileUtility.h>
#include <utilities/MathUtility.h>
#include <utilities/Terminal.h>
#include <vector>

bool StructureSystem::filter(Entity* entity) const {
  return entity->hasComponent<StructureComponent>();
}

void StructureSystem::update(Entity* entity) {
  if (Input::getKey(KeyCode::C) && Input::check(KeyCode::CTRL)) {
    EditorUtility::createEmptyStructure(entity);
  }

  if (Input::mouseLeft()) {
    Vector2 mousePosition = getMousePosition();

    auto structure = entity->getComponent<StructureComponent>();
    if (isActiveTable(mousePosition, structure->size)) return;

    drawTile(mousePosition, structure);
  }

  if (Input::mouseRight()) drawEmptyTile(entity);
}
void StructureSystem::drawTile(const Vector2& mousePosition, StructureComponent* structure) {
  auto brushComponent = getEntityManager()->getByTag("brush")[0];
  auto brush = brushComponent->getComponent<BrushComponent>();
  auto color = brushComponent->getComponent<ColorComponent>();

  structure->objects[mousePosition.getX()][mousePosition.getY()] = Tile(brush->graphic, color->color);
}
void StructureSystem::drawEmptyTile(const Entity* entity) {
  Vector2 mousePosition = getMousePosition();

  auto structure = entity->getComponent<StructureComponent>();
  if (isActiveTable(mousePosition, structure->size)) return;

  Tile tile;
  if (mousePosition.getX() == 0 || mousePosition.getY() == 0) tile = Tile('#', Color::Gray);
  if (mousePosition.getX() == structure->size.getX() - 1 || mousePosition.getY() == structure->size.getY() - 1)
    tile = Tile('#', Color::Gray);
  structure->objects[mousePosition.getX()][mousePosition.getY()] = tile;
}
void StructureSystem::postUpdate(Entity* entity) {
  auto component = entity->getComponent<StructureComponent>();
  Vector2 size(component->size.getX() + _left * 2, component->size.getY() + _top * 2 + 1);

  Terminal::setLayer(1);
  Terminal::crop(_position.getX(), _position.getY(), size.getX(), size.getY());
  Terminal::clearArea(_position, size);

  Terminal::setColor(Color::White);
  SceneRenderUtility::drawBorder(_position, size);

  for (size_t x = 0; x < component->objects.size(); ++x) {
    for (size_t y = 0; y < component->objects[x].size(); ++y) {
      Terminal::setColor(component->objects[x][y].color);
      Terminal::put(_position.getX() + x + _left, _position.getY() + y + _top, component->objects[x][y].graphic);
    }
  }

  Vector2 mousePosition = getMousePosition();
  if (!isActiveTable(mousePosition, component->size)) {
    auto brushComponent = getEntityManager()->getByTag("brush")[0];
    auto brush = brushComponent->getComponent<BrushComponent>();
    auto color = brushComponent->getComponent<ColorComponent>();

    Terminal::setColor(Color(120, color->color.r, color->color.g, color->color.b));
    Terminal::put(mousePosition.getX() + _position.getX() + _left, mousePosition.getY() + _position.getY() + _top,
                  brush->graphic);
  }
}

Vector2 StructureSystem::getMousePosition() const {
  Vector2 mousePosition = Input::getMousePosition();
  mousePosition.translate(-_left - _position.getX(), -_top - _position.getY());
  return mousePosition;
}

// TODO(ATF): переименовать
bool StructureSystem::isActiveTable(const Vector2& point, const Vector2& sizeTable) const {
  return point.getX() >= sizeTable.getX() || point.getY() >= sizeTable.getY() || point.getX() < 0 || point.getY() < 0;
}
