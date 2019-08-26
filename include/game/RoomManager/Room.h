//
// Created by AsTeFu on 24.07.2019.
//

#ifndef INCLUDE_GAME_ROOMMANAGER_ROOM_H_
#define INCLUDE_GAME_ROOMMANAGER_ROOM_H_

#include <ecs/Engine.h>
#include <game/Items/GeneratorInventoryItem.h>
#include <game/Player/Special.h>
#include <game/Scenes/SceneManager.h>
#include <game/Utility/DTO/PlayerDTO.h>
#include <game/Utility/DTO/SpecialDTO.h>
#include <string>
#include "game/Utility/Display.h"

using std::vector;

enum DirectionExit { Right, Top, Left, Bottom };


class Room {
 private:
  int id;
  int _width;
  int _height;
  int exitID{0};
  Engine _engine;
  RoomManager* _roomManager;
  GeneratorInventoryItem _generator{};

 public:
  static int countRoom;
  Room(int width, int height, SceneManager* sceneManager, RoomManager* roomManager);

  PlayerDTO getPlayerDTO();
  void setPlayerDTO(const PlayerDTO& dto);
  Engine& getEngine();
  int getID();

  void start();
  void update();

  void activateSystem();

  void addSpecial(const SpecialDTO& specialDto);
  void addName(const string& name);
};

#endif  // INCLUDE_GAME_ROOMMANAGER_ROOM_H_
