//
// Created by AsTeFu on 07.08.2019.
//

#include "game/Systems/ExitSystem.h"
#include <game/Components/ExitComponent.h>
#include <game/Components/Transform.h>
#include <game/Components/Trigger.h>
#include <game/ECSUtility.h>
#include <game/Utility/Input.h>
#include <game/Utility/Random.h>
#include <string>
#include <vector>
#include "game/RoomManager/RoomManager.h"

bool ExitSystem::filter(Entity* entity) const {
  return entity->hasComponent<ExitComponent>() && entity->hasComponent<Trigger>() && entity->hasComponent<Transform>();
}
void ExitSystem::postUpdate(Entity* entity) {
  if (isActivate) return;
  auto transform = entity->getComponent<Transform>();
  auto player = _roomManager->getCurrentPlayer();

  if (transform->position == player->getComponent<Transform>()->position) {
    isActivate = true;
    auto currentRoomExit = entity->getComponent<ExitComponent>();

    // auto playerDTO = _roomManager->getCurrentPlayer();
    // Entity* newPlayer;

    if (currentRoomExit->direction) {
      _roomManager->nextRoom();
      std::cout << "next room" << std::endl;
      // newPlayer = ECSUtility::copyPlayer(playerDTO, _roomManager->getCurrentPlayer());
    } else {
      std::cout << "previous room" << std::endl;
      _roomManager->previousRoom();
      // newPlayer = _roomManager->getCurrentPlayer();
    }
    // auto newPlayer = Entity::copyEntity(playerDTO, _roomManager->getCurrentPlayer());

    std::string tag = currentRoomExit->direction ? "<" : ">";
    Vector2 dir;
    if (Input::isPressed(TK_LEFT)) dir = Vector2::LEFT;
    if (Input::isPressed(TK_RIGHT)) dir = Vector2::RIGHT;
    if (Input::isPressed(TK_UP)) dir = Vector2::UP;
    if (Input::isPressed(TK_DOWN)) dir = Vector2::DOWN;

    Vector2 startPosition = _roomManager->getCurrentRoom()
                                ->getEngine()
                                .getEntityManager()
                                ->getByTag(tag)[0]
                                ->getComponent<Transform>()
                                ->position;
    auto transformPlayer = _roomManager->getCurrentPlayer()->getComponent<Transform>();
    transformPlayer->position.set(startPosition + dir);

    _roomManager->getCurrentRoom()
        ->getEngine()
        .getEntityManager()
        ->getByTag("camera")[0]
        ->getComponent<Transform>()
        ->position.set(transformPlayer->position);
    terminal_clear();
    // _roomManager->update();
    _roomManager->getCurrentRoom()->activateSystem();
  }
}
void ExitSystem::preUpdate(Entity* entity) {
  isActivate = false;
}
