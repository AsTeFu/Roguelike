//
// Created by AsTeFu on 08.08.2019.
//

#include "game/Systems/DeadSystem.h"
#include <game/Components/AbilitiesComponent.h>
#include <game/Components/CameraComponent.h>
#include <game/Components/ChestComponent.h>
#include <game/Components/Graphic.h>
#include <game/Components/HealthComponent.h>
#include <game/Components/LevelComponent.h>
#include <game/Components/PlayerComponent.h>
#include <game/Components/SpecialComponent.h>
#include <game/Components/Transform.h>
#include <game/Components/WeaponComponent.h>
#include <game/Logs/GameLogger.h>
#include <game/Utility/ConfigTerminal.h>
#include <game/Utility/Random.h>
#include "ecs/SystemManager.h"

bool DeadSystem::filter(Entity* entity) const {
  return entity->hasComponent<HealthComponent>() && !entity->hasComponent<PlayerComponent>();
}
void DeadSystem::update(Entity* entity) {
  auto healthComponent = entity->getComponent<HealthComponent>();

  if (healthComponent->health <= 0) {
    std::cout << "Entity is dead" << std::endl;

    auto player = getEntityManager()->getByTag("player")[0];
    int playerLuck = player->getComponent<SpecialComponent>()->getValue(LUCK);

    // Player experience
    int experience = 30 + Random::random(15);

    if (player->getComponent<LevelComponent>()->addExperience(experience)) {
      player->getComponent<SpecialComponent>()->special.addAvailablePoint();
      player->getComponent<AbilitiesComponent>()->available++;
      GameLogger::getInstance().add("[color=Sublime]Level UP!");
    }

    for (const auto& item : *getEntityManager()) {
      if (item.hasComponent<ChestComponent>() &&
          item.getComponent<Transform>()->position == entity->getComponent<Transform>()->position) {
        auto chest = item.getComponent<ChestComponent>();
        addItems(chest, entity, playerLuck);
        return;
      }
    }

    auto deadEntity = getEntityManager()->createEntity();
    deadEntity->addComponent<Transform>(entity->getComponent<Transform>()->position);
    deadEntity->addComponent<Graphic>(Display('&', color_from_name("red")));
    deadEntity->addComponent<ChestComponent>();
    deadEntity->getComponent<ChestComponent>()->isOpen = true;
    // deadEntity->getComponent<Graphic>()->offset =
    // getEntityManager()->getByTag("camera")[0]->getComponent<CameraComponent>()->offset;

    addItems(deadEntity->getComponent<ChestComponent>(), entity, playerLuck);

    getSystemManager()->addEntity(deadEntity);
  }
}
void DeadSystem::addItems(ChestComponent* chest, Entity* enemy, int playerLuck) {
  chest->addItem<Weapon>(new Weapon(*dynamic_cast<Weapon*>(enemy->getComponent<WeaponComponent>()->weapon.get())));
  for (const auto& armor : enemy->getComponent<ArmorComponent>()->equipments) {
    chest->addItem<Armor>(new Armor(*dynamic_cast<Armor*>(armor.second.get())));
  }
  chest->addItem<CoinItem>(new CoinItem(Random::random(20 + playerLuck * 5, 90 + playerLuck * 5)));

  getSystemManager()->deleteEntity(enemy->getID());
  getEntityManager()->deleteEntity(enemy->getID());
}
