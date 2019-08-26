//
// Created by AsTeFu on 10.07.2019.
//
#include "game/Utility/Input.h"
#include <BearLibTerminal.h>

Vector2 Input::axis = Vector2::ZERO;

void Input::updateAxis() {
  if (isPressed(TK_LEFT))
    axis.set(-1, 0);
  else if (isPressed(TK_RIGHT))
    axis.set(1, 0);
  else if (isPressed(TK_UP))
    axis.set(0, -1);
  else if (isPressed(TK_DOWN))
    axis.set(0, 1);
  else
    axis.set(0, 0);
}
bool Input::isPressed(int button) {
  return terminal_peek() == button;
}
const Vector2& Input::getAxis() {
  return axis;
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
