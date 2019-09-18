//
// Created by AsTeFu on 24.07.2019.
//

#include <game/RoomManager/Builders/RoomBuilder.h>
#include <game/RoomManager/Room.h>
#include <game/Systems/AIMovementSystem.h>
#include <game/Systems/AbilityOpenSystem.h>
#include <game/Systems/AttackSystem.h>
#include <game/Systems/BackpackOpenSystem.h>
#include <game/Systems/CameraSystem.h>
#include <game/Systems/CashTriggerSystem.h>
#include <game/Systems/CheatPlayerSystem.h>
#include <game/Systems/ChestOpenSystem.h>
#include <game/Systems/CollisionSystem.h>
#include <game/Systems/DeadSystem.h>
#include <game/Systems/ExitSystem.h>
#include <game/Systems/FindEventSystem.h>
#include <game/Systems/FoodTriggerSystem.h>
#include <game/Systems/GameOverSystem.h>
#include <game/Systems/InputSystem.h>
#include <game/Systems/LightingSystem.h>
#include <game/Systems/MedkitTriggerSystem.h>
#include <game/Systems/MovementSystem.h>
#include <game/Systems/RenderSystems/GraphicRenderSystem.h>
#include <game/Systems/RenderSystems/MainRenderSystem.h>
#include <game/Systems/RenderSystems/PointRenderSystem.h>
#include <game/Systems/RenderSystems/RenderMoveableSystem.h>
#include <game/Systems/RenderSystems/RenderPlayerSystem.h>
#include <game/Systems/RenderSystems/RenderSystem.h>
#include <game/Systems/RenderSystems/TextRenderSystem.h>
#include <game/Systems/RenderSystems/WallRenderSystem.h>
#include <game/Systems/ShopOpenSystem.h>
#include <game/Systems/StarvationSystem.h>
#include <game/Systems/StepsSystem.h>
#include <game/Utility/DTO/RenderModeDTO.h>
#include <vector>
#include "game/RoomManager/RoomManager.h"

int Room::countRoom = 0;

Room::Room(int width, int height, SceneManager* sceneManager, RoomManager* roomManager)
    : id(++countRoom),
      _width(width),
      _height(height),
      _engine(sceneManager),
      _roomManager(roomManager),
      _sceneManager(sceneManager) {}

void Room::start() {
  _engine.update();
}
void Room::update() {
  _engine.update();
}

void Room::activateSystem() {
  _engine.getSystemManager()->addSystem<InputSystem>();
  _engine.getSystemManager()->addSystem<CheatPlayerSystem>();
  _engine.getSystemManager()->addSystem<BackpackOpenSystem>();
  _engine.getSystemManager()->addSystem<AbilityOpenSystem>();
  _engine.getSystemManager()->addSystem<AIMovementSystem>();

  _engine.getSystemManager()->addSystem<CollisionSystem>();
  _engine.getSystemManager()->addSystem<MovementSystem>();
  _engine.getSystemManager()->addSystem<StepsSystem>();
  _engine.getSystemManager()->addSystem<StarvationSystem>();
  _engine.getSystemManager()->addSystem<GameOverSystem>(_roomManager);

  _engine.getSystemManager()->addSystem<ChestOpenSystem>();
  _engine.getSystemManager()->addSystem<ShopOpenSystem>();

  _engine.getSystemManager()->addSystem<AttackSystem>();
  _engine.getSystemManager()->addSystem<DeadSystem>();

  _engine.getSystemManager()->addSystem<CashTriggerSystem>();
  _engine.getSystemManager()->addSystem<MedkitTriggerSystem>();
  _engine.getSystemManager()->addSystem<FoodTriggerSystem>();

  _engine.getSystemManager()->addSystem<CameraSystem>();
  // _engine.getSystemManager()->addSystem<PointRenderSystem>();
  _engine.getSystemManager()->addSystem<LightingSystem>(_width);
  _engine.getSystemManager()->addSystem<MainRenderSystem>(
      vector<IRenderSystem*>{new TextRenderSystem(_engine.getEntityManager()),
                             new GraphicRenderSystem(_engine.getEntityManager())},
      _sceneManager->getContext()->getObject<RenderModeDTO>()->mode);
  // _engine.getSystemManager()->addSystem<WallRenderSystem>();
  // _engine.getSystemManager()->addSystem<RenderSystem>();
  // _engine.getSystemManager()->addSystem<RenderMoveableSystem>();
  // _engine.getSystemManager()->addSystem<RenderPlayerSystem>();
  _engine.getSystemManager()->addSystem<FindEventSystem>();
  _engine.getSystemManager()->addSystem<ExitSystem>(_roomManager);
}

Engine& Room::getEngine() {
  return _engine;
}
int Room::getID() {
  return id;
}
