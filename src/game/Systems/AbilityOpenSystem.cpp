//
// Created by AsTeFu on 20.08.2019.
//

#include "game/Systems/AbilityOpenSystem.h"
#include <ecs/EntityManager.h>
#include <game/Components/PlayerComponents/PlayerComponent.h>
#include <game/Utility/DTO/EnhanceDTO.h>
#include <game/Utility/Input.h>

bool AbilityOpenSystem::filter(Entity* entity) const {
  return entity->hasComponent<PlayerComponent>();
}
void AbilityOpenSystem::update(Entity* entity) {
  if (Input::getKey(KeyCode::O)) {
    getSceneManager()->getContext()->addObject<EnhanceDTO>(
        entity->getComponent<SpecialComponent>(), entity->getComponent<AbilitiesComponent>(),
        entity->getComponent<LevelComponent>(), entity->getComponent<HealthComponent>());
    getSceneManager()->switchScene("Ability");
  }
}
