//
// Created by AsTeFu on 24.07.2019.
//

#ifndef INCLUDE_GAME_ROOMMANAGER_BUILDERS_ROOMBUILDER_H_
#define INCLUDE_GAME_ROOMMANAGER_BUILDERS_ROOMBUILDER_H_

#include <ecs/Engine.h>
#include <game/Items/GeneratorInventoryItem.h>
#include <game/Scenes/SceneManager.h>
#include <roomcreator/Components/StructureComponent.h>
#include <functional>
#include <map>
#include "game/RoomManager/Builders/RoomDTO.h"

using std::bind;
using std::function;
using std::make_pair;
using std::map;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::placeholders::_4;

// class RoomManager;
class Room;

class RoomBuilder {
 private:
  GeneratorInventoryItem _generator{};
  map<char, function<void(int, int, Tile, Engine* engine)> > _builds;

  void addCoin(int x, int y, Tile tile, Engine* engine);
  void addFood(int x, int y, Tile tile, Engine* engine);
  void addHealth(int x, int y, Tile tile, Engine* engine);
  void addWall(int x, int y, Tile tile, Engine* engine);
  void addNextRoomExit(int x, int y, Tile tile, Engine* engine);
  void addPreviousRoomExit(int x, int y, Tile tile, Engine* engine);
  void addEnemy(int x, int y, Tile tile, Engine* engine);
  void addChest(int x, int y, Tile tile, Engine* engine);
  void addShop(int x, int y, Tile tile, Engine* engine);
  void addPoint(int x, int y, Tile tile, Engine* engine);
  void addPlayer(int x, int y, Tile tile, Engine* engine);

 public:
  RoomBuilder();
  Room* build(StructureComponent* const structure, SceneManager* sceneManager, RoomManager* roomManager);
  Special generateSpecialEnemy() const;
  void transferPlayer(Entity* player, Room* currentRoom) const;
  void startPlayer(Entity* player, SceneManager* sceneManager);
};

#endif  // INCLUDE_GAME_ROOMMANAGER_BUILDERS_ROOMBUILDER_H_
