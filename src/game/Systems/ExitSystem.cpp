//
// Created by AsTeFu on 07.08.2019.
//

#include "game/Systems/ExitSystem.h"
#include <game/Components/ExitComponent.h>
#include <game/Components/Transform.h>
#include <game/Components/Trigger.h>
#include <game/Utility/Input.h>
#include <game/Utility/Random.h>
#include <string>
#include "game/RoomManager/RoomManager.h"

bool ExitSystem::filter(Entity* entity) const {
  return entity->hasComponent<ExitComponent>() && entity->hasComponent<Trigger>() && entity->hasComponent<Transform>();
}
void ExitSystem::postUpdate(Entity* entity) {
  auto transform = entity->getComponent<Transform>();
  auto player = getEntityManager()->getByTag("player")[0];

  if (transform->position == player->getComponent<Transform>()->position) {
    auto currentRoomExit = entity->getComponent<ExitComponent>();

    auto playerDTO = _roomManager->getCurrentPlayer();

    if (currentRoomExit->direction) {
      _roomManager->nextRoom();
      std::cout << "next room" << std::endl;
    } else {
      std::cout << "previous room" << std::endl;
      _roomManager->previousRoom();
    }
    auto newPlayer = Entity::copyEntity(playerDTO, _roomManager->getCurrentPlayer());

    std::string tag = currentRoomExit->direction ? "<" : ">";
    Vector2 dir;
    if (Input::isPressed(TK_LEFT)) dir = Vector2::LEFT;
    if (Input::isPressed(TK_RIGHT)) dir = Vector2::RIGHT;
    if (Input::isPressed(TK_UP)) dir = Vector2::UP;
    if (Input::isPressed(TK_DOWN)) dir = Vector2::DOWN;

    // Vector2 startPosition = _roomManager->getCurrentRoom()
    //                             ->getEngine()
    //                             .getEntityManager()
    //                             ->getByTag(tag)[0]
    //                             ->getComponent<Transform>()
    //                             ->position;
    auto transformPlayer = newPlayer->getComponent<Transform>();
    transformPlayer->position.set(2, 2);

    _roomManager->getCurrentRoom()
        ->getEngine()
        .getEntityManager()
        ->getByTag("camera")[0]
        ->getComponent<Transform>()
        ->position.set(transformPlayer->position);
    terminal_clear();
    _roomManager->update();
  }
}
