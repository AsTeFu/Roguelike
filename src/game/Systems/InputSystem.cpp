//
// Created by AsTeFu on 02.08.2019.
//

#include "game/Systems/InputSystem.h"
#include <game/Utility/Input.h>
#include <map>
#include <vector>
#include "game/Components/BaseComponent/Movement.h"
#include "game/Components/PlayerComponents/InputKeyboard.h"

std::map<std::vector<KeyCode>, Vector2> InputSystem::buttons{{{KeyCode::LeftArrow, KeyCode::A}, Vector2::LEFT},
                                                         {{KeyCode::RightArrow, KeyCode::D}, Vector2::RIGHT},
                                                         {{KeyCode::UpArrow, KeyCode::W}, Vector2::UP},
                                                         {{KeyCode::DownArrow, KeyCode::S}, Vector2::DOWN}};

void InputSystem::preUpdate(Entity* entity) {
  auto movement = entity->getComponent<Movement>();

  movement->direction.set(Vector2::ZERO);
  for (const auto& keys : buttons)
    for (const auto& key : keys.first)
      if (Input::getKeyDown(key)) movement->direction.set(keys.second);
}
bool InputSystem::filter(Entity* entity) const {
  return entity->hasComponent<Movement>() && entity->hasComponent<InputKeyboard>();
}
