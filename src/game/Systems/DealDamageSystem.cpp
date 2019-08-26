//
// Created by AsTeFu on 09.08.2019.
//

#include "game/Systems/DealDamageSystem.h"
#include <game/Components/ArmorComponent.h>
#include <game/Components/HealthComponent.h>
#include <game/Components/ProtectComponent.h>
#include <game/Logs/GameLogger.h>
#include <game/Utility/Random.h>
#include "ecs/EntityManager.h"
#include "ecs/SystemManager.h"

bool DealDamageSystem::filter(Entity* entity) const {
  return entity->hasComponent<DamageEvent>();
}
void DealDamageSystem::update(Entity* entity) {
  auto event = entity->getComponent<DamageEvent>();

  if (!event->target->hasComponent<HealthComponent>()) {
    return;
  }

  auto targetHealth = event->target->getComponent<HealthComponent>();

  if (event->target->hasComponent<ArmorComponent>()) {
    auto armor = event->target->getComponent<ArmorComponent>();

    int dodge = 0;
    for (const auto& arm : armor->equipments) {
      dodge += arm.second->dodge;
    }

    if (Random::random(100) < dodge) {
      if (event->target->getID() == 1)
        GameLogger::getInstance().add("Player dodges from damage");
      else
        GameLogger::getInstance().add("Enemy dodges from damage");
      return;
    }
  }

  int damage = event->weapon->damage;

  if (Random::random(100) < event->weapon->chanceCritical) {
    if (event->target->getID() == 1)
      GameLogger::getInstance().add("Player receives double damage");
    else
      GameLogger::getInstance().add("Player deals double damage");
    damage *= 2;
  }

  if (event->target->hasComponent<ArmorComponent>()) {
    auto armor = event->target->getComponent<ArmorComponent>();

    int protect = 0;
    for (const auto& arm : armor->equipments) {
      protect += arm.second->protect;
    }

    damage -= protect;
  }

  if (damage > 0) {
    targetHealth->health -= damage;

    if (event->target->getID() == 1)
      GameLogger::getInstance().add("Enemy deals [color=red]" + std::to_string(damage) + "[/color] damage");
    else
      GameLogger::getInstance().add("Player deals [color=red]" + std::to_string(damage) + "[/color] damage");
  }
  // getSystemManager()->deleteEntity(entity->getID());
  getEntityManager()->deleteEntity(entity->getID());
  getSystemManager()->setComponents();
}
void DealDamageSystem::postUpdate(Entity* entity) {}
