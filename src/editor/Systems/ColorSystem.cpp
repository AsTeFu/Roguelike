//
// Created by AsTeFu on 22.08.2019.
//

#include <ecs/EntityManager.h>
#include <editor/Components/BrushComponent.h>
#include <editor/Components/ColorComponent.h>
#include <editor/Components/ColorsComponent.h>
#include <editor/Systems/ColorSystem.h>
#include <game/Scenes/SceneRenderUtility.h>
#include <game/Utility/Config.h>
#include <game/Utility/Input.h>
#include <game/Utility/Utility.h>
#include <utilities/Terminal.h>

bool ColorSystem::filter(Entity* entity) const {
  return entity->hasComponent<ColorsComponent>();
}
void ColorSystem::update(Entity* entity) {
  if (Input::getKey(KeyCode::RightArrow) || Input::getKey(KeyCode::D)) {
    if (_currentColor == static_cast<int>(entity->getComponent<ColorsComponent>()->colors.size()) - 1) {
      _currentColor = -1;
    }

    if (_currentColor < static_cast<int>(entity->getComponent<ColorsComponent>()->colors.size()) - 1) {
      _currentColor++;

      auto color = entity->getComponent<ColorsComponent>()->colors[_currentColor];
      *getEntityManager()->getByTag("brush")[0]->getComponent<ColorComponent>() = *color;
    }
  }

  if (Input::getKey(KeyCode::LeftArrow) || Input::getKey(KeyCode::A)) {
    if (_currentColor == 0) {
      _currentColor = static_cast<int>(entity->getComponent<ColorsComponent>()->colors.size());
    }

    if (_currentColor > 0) {
      _currentColor--;

      auto color = entity->getComponent<ColorsComponent>()->colors[_currentColor];
      *getEntityManager()->getByTag("brush")[0]->getComponent<ColorComponent>() = *color;
    }
  }
}
void ColorSystem::postUpdate(Entity* entity) {
  Terminal::setLayer(4);
  Terminal::crop(_position, _size);
  Terminal::clearArea(_position, _size);

  Terminal::setColor(Color::White);

  SceneRenderUtility::drawBorder(_position, _size);

  int x = _position.getX() + leftMargin;
  int y = _position.getY() + topMargin;

  int i = 0;
  auto component = entity->getComponent<ColorsComponent>();
  for (const auto& color : component->colors) {
    if (i == _currentColor) {
      Terminal::setColor(Color::White);
      SceneRenderUtility::drawBorder(x - 1, y - 1, 7, 4);
    }

    Terminal::setColor(color->color);
    Terminal::print(x, y++, "#####");
    Terminal::print(x, y--, "#####");

    x += 3 + 5;
    i++;
    if (x > _position.getX() + _size.getX() - 8) {
      x = _position.getX() + 5;
      y += 3;
    }
  }
}
