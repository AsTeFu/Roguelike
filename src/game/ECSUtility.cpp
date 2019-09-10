//
// Created by AsTeFu on 27.08.2019.
//
#include <game/Components/ItemComponents/HealthComponent.h>
#include <game/Components/ItemComponents/InventoryComponent.h>
#include <game/Components/ItemComponents/SpecialComponent.h>
#include <game/Components/ItemComponents/WeaponComponent.h>
#include <game/Components/PlayerComponents/AbilitiesComponent.h>
#include <game/Components/PlayerComponents/LevelComponent.h>
#include <game/Components/PlayerComponents/NameComponent.h>
#include <game/Components/PlayerComponents/StarvationComponent.h>
#include <game/Components/PlayerComponents/StepsComponent.h>
#include <game/Components/PlayerComponents/WalletComponent.h>
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

  toPlayer->getComponent<WeaponComponent>()->weapon.swap(fromPlayer->getComponent<WeaponComponent>()->weapon);
  toPlayer->getComponent<ArmorComponent>()->setEquipments(fromPlayer->getComponent<ArmorComponent>());
  toPlayer->removeComponent<InventoryComponent>();
  toPlayer->addComponent<InventoryComponent>(*fromPlayer->getComponent<InventoryComponent>());

  return toPlayer;
}
