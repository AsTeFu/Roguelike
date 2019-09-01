//
// Created by AsTeFu on 07.08.2019.
//

#include "game/Systems/ExitSystem.h"
#include <utilities/Random.h>
#include <game/Components/BaseComponent/Transform.h>
#include <game/Components/BaseComponent/Trigger.h>
#include <game/Components/EnvironmentComponents/ExitComponent.h>
#include <game/ECSUtility.h>
#include <game/Utility/Input.h>
#include <utilities/Terminal.h>
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
    if (Input::getKey(KeyCode::LeftArrow)) dir = Vector2::LEFT;
    if (Input::getKey(KeyCode::RightArrow)) dir = Vector2::RIGHT;
    if (Input::getKey(KeyCode::UpArrow)) dir = Vector2::UP;
    if (Input::getKey(KeyCode::DownArrow)) dir = Vector2::DOWN;

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
    Terminal::clear();
    // _roomManager->update();
    // _roomManager->getCurrentRoom()->activateSystem();
    _roomManager->getCurrentRoom()->getEngine().getSystemManager()->setComponents();
  }
}
void ExitSystem::preUpdate(Entity* entity) {
  isActivate = false;
}
