//
// Created by AsTeFu on 20.08.2019.
//

#include "game/Systems/FindEventSystem.h"
#include <game/Components/AIController.h>
#include <game/Components/BaseComponent/Graphic.h>
#include <game/Components/BaseComponent/VisibleComponent.h>
#include <game/Components/EnvironmentComponents/ChestComponent.h>
#include <game/Components/EnvironmentComponents/ShopComponent.h>
#include <game/Components/ItemComponents/HealthComponent.h>
#include <game/Components/ItemComponents/SpecialComponent.h>
#include <game/Components/ItemComponents/WeaponComponent.h>
#include <game/Logs/GameLogger.h>

bool FindEventSystem::filter(Entity* entity) const {
  return entity->hasComponent<Graphic>() && entity->hasComponent<VisibleComponent>();
}
void FindEventSystem::postUpdate(Entity* entity) {
  if (!entity->getComponent<VisibleComponent>()->visible && entity->getComponent<Graphic>()->visible) {
    if (entity->hasComponent<AIController>())
      spottedEnemy(entity);
    else if (entity->hasComponent<ChestComponent>())
      spottedChest(entity);
    else if (entity->hasComponent<ShopComponent>())
      spottedShop(entity);
  }
}
void FindEventSystem::spottedEnemy(Entity* enemy) {
  enemy->getComponent<VisibleComponent>()->visible = true;

  auto special = enemy->getComponent<SpecialComponent>();
  int damage = enemy->getComponent<WeaponComponent>()->weapon->damage + special->getValue(STRENGTH) * 2;
  int protect = enemy->getComponent<ArmorComponent>()->getProtect() + special->getValue(ENDURANCE) * 2;
  int health = enemy->getComponent<HealthComponent>()->health;

  GameLogger::getInstance().add("Spotted the [color=red]ENEMY[/color]! Damage: [color=red]" + std::to_string(damage) +
                                "[/color], protect: [color=dark blue]" + std::to_string(protect) +
                                "[/color], health: [color=red]" + std::to_string(health) + "[/color].");
}
void FindEventSystem::spottedChest(Entity* chest) {
  chest->getComponent<VisibleComponent>()->visible = true;

  GameLogger::getInstance().add("Spotted the [color=yellow]CHEST[/color]!");
}
void FindEventSystem::spottedShop(Entity* shop) {
  shop->getComponent<VisibleComponent>()->visible = true;

  GameLogger::getInstance().add("Spotted the [color=dark blue]SHOP[/color]!");
}
