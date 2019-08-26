//
// Created by AsTeFu on 02.08.2019.
//

#include "game/Systems/InputSystem.h"
#include <BearLibTerminal.h>
#include <algorithm>
#include <map>
#include "game/Components/InputKeyboard.h"
#include "game/Components/Movement.h"

void InputSystem::preUpdate(Entity* entity) {
  auto movement = entity->getComponent<Movement>();
  auto input = entity->getComponent<InputKeyboard>();

  std::map<int, Vector2> buttons;
  buttons.emplace(TK_LEFT, Vector2::LEFT);
  buttons.emplace(TK_RIGHT, Vector2::RIGHT);
  buttons.emplace(TK_UP, Vector2::UP);
  buttons.emplace(TK_DOWN, Vector2::DOWN);

  int key = terminal_peek();

  if (input->downs[key]) {
    movement->direction.set(Vector2::ZERO);
    return;
  }

  for (const auto& button : buttons) {
    if ((button.first | TK_KEY_RELEASED) == key) {
      // std::cout << "Released button: " << button.second << std::endl;
      movement->direction.set(Vector2::ZERO);
      input->downs[button.first] = false;
      return;
    }
  }

  input->key = key;
  input->downs[key] = true;

  if (buttons.count(input->key))
    movement->direction.set(buttons.at(input->key));
  else
    movement->direction.set(Vector2::ZERO);
}
bool InputSystem::filter(Entity* entity) const {
  return entity->hasComponent<Movement>() && entity->hasComponent<InputKeyboard>();
}
