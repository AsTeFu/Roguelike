//
// Created by AsTeFu on 11.08.2019.
//

#ifndef INCLUDE_GAME_UTILITY_DTO_BACKPACKDTO_H_
#define INCLUDE_GAME_UTILITY_DTO_BACKPACKDTO_H_

#include <game/Components/ArmorComponent.h>
#include <game/Components/InventoryComponent.h>
#include <game/Components/SpecialComponent.h>
#include <game/Components/WeaponComponent.h>
#include "game/Utility/DTO/ObjectDTO.h"

class BackpackDTO : public ObjectDTO {
 public:
  WeaponComponent* weaponComponent;
  ArmorComponent* armorComponent;
  InventoryComponent* inventoryComponent;
  SpecialComponent* specialComponent;

  BackpackDTO(WeaponComponent* weaponComponent, ArmorComponent* armorComponent, InventoryComponent* inventoryComponent,
              SpecialComponent* specialComponent)
      : weaponComponent(weaponComponent),
        armorComponent(armorComponent),
        inventoryComponent(inventoryComponent),
        specialComponent(specialComponent) {}
};

#endif  // INCLUDE_GAME_UTILITY_DTO_BACKPACKDTO_H_
