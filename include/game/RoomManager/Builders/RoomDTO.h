//
// Created by AsTeFu on 24.07.2019.
//

#ifndef INCLUDE_GAME_ROOMMANAGER_BUILDERS_ROOMDTO_H_
#define INCLUDE_GAME_ROOMMANAGER_BUILDERS_ROOMDTO_H_

#include <map>
#include <utility>
#include <vector>
#include "Utilities/Vector2.h"

class RoomDTO {
  int _width;
  int _height;
  std::map<char, std::vector<Vector2>> _listObjects;

 public:
  // TODO(AsTeFu): так копируется или нет
  explicit RoomDTO(std::map<char, std::vector<Vector2>> list, int width, int height)
      : _width(width), _height(height), _listObjects(std::move(list)) {}

  const std::map<char, std::vector<Vector2>>& getListObjects() const {
    return _listObjects;
  }
  int getWidth() const {
    return _width;
  }
  int getHegiht() const {
    return _height;
  }
};

#endif  // INCLUDE_GAME_ROOMMANAGER_BUILDERS_ROOMDTO_H_
