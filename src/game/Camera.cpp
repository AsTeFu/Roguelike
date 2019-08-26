//
// Created by AsTeFu on 13.07.2019.
//

#include "game/Camera.h"
#include <game/Utility/ConfigTerminal.h>

const Vector2& Camera::getOffset() const {
  return _offset;
}

int normalize(int num) {
  if (num == 0) return 0;
  if (num > 0) return 1;
  return -1;
}
void Camera::updatePosition(const Vector2& actorPosition) {
  int lengthX = _centerPosition.getX() - actorPosition.getX();
  int lengthY = _centerPosition.getY() - actorPosition.getY();

  if (abs(lengthX) > _border.getX()) _centerPosition.setX(_centerPosition.getX() - normalize(lengthX));
  if (abs(lengthY) > _border.getY()) _centerPosition.setY(_centerPosition.getY() - normalize(lengthY));

  _offset.set(_size.getX() - _centerPosition.getX(), _size.getY() - _centerPosition.getY());
}
Camera& Camera::getInstance() {
  static Camera instance(ConfigTerminal::startPos);
  return instance;
}
void Camera::setStartPos(const Vector2& pos) {
    _centerPosition.set(pos);
}
