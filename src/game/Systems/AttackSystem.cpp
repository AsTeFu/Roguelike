//
// Created by AsTeFu on 07.08.2019.
//

#include "game/Systems/AttackSystem.h"
#include <Utilities/Random.h>
#include <game/Components/AIController.h>
#include <game/Components/AttackComponent.h>
#include <game/Components/BaseComponent/Transform.h>
#include <game/Components/ItemComponents/HealthComponent.h>
#include <game/Components/ItemComponents/SpecialComponent.h>
#include <game/Components/ItemComponents/WeaponComponent.h>
#include <game/Components/PlayerComponents/AbilitiesComponent.h>
#include <game/Components/PlayerComponents/PlayerComponent.h>
#include <game/Logs/GameLogger.h>
#include <game/Utility/Input.h>
#include "ecs/EntityManager.h"
#include "ecs/SystemManager.h"

bool AttackSystem::filter(Entity* entity) const {
  return entity->hasComponent<AttackComponent>() && entity->hasComponent<AIController>();
}
void AttackSystem::preUpdate(Entity* entity) {
  // TODO(AsTeFu): разбить на две системы
  // игрок атакует противников
  // противники атакуют игрока
  // такое деление нужно, потому что противники не могут атаковать противников

  auto player = getEntityManager()->getByTag("player")[0];
  auto playerPos = player->getComponent<Transform>();
  auto entityPos = entity->getComponent<Transform>();
  auto entityAttack = entity->getComponent<AIController>();

  if ((playerPos->position - entityPos->position).len2() <= 2) {
    if (entityAttack->lastPosition == playerPos->position) attack(entity, player);
    entityAttack->lastPosition.set(playerPos->position);
    if (Input::getKey(KeyCode::Space)) attack(player, entity);
  }
}

void AttackSystem::attack(Entity* entity, Entity* target) {
  if (!target->hasComponent<HealthComponent>() || !entity->hasComponent<WeaponComponent>()) return;
  auto weapon = entity->getComponent<WeaponComponent>()->weapon.get();

  auto targetHealth = target->getComponent<HealthComponent>();

  auto entitySpecial = entity->getComponent<SpecialComponent>();
  auto targetSpecial = entity->getComponent<SpecialComponent>();

  if (target->hasComponent<ArmorComponent>()) {
    auto armor = target->getComponent<ArmorComponent>();

    int dodge = 0;
    for (const auto& arm : armor->equipments) {
      dodge += arm.second->dodge;
    }

    if (Random::random(100) + targetSpecial->getValue(LUCK) + targetSpecial->getValue(AGILITY) < dodge) {
      if (target->getID() == 1)
        GameLogger::getInstance().add("Player dodges from damage");
      else
        GameLogger::getInstance().add("Enemy dodges from damage");
      return;
    }
  }

  int damage = weapon->damage;
  int bonusCritical = 0;

  if (entity->getID() == 1 && entity->getComponent<AbilitiesComponent>()->hasAbility("Кровавая баня")) {
    damage = static_cast<int>(120.0 * damage / 100.0);
  }

  if (entity->getID() == 1 && entity->getComponent<AbilitiesComponent>()->hasAbility("Точность")) {
    bonusCritical = 15;
  }

  if (Random::random(100) < weapon->chanceCritical + entitySpecial->getValue(LUCK) * 2 + bonusCritical) {
    if (target->getID() == 1)
      GameLogger::getInstance().add("Player receives double damage");
    else
      GameLogger::getInstance().add("Player deals double damage");
    damage *= 2;
  }

  if (target->hasComponent<ArmorComponent>()) {
    auto armor = target->getComponent<ArmorComponent>();

    int protect = 0;
    for (const auto& arm : armor->equipments) {
      protect += arm.second->protect;
    }

    damage -= protect - targetSpecial->getValue(ENDURANCE) * 2;
  }

  damage += Random::random(10 + entitySpecial->getValue(LUCK)) + entitySpecial->getValue(STRENGTH) * 2;

  if (damage > 0) {
    targetHealth->health -= damage;

    if (target->getID() == 1)
      GameLogger::getInstance().add("Enemy deals [color=red]" + std::to_string(damage) + "[/color] damage");
    else
      GameLogger::getInstance().add("Player deals [color=red]" + std::to_string(damage) + "[/color] damage");
  } else {
    if (target->getID() == 1)
      GameLogger::getInstance().add("Броня не пробита! P.S ваша броня");
    else
      GameLogger::getInstance().add("Есть попадание по врагу! P.S без урона");
  }
}
