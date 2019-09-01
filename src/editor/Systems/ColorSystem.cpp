//
// Created by AsTeFu on 22.08.2019.
//

#include <BearLibTerminal.h>
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
  Vector2 size(Config::getInstance().sizeTerminal.getX() - 20, 10);
  terminal_layer(4);
  terminal_crop(_position.getX(), _position.getY(), size.getX(), size.getY());
  terminal_clear_area(_position.getX(), _position.getY(), size.getX(), size.getY());

  terminal_color("white");

  SceneRenderUtility::verticalBorder(_position, size);
  SceneRenderUtility::horizontalBorder(_position, size);

  int offsetX = _position.getX() + 5;
  int offsetY = _position.getY() + 2;

  int i = 0;
  auto component = entity->getComponent<ColorsComponent>();
  for (const auto& color : component->colors) {
    if (i == _currentColor) {
      terminal_color("white");
      SceneRenderUtility::drawBorder(offsetX - 1, offsetY - 1, 7, 4);
    }

    Terminal::setColor(color->color);
    Terminal::print(offsetX, offsetY++, "#####");
    Terminal::print(offsetX, offsetY--, "#####");

    offsetX += 3 + 5;
    i++;
    if (offsetX > _position.getX() + size.getX() - 8) {
      offsetX = _position.getX() + 5;
      offsetY += 3;
    }
  }
}
