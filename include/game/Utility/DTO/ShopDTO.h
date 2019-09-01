//
// Created by AsTeFu on 19.08.2019.
//

#ifndef INCLUDE_GAME_UTILITY_DTO_SHOPDTO_H_
#define INCLUDE_GAME_UTILITY_DTO_SHOPDTO_H_

#include <game/Components/EnvironmentComponents/ShopComponent.h>
#include <game/Components/ItemComponents/HealthComponent.h>
#include <game/Components/ItemComponents/InventoryComponent.h>
#include <game/Components/ItemComponents/SpecialComponent.h>
#include <game/Components/ItemComponents/WeaponComponent.h>
#include <game/Components/PlayerComponents/StarvationComponent.h>
#include <game/Components/PlayerComponents/WalletComponent.h>
#include "game/Utility/DTO/ObjectDTO.h"

class ShopDTO : public ObjectDTO {
 public:
  ShopComponent* shopComponent;
  WeaponComponent* weaponComponent;
  ArmorComponent* armorComponent;
  WalletComponent* walletComponent;
  StarvationComponent* starvationComponent;
  HealthComponent* healthComponent;
  InventoryComponent* inventoryComponent;
  SpecialComponent* specialComponent;

  ShopDTO(ShopComponent* shopComponent, WeaponComponent* weaponComponent, ArmorComponent* armorComponent,
          WalletComponent* walletComponent, StarvationComponent* starvationComponent, HealthComponent* healthComponent,
          InventoryComponent* inventoryComponent, SpecialComponent* specialComponent)
      : shopComponent(shopComponent),
        weaponComponent(weaponComponent),
        armorComponent(armorComponent),
        walletComponent(walletComponent),
        starvationComponent(starvationComponent),
        healthComponent(healthComponent),
        inventoryComponent(inventoryComponent),
        specialComponent(specialComponent) {}
};

#endif  // INCLUDE_GAME_UTILITY_DTO_SHOPDTO_H_
