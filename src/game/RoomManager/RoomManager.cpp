//
// Created by AsTeFu on 24.07.2019.
//

#include "game/RoomManager/RoomManager.h"
#include <game/Scenes/BackpackScene.h>
#include <game/Utility/DTO/SpecialDTO.h>
#include <game/Utility/Random.h>
#include <game/Utility/Utility.h>
#include <roomcreator/FileUtility.h>
#include <string>
#include "game/RoomManager/Builders/RoomReader.h"
#include "game/RoomManager/Room.h"
#include "game/Scenes/EndGameScene.h"

RoomManager::RoomManager(SceneManager* sceneManager) : sceneManager(sceneManager) {}

void RoomManager::update() {
  _currentRoom->update();
}
PlayerDTO RoomManager::getPlayerInfo() const {
  return _currentRoom->getPlayerDTO();
}

Room* RoomManager::getCurrentRoom() {
  return _currentRoom;
}
/*
void RoomManager::addSpecial(const SpecialDTO& special) {
  _currentRoom->addSpecial(special);
}
Room* RoomManager::getNewRoom() {
  return _builder.build(_roomsPatterns[Random::random(_roomsPatterns.size())].get(), sceneManager, this);
}

void RoomManager::addName(const std::string& name) {
  _currentRoom->addName(name);
} */

int RoomManager::createRoom() {
  int rnd;
  do {
    rnd = Random::random(_roomsPatterns.size());
  } while (rnd == lastPatterID);

  std::cout << "Create room" << std::endl;

  _rooms[Room::countRoom] = unique_ptr<Room>(_builder.build(_roomsPatterns[rnd].get(), sceneManager, this));
  _currentRoom = _rooms[Room::countRoom].get();
  lastPatterID = rnd;
  return Room::countRoom;
}
void RoomManager::nextRoom() {
  if (_currentID == _rooms.size()) {
    createRoom();
    _currentID++;
  } else {
    _currentRoom = _rooms[++_currentID].get();
  }
}
void RoomManager::previousRoom() {
  if (_currentID > 1) {
    _currentRoom = _rooms[--_currentID].get();
  }
}
Entity* RoomManager::getCurrentPlayer() const {
  return _currentRoom->getEngine().getEntityManager()->getByTag("player")[0];
}
void RoomManager::start() {
  if (Room::countRoom == 0) {
    auto rooms = Utility::readNames("Resource/Rooms");
    for (const auto& name : rooms) {
      _roomsPatterns.emplace_back(std::unique_ptr<StructureComponent>(FileUtility::readRoom("Resource/Rooms/" + name)));
    }
    // _rooms[Room::countRoom] = unique_ptr<Room>(_builder.build(_roomsPatterns[0].get(), sceneManager, this));
    // _currentRoom = _rooms[Room::countRoom].get();
    createRoom();
  }
}
