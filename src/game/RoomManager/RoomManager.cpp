//
// Created by AsTeFu on 24.07.2019.
//

#include "game/RoomManager/RoomManager.h"
#include <game/Components/RenderType.h>
#include <game/ECSUtility.h>
#include <game/Scenes/BackpackScene.h>
#include <game/Utility/DTO/SpecialDTO.h>
#include <game/Utility/Utility.h>
#include <utilities/FileUtility.h>
#include <utilities/Random.h>
#include <string>
#include "game/RoomManager/Builders/RoomReader.h"
#include "game/RoomManager/Room.h"
#include "game/Scenes/EndGameScene.h"

RoomManager::RoomManager(SceneManager* sceneManager) : sceneManager(sceneManager) {}

void RoomManager::update() {
  _currentRoom->update();
}

Room* RoomManager::getCurrentRoom() {
  return _currentRoom;
}
/*
void RoomManager::addSpecial(const SpecialDTO& special) {
  _currentRoom->addSpecial(special);
}
Room* RoomManager::getNewRoom() {
  return _builder.build(_roomsPatterns[Random::random(_roomsPatterns.sizeShop())].get(), sceneManager, this);
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
  auto oldPlayer = getCurrentPlayer();
  if (_currentID == _rooms.size()) {
    createRoom();
    _currentID++;
    ECSUtility::copyPlayer(oldPlayer, getCurrentPlayer());
  } else {
    _currentRoom = _rooms[++_currentID].get();
    ECSUtility::transferPlayer(oldPlayer, getCurrentPlayer());
  }
  std::cout << "Current room: " << _currentID << std::endl;
}

void RoomManager::previousRoom() {
  if (_currentID > 1) {
    auto oldPlayer = getCurrentPlayer();
    _currentRoom = _rooms[--_currentID].get();
    ECSUtility::transferPlayer(oldPlayer, getCurrentPlayer());
    std::cout << "Current room: " << _currentID << std::endl;
  }
}
Entity* RoomManager::getCurrentPlayer() const {
  return _currentRoom->getEngine().getEntityManager()->getByTag("player")[0];
}
void RoomManager::start() {
  if (Room::countRoom == 0) {
    auto roomsNames = Utility::readDirection("Resource\\Rooms");
    for (const auto& name : roomsNames) {
      _roomsPatterns.emplace_back(
          std::unique_ptr<StructureComponent>(FileUtility::readRoom("Resource\\Rooms\\" + name)));
    }

    createRoom();
    EntityManager* entityManager = _rooms[1]->getEngine().getEntityManager();
    SystemManager* systemManager = _rooms[1]->getEngine().getSystemManager();
    for (const auto& exit : entityManager->getByTag("<")) {
      size_t idExit = exit->getID();
      entityManager->deleteEntity(idExit);
      systemManager->deleteEntity(idExit);
    }
    systemManager->setComponents();
  }
}
