//
// Created by AsTeFu on 10.08.2019.
//

#ifndef INCLUDE_GAME_UTILITY_DTO_CHESTDTO_H_
#define INCLUDE_GAME_UTILITY_DTO_CHESTDTO_H_

#include <game/Components/ArmorComponent.h>
#include <game/Components/ChestComponent.h>
#include <game/Components/HealthComponent.h>
#include <game/Components/InventoryComponent.h>
#include <game/Components/SpecialComponent.h>
#include <game/Components/StarvationComponent.h>
#include <game/Components/WalletComponent.h>
#include <game/Components/WeaponComponent.h>
#include "game/Utility/DTO/ObjectDTO.h"

// TODO(AsTeFu): rename
class ChestDTO : public ObjectDTO {
 public:
  ChestComponent* chestComponent;
  WeaponComponent* weaponComponent;
  ArmorComponent* armorComponent;
  WalletComponent* walletComponent;
  StarvationComponent* starvationComponent;
  HealthComponent* healthComponent;
  InventoryComponent* inventoryComponent;
  SpecialComponent* specialComponent;

  ChestDTO(ChestComponent* chestComponent, WeaponComponent* weaponComponent, ArmorComponent* armorComponent,
           WalletComponent* walletComponent, StarvationComponent* starvationComponent, HealthComponent* healthComponent,
           InventoryComponent* inventoryComponent, SpecialComponent* specialComponent)
      : chestComponent(chestComponent),
        weaponComponent(weaponComponent),
        armorComponent(armorComponent),
        walletComponent(walletComponent),
        starvationComponent(starvationComponent),
        healthComponent(healthComponent),
        inventoryComponent(inventoryComponent),
        specialComponent(specialComponent) {}
};

#endif  // INCLUDE_GAME_UTILITY_DTO_CHESTDTO_H_
