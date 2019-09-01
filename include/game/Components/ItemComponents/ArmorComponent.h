//
// Created by  on 09.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_ITEMCOMPONENTS_ARMORCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_ITEMCOMPONENTS_ARMORCOMPONENT_H_

#include <game/Components/PlayerComponents/StarvationComponent.h>
#include <game/Components/PlayerComponents/WalletComponent.h>
#include <game/Items/Armor.h>
#include <game/Items/InventoryItem.h>
#include <game/Utility/Config.h>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "ecs/IComponent.h"

class ArmorComponent : public IComponent {
 public:
  std::map<Slot, std::unique_ptr<Armor>> equipments;
  explicit ArmorComponent(const std::vector<Armor*>& armors) {
    for (const auto& armor : armors) {
      equipments[armor->slot] = std::unique_ptr<Armor>(armor);
    }
  }
  ArmorComponent(const ArmorComponent& armorComponent) {
    for (const auto& equipment : armorComponent.equipments) {
      equipments[equipment.first] = std::unique_ptr<Armor>(equipment.second.get());
    }
  }

  int getProtect() const {
    int protect = 0;
    for (const auto& equipment : equipments) {
      protect += equipment.second->protect;
    }
    return protect;
  }
  int getDodge() const {
    int protect = 0;
    for (const auto& equipment : equipments) {
      protect += equipment.second->dodge;
    }
    return protect;
  }

  std::vector<Armor*> getEquipments() {
    std::vector<Armor*> armors;
    for (const auto& armor : equipments) {
      armors.push_back(armor.second.get());
    }
    return armors;
  }
  void setEquipments(ArmorComponent* armorEquipments) {
    for (auto& equipment : armorEquipments->equipments) {
      equipments[equipment.first].swap(equipment.second);
    }
  }
};

#endif  // INCLUDE_GAME_COMPONENTS_ITEMCOMPONENTS_ARMORCOMPONENT_H_
