//
// Created by AsTeFu on 09.08.2019.
//

#ifndef INCLUDE_GAME_UTILITY_DTO_PLAYERDTO_H_
#define INCLUDE_GAME_UTILITY_DTO_PLAYERDTO_H_

#include <game/Components/ItemComponents/InventoryComponent.h>
#include <game/Components/ItemComponents/SpecialComponent.h>
#include <game/Components/ItemComponents/WeaponComponent.h>
#include <game/Components/PlayerComponents/AbilitiesComponent.h>
#include <game/Components/PlayerComponents/LevelComponent.h>
#include <game/Utility/DTO/ObjectDTO.h>
#include <string>
#include <utility>

class PlayerDTO : public ObjectDTO {
 public:
  std::string name;
  int cash;
  int food;
  int health;
  int steps;
  const WeaponComponent* weapon;
  const ArmorComponent* armor;
  const InventoryComponent* inventory;
  const SpecialComponent* special;
  const LevelComponent* level;
  const AbilitiesComponent* abilities;

  PlayerDTO(const string& name, int cash, int food, int health, int steps, const WeaponComponent* weapon,
            const ArmorComponent* armor, const InventoryComponent* inventory, const SpecialComponent* special,
            const LevelComponent* level, const AbilitiesComponent* abilities)
      : name(name),
        cash(cash),
        food(food),
        health(health),
        steps(steps),
        weapon(weapon),
        armor(armor),
        inventory(inventory),
        special(special),
        level(level),
        abilities(abilities) {}
};

#endif  // INCLUDE_GAME_UTILITY_DTO_PLAYERDTO_H_
