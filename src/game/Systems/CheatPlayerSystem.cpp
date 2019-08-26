//
// Created by AsTeFu on 19.08.2019.
//

#include "game/Systems/CheatPlayerSystem.h"
#include <BearLibTerminal.h>
#include <game/Components/AbilitiesComponent.h>
#include <game/Components/LevelComponent.h>
#include <game/Components/PlayerComponent.h>
#include <game/Components/WeaponComponent.h>
#include <game/Items/GeneratorInventoryItem.h>
#include <game/Utility/Input.h>

bool CheatPlayerSystem::filter(Entity* entity) const {
  return entity->hasComponent<PlayerComponent>();
}
void CheatPlayerSystem::update(Entity* entity) {
  if (Input::isPressed(TK_T)) {
    GeneratorInventoryItem generator;
    entity->getComponent<WeaponComponent>()->weapon =
        std::unique_ptr<Weapon>(generator.generateWeapon(Sublime, Sublime));
  }

  if (Input::isPressed(TK_Y)) {
    GeneratorInventoryItem generator;
    entity->getComponent<ArmorComponent>()->equipments.clear();
    entity->getComponent<ArmorComponent>()->equipments.emplace(
        Helmet, std::unique_ptr<Armor>(generator.generateArmor(Helmet, Sublime, Sublime)));

    entity->getComponent<ArmorComponent>()->equipments.emplace(
        Armour, std::unique_ptr<Armor>(generator.generateArmor(Armour, Sublime, Sublime)));

    entity->getComponent<ArmorComponent>()->equipments.emplace(
        Boots, std::unique_ptr<Armor>(generator.generateArmor(Boots, Sublime, Sublime)));
  }

  if (Input::isPressed(TK_U)) {
    GeneratorInventoryItem generator;
    entity->getComponent<WeaponComponent>()->weapon = std::unique_ptr<Weapon>(generator.generateWeapon());
  }

  if (Input::isPressed(TK_L)) {
    auto level = entity->getComponent<LevelComponent>();
    if (level->addExperience(level->maxExperience - level->currentExperience + 1)) {
      entity->getComponent<SpecialComponent>()->special.addAvailablePoint();
      entity->getComponent<AbilitiesComponent>()->available++;
    }
  }
}
