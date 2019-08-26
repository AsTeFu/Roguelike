//
// Created by AsTeFu on 24.07.2019.
//

#ifndef INCLUDE_GAME_ROOMMANAGER_ROOMMANAGER_H_
#define INCLUDE_GAME_ROOMMANAGER_ROOMMANAGER_H_

#include <game/RoomManager/Builders/RoomBuilder.h>
#include <game/RoomManager/Builders/RoomDTO.h>
#include <game/Scenes/SceneManager.h>
#include <game/Utility/DTO/PlayerDTO.h>
#include <game/Utility/DTO/SpecialDTO.h>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "game/RoomManager/Room.h"

class Room;

using std::unique_ptr;
using std::vector;

class RoomManager {
 private:
  Room* _currentRoom;
  size_t _currentID{1};
  std::map<int, unique_ptr<Room>> _rooms;

  RoomBuilder _builder;
  // vector<RoomDTO> _roomsPatterns;
  vector<unique_ptr<StructureComponent>> _roomsPatterns;

  SceneManager* const sceneManager;
  int lastPatterID{-1};

 public:
  explicit RoomManager(SceneManager* sceneManager);
  void update();
  void start();
  PlayerDTO getPlayerInfo() const;
  // void switchRoom(int id);
  void nextRoom();
  int createRoom();
  void previousRoom();
  // Room* getNewRoom();
  Room* getCurrentRoom();
  // void addSpecial(const SpecialDTO& special);
  // void addName(const std::string& name);
  Entity* getCurrentPlayer() const;
};

#endif  // INCLUDE_GAME_ROOMMANAGER_ROOMMANAGER_H_
