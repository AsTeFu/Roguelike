//
// Created by AsTeFu on 10.07.2019.
//
#include "game/Utility/Input.h"
#include <BearLibTerminal.h>
#include <map>
#include <vector>

std::map<int, bool> Input::keys = std::map<int, bool>();

bool Input::getKey(const KeyCode& code) {
  return terminal_peek() == code.key;
}
bool Input::getKeyUp(const KeyCode& code) {
  return terminal_peek() == (code.key | TK_KEY_RELEASED);
}
bool Input::isExit() {
  return false;
}
bool Input::mouseLeft() {
  return terminal_check(TK_MOUSE_LEFT);
}
bool Input::mouseRight() {
  return terminal_check(TK_MOUSE_RIGHT);
}
bool Input::hasInput() {
  return terminal_has_input();
}
int Input::read() {
  return terminal_read();
}
bool Input::getKeyDown(const KeyCode& code) {
  if (code.key == terminal_peek() && !keys[code.key]) {
    keys[code.key] = true;
    return keys[code.key];
  }
  return false;
}
void Input::updateKeys() {
  int peek = terminal_peek();
  for (auto& key : keys) {
    if ((key.first | TK_KEY_RELEASED) == peek) {
      key.second = false;
    }
  }
}
bool Input::check(const KeyCode& keyCode) {
  return terminal_check(keyCode.key);
}
bool Input::isMouseWheel() {
  return terminal_peek() == TK_MOUSE_SCROLL;
}
int Input::getMouseWheel() {
  return terminal_state(TK_MOUSE_WHEEL);
}
Vector2 Input::getMousePosition() {
  int x = terminal_state(TK_MOUSE_X);
  int y = terminal_state(TK_MOUSE_Y);

  return {x, y};
}
