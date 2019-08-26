//
// Created by AsTeFu on 19.08.2019.
//

#ifndef INCLUDE_GAME_UTILITY_DTO_SHOPDTO_H_
#define INCLUDE_GAME_UTILITY_DTO_SHOPDTO_H_

#include <game/Components/HealthComponent.h>
#include <game/Components/InventoryComponent.h>
#include <game/Components/ShopComponent.h>
#include <game/Components/SpecialComponent.h>
#include <game/Components/StarvationComponent.h>
#include <game/Components/WalletComponent.h>
#include <game/Components/WeaponComponent.h>
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
