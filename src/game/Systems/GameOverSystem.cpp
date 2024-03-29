//
// Created by AsTeFu on 11.08.2019.
//

#include "game/Systems/GameOverSystem.h"
#include <game/Components/BaseComponent/Transform.h>
#include <game/Components/BaseComponent/Trigger.h>
#include <game/Components/EnvironmentComponents/ExitComponent.h>
#include <game/Components/ItemComponents/HealthComponent.h>
#include <game/Components/PlayerComponents/PlayerComponent.h>
#include "game/RoomManager/RoomManager.h"

bool GameOverSystem::filter(Entity* entity) const {
  return entity->hasComponent<PlayerComponent>();
}
void GameOverSystem::postUpdate(Entity* entity) {
  // End game
  /* if (Room::countRoom > 10) {
    getSceneManager()->getContext()->addObject<PlayerDTO>(getRoomManager()->getPlayerInfo());
    getSceneManager()->switchScene("EndGame");
  } */

  // Проиграл по хп
  if (entity->hasComponent<HealthComponent>() && entity->getComponent<HealthComponent>()->health <= 0) {
    getSceneManager()->getContext()->addObject<PlayerDTO>(_roomManager->getCurrentPlayer());
    getSceneManager()->switchScene(gameOverScene);
  }
}
