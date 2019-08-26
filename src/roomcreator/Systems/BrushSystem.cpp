//
// Created by AsTeFu on 22.08.2019.
//

#include <ecs/EntityManager.h>
#include <game/Utility/Input.h>
#include <game/Utility/MathUtility.h>
#include <game/Utility/Utility.h>
#include <roomcreator/Components/BrushesComponent.h>
#include <roomcreator/Systems/BrushSystem.h>

bool BrushSystem::filter(Entity* entity) const {
  return entity->hasComponent<BrushesComponent>();
}
void BrushSystem::update(Entity* entity) {
  if (Input::hasInput()) {
    if (terminal_peek() == TK_MOUSE_SCROLL) {
      int amount = terminal_state(TK_MOUSE_WHEEL);

      if (std::abs(amount) > 0) {
        int size = static_cast<int>(entity->getComponent<BrushesComponent>()->brushes.size());

        if ((amount > 0 && _currentBrush < size - 1) || (amount < 0 && _currentBrush > 0)) {
          _currentBrush += MathUtility::sign(amount);

          auto brush = getEntityManager()->getByTag("brush")[0]->getComponent<BrushComponent>();
          auto brushes = entity->getComponent<BrushesComponent>();

          brush->name = brushes->brushes[_currentBrush]->name;
          brush->graphic = brushes->brushes[_currentBrush]->graphic;
        }
      }
    }
    /*
    for (int i = 0; i < 10; ++i) {
      if (Input::isPressed(TK_1 + i)) {
        auto brush = getEntityManager()->getByTag("brush")[0]->getComponent<BrushComponent>();
        auto brushes = entity->getComponent<BrushesComponent>();

        brush->name = brushes->brushes[i]->name;
        brush->graphic = brushes->brushes[i]->graphic;
        _currentBrush = i;
      }
    } */
  }
}
void BrushSystem::postUpdate(Entity* entity) {
  Vector2 size(30, 30);
  terminal_layer(2);
  terminal_crop(_position.getX(), _position.getY(), size.getX(), size.getY());
  terminal_clear_area(_position.getX(), _position.getY(), size.getX(), size.getY());

  terminal_color("white");

  Utility::drawBorder(_position, size);

  int offsetX = _position.getX() + 2;
  int offsetY = _position.getY() + 2;

  terminal_print(offsetX, offsetY, "Brushes:");

  offsetX += 1;
  offsetY += 2;

  int i = 1;
  auto component = entity->getComponent<BrushesComponent>();
  for (const auto& brush : component->brushes) {
    if (i - 1 == _currentBrush)
      terminal_color("white");
    else
      terminal_color("gray");
    terminal_printf(offsetX, offsetY++, "%d. %s: %c", i, brush->name.c_str(), brush->graphic);
    i++;
  }
}
