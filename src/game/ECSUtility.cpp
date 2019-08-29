//
// Created by AsTeFu on 27.08.2019.
//
#include <game/Components/AbilitiesComponent.h>
#include <game/Components/HealthComponent.h>
#include <game/Components/InventoryComponent.h>
#include <game/Components/LevelComponent.h>
#include <game/Components/NameComponent.h>
#include <game/Components/SpecialComponent.h>
#include <game/Components/StarvationComponent.h>
#include <game/Components/StepsComponent.h>
#include <game/Components/WalletComponent.h>
#include <game/Components/WeaponComponent.h>
#include <game/ECSUtility.h>

Entity* ECSUtility::copyPlayer(Entity* const fromPlayer, Entity* toPlayer) {
  toPlayer->addComponent<NameComponent>(fromPlayer->getComponent<NameComponent>()->name);

  toPlayer->addComponent<SpecialComponent>(fromPlayer->getComponent<SpecialComponent>()->special);
  toPlayer->addComponent<WalletComponent>(fromPlayer->getComponent<WalletComponent>()->cash);
  toPlayer->addComponent<HealthComponent>(fromPlayer->getComponent<HealthComponent>()->health);
  toPlayer->addComponent<StarvationComponent>(fromPlayer->getComponent<StarvationComponent>()->currentFood);
  toPlayer->addComponent<StepsComponent>(fromPlayer->getComponent<StepsComponent>()->currentSteps);
  toPlayer->addComponent<LevelComponent>(*fromPlayer->getComponent<LevelComponent>());

  // TODO(AsTeFu): abilities
  toPlayer->addComponent<AbilitiesComponent>();
  *toPlayer->getComponent<AbilitiesComponent>() = *fromPlayer->getComponent<AbilitiesComponent>();

  toPlayer->addComponent<WeaponComponent>(fromPlayer->getComponent<WeaponComponent>()->weapon.get());
  toPlayer->addComponent<ArmorComponent>(*fromPlayer->getComponent<ArmorComponent>());
  toPlayer->addComponent<InventoryComponent>(*fromPlayer->getComponent<InventoryComponent>());

  return toPlayer;
}
Entity* ECSUtility::transferPlayer(Entity* const fromPlayer, Entity* toPlayer) {
  toPlayer->getComponent<NameComponent>()->name = fromPlayer->getComponent<NameComponent>()->name;
  toPlayer->getComponent<SpecialComponent>()->setSpecials(fromPlayer->getComponent<SpecialComponent>());
  toPlayer->getComponent<WalletComponent>()->cash = fromPlayer->getComponent<WalletComponent>()->cash;
  toPlayer->getComponent<HealthComponent>()->health = fromPlayer->getComponent<HealthComponent>()->health;
  toPlayer->getComponent<StarvationComponent>()->currentFood =
      fromPlayer->getComponent<StarvationComponent>()->currentFood;
  toPlayer->getComponent<StepsComponent>()->currentSteps = fromPlayer->getComponent<StepsComponent>()->currentSteps;
  toPlayer->getComponent<LevelComponent>()->setExperience(fromPlayer->getComponent<LevelComponent>());

  // TODO(AsTeFu): abilities
  *toPlayer->getComponent<AbilitiesComponent>() = *fromPlayer->getComponent<AbilitiesComponent>();

  *toPlayer->getComponent<WeaponComponent>()->weapon = *fromPlayer->getComponent<WeaponComponent>()->weapon;
  toPlayer->getComponent<ArmorComponent>()->setEquipments(fromPlayer->getComponent<ArmorComponent>());
  toPlayer->getComponent<InventoryComponent>()->setInventory(fromPlayer->getComponent<InventoryComponent>());

  return toPlayer;
}
