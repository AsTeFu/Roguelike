//
// Created by AsTeFu on 11.08.2019.
//

#include "game/Systems/BackpackOpenSystem.h"
#include <game/Components/ItemComponents/InventoryComponent.h>
#include <game/Components/PlayerComponents/PlayerComponent.h>
#include <game/Utility/DTO/BackpackDTO.h>
#include <game/Utility/Input.h>
#include "ecs/EntityManager.h"

bool BackpackOpenSystem::filter(Entity* entity) const {
  return entity->hasComponent<PlayerComponent>() && entity->hasComponent<InventoryComponent>();
}
void BackpackOpenSystem::update(Entity* entity) {
  // entity->getComponent<InventoryComponent>()->maxItems =
  //    entity->getComponent<SpecialComponent>()->getValue(STRENGTH) / 2;

  if (Input::getKey(KeyCode::I)) {
    getSceneManager()->getContext()->addObject<BackpackDTO>(entity);
    getSceneManager()->switchScene("Backpack");
  }
}
