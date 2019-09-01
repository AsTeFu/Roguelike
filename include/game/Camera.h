//
// Created by AsTeFu on 13.07.2019.
//

#ifndef INCLUDE_GAME_CAMERA_H_
#define INCLUDE_GAME_CAMERA_H_

#include <game/Utility/Config.h>
#include "Utilities/Vector2.h"

class Camera {
 private:
  Vector2 _centerPosition;
  Vector2 _size;
  Vector2 _border;
  Vector2 _offset;

  explicit Camera(const Vector2& position)
      : _centerPosition(position),
        _size(Config::getInstance().sizeTerminal.getX() * Config::getInstance().area.getX() / 200,
              Config::getInstance().sizeTerminal.getY() * Config::getInstance().area.getY() / 200),
        _border(Config::getInstance().borderSize),
        _offset(_size.getX() - _centerPosition.getX(), _size.getY() - _centerPosition.getY()) {}
  Camera(const Camera& camera);

 public:
  const Vector2& getOffset() const;
  void updatePosition(const Vector2& actorPosition);
  static Camera& getInstance();
  void setStartPos(const Vector2& pos);
};

#endif  // INCLUDE_GAME_CAMERA_H_
