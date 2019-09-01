//
// Created by AsTeFu on 22.08.2019.
//

#include <BearLibTerminal.h>
#include <ecs/EntityManager.h>
#include <editor/Components/BrushComponent.h>
#include <editor/Components/ColorComponent.h>
#include <editor/Components/StructureComponent.h>
#include <editor/CreatorUtility.h>
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
  if (Input::getKey(KeyCode::C) && terminal_check(TK_CONTROL)) {
    CreatorUtility::createEmptyStructure(entity);
  }

  if (Input::mouseLeft()) {
    Vector2 mousePosition = getMousePosition();

    auto structure = entity->getComponent<StructureComponent>();
    if (isActiveTable(mousePosition, structure->size)) return;

    auto brushComponent = getEntityManager()->getByTag("brush")[0];
    auto brush = brushComponent->getComponent<BrushComponent>();
    auto color = brushComponent->getComponent<ColorComponent>();

    structure->objects[mousePosition.getX()][mousePosition.getY()] = Tile(brush->graphic, color->color);
  }

  if (Input::mouseRight()) {
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
  SceneRenderUtility::drawBorder(_position, size);

  for (size_t x = 0; x < component->objects.size(); ++x) {
    for (size_t y = 0; y < component->objects[x].size(); ++y) {
      Terminal::setColor(component->objects[x][y].color);
      terminal_put(_position.getX() + x + _left, _position.getY() + y + _top, component->objects[x][y].graphic);
    }
  }

  Vector2 mousePosition = getMousePosition();
  if (!isActiveTable(mousePosition, component->size)) {
    auto brushComponent = getEntityManager()->getByTag("brush")[0];
    auto brush = brushComponent->getComponent<BrushComponent>();
    auto color = brushComponent->getComponent<ColorComponent>();

    terminal_color(color_from_argb(120, color->color.r, color->color.g, color->color.b));
    terminal_put(mousePosition.getX() + _position.getX() + _left, mousePosition.getY() + _position.getY() + _top,
                 brush->graphic);
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
