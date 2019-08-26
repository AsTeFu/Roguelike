//
// Created by AsTeFu on 24.07.2019.
//
#ifndef INCLUDE_GAME_ROOMMANAGER_BUILDERS_ROOMREADER_H_
#define INCLUDE_GAME_ROOMMANAGER_BUILDERS_ROOMREADER_H_

#include <string>
#include "game/RoomManager/Builders/RoomDTO.h"

class RoomReader {
 public:
  RoomDTO readerRoom(const std::string&);
};

#endif  // INCLUDE_GAME_ROOMMANAGER_BUILDERS_ROOMREADER_H_
