//
// Created by AsTeFu on 22.08.2019.
//

#include <ecs/EntityManager.h>
#include <editor/Components/BrushesComponent.h>
#include <editor/Systems/BrushSystem.h>
#include <game/Scenes/SceneRenderUtility.h>
#include <game/Utility/Input.h>
#include <game/Utility/Utility.h>
#include <utilities/MathUtility.h>
#include <utilities/Terminal.h>

bool BrushSystem::filter(Entity* entity) const {
  return entity->hasComponent<BrushesComponent>();
}
void BrushSystem::update(Entity* entity) {
  if (Input::hasInput()) {
    if (Input::isMouseWheel()) {
      int amount = Input::getMouseWheel();

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
  }
}
void BrushSystem::postUpdate(Entity* entity) {
  Terminal::setLayer(2);
  Terminal::crop(_position, _size);
  Terminal::clearArea(_position, _size);

  Terminal::setColor(Color::White);

  SceneRenderUtility::drawBorder(_position, _size);

  int x = _position.getX() + _leftMargin;
  int y = _position.getY() + _topMargin;

  Terminal::print(x, y, "Brushes:");

  x += 1;
  y += 2;

  int i = 1;
  auto component = entity->getComponent<BrushesComponent>();
  for (const auto& brush : component->brushes) {
    if (i - 1 == _currentBrush)
      Terminal::setColor(Color::White);
    else
      Terminal::setColor(Color::Gray);
    Terminal::printf(x, y++, "%d. %s: %c", i, brush->name.c_str(), brush->graphic);
    i++;
  }
}
