//
// Created by AsTeFu on 11.08.2019.
//

#include "game/Systems/MedkitTriggerSystem.h"
#include <game/Components/AbilitiesComponent.h>
#include <game/Components/HealthComponent.h>
#include <game/Components/HealthItemComponent.h>
#include <game/Components/SpecialComponent.h>
#include <game/Components/Transform.h>
#include <game/Components/Trigger.h>
#include <game/Logs/GameLogger.h>
#include <algorithm>
#include "ecs/EntityManager.h"
#include "ecs/SystemManager.h"

bool MedkitTriggerSystem::filter(Entity* entity) const {
  return entity->hasComponent<Trigger>() && entity->hasComponent<HealthItemComponent>();
}
void MedkitTriggerSystem::update(Entity* entity) {
  auto medkit = entity->getComponent<HealthItemComponent>();
  auto transform = entity->getComponent<Transform>();

  auto player = getEntityManager()->getByTag("player")[0];

  if (transform->position == player->getComponent<Transform>()->position) {
    if (player->hasComponent<HealthComponent>()) {
      // TODO(AsTeFu): special
      auto special = player->getComponent<SpecialComponent>();

      int abilityHealth = 0;
      if (player->getComponent<AbilitiesComponent>()->hasAbility("Ускоренный метаболизм")) abilityHealth = 50;

      int addHealth = medkit->health + special->getValue(INTELLIGENCE) * 5 + special->getValue(LUCK) * 2;
      addHealth = static_cast<int>(addHealth * (100 + abilityHealth) / 100.0);
      player->getComponent<HealthComponent>()->health += addHealth;

      GameLogger::getInstance().add("[color=red]Medkit[/color] was picked up [color=red](" + std::to_string(addHealth) +
                                    ")");
    }

    getEntityManager()->deleteEntity(entity->getID());
    getSystemManager()->deleteEntity(entity->getID());
  }
}
