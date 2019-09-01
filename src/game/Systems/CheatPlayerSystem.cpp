//
// Created by AsTeFu on 19.08.2019.
//

#include "game/Systems/CheatPlayerSystem.h"
#include <game/Components/ItemComponents/WeaponComponent.h>
#include <game/Components/PlayerComponents/AbilitiesComponent.h>
#include <game/Components/PlayerComponents/LevelComponent.h>
#include <game/Components/PlayerComponents/PlayerComponent.h>
#include <game/Items/GeneratorInventoryItem.h>
#include <game/Utility/Input.h>

bool CheatPlayerSystem::filter(Entity* entity) const {
  return entity->hasComponent<PlayerComponent>();
}
void CheatPlayerSystem::update(Entity* entity) {
  if (Input::getKeyDown(KeyCode::T)) {
    GeneratorInventoryItem generator;
    entity->getComponent<WeaponComponent>()->weapon =
        std::unique_ptr<Weapon>(generator.generateWeapon(Sublime, Sublime));
  }

  if (Input::getKeyDown(KeyCode::Y)) {
    GeneratorInventoryItem generator;
    entity->getComponent<ArmorComponent>()->equipments.clear();
    entity->getComponent<ArmorComponent>()->equipments.emplace(
        Helmet, std::unique_ptr<Armor>(generator.generateArmor(Helmet, Sublime, Sublime)));

    entity->getComponent<ArmorComponent>()->equipments.emplace(
        Armour, std::unique_ptr<Armor>(generator.generateArmor(Armour, Sublime, Sublime)));

    entity->getComponent<ArmorComponent>()->equipments.emplace(
        Boots, std::unique_ptr<Armor>(generator.generateArmor(Boots, Sublime, Sublime)));
  }

  if (Input::getKeyDown(KeyCode::U)) {
    GeneratorInventoryItem generator;
    entity->getComponent<WeaponComponent>()->weapon = std::unique_ptr<Weapon>(generator.generateWeapon());
  }

  if (Input::getKeyDown(KeyCode::I)) {
    auto level = entity->getComponent<LevelComponent>();

    // TODO(AsTeFu): тут уровень
    if (level->addExperience()) {
      entity->getComponent<SpecialComponent>()->special.addAvailablePoint();
      entity->getComponent<AbilitiesComponent>()->available++;
    }
  }
}
