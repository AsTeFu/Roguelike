//
// Created by AsTeFu on 08.08.2019.
//

#include "game/Systems/DeadSystem.h"
#include <utilities/Random.h>
#include <game/Components/BaseComponent/CameraComponent.h>
#include <game/Components/BaseComponent/Graphic.h>
#include <game/Components/BaseComponent/Transform.h>
#include <game/Components/EnvironmentComponents/ChestComponent.h>
#include <game/Components/ItemComponents/HealthComponent.h>
#include <game/Components/ItemComponents/SpecialComponent.h>
#include <game/Components/ItemComponents/WeaponComponent.h>
#include <game/Components/PlayerComponents/AbilitiesComponent.h>
#include <game/Components/PlayerComponents/LevelComponent.h>
#include <game/Components/PlayerComponents/PlayerComponent.h>
#include <game/Items/CoinItem.h>
#include <game/Logs/GameLogger.h>
#include <game/Utility/Config.h>
#include <game/Utility/LevelUtility.h>
#include "ecs/SystemManager.h"

bool DeadSystem::filter(Entity* entity) const {
  return entity->hasComponent<HealthComponent>() && !entity->hasComponent<PlayerComponent>();
}
void DeadSystem::update(Entity* entity) {
  auto healthComponent = entity->getComponent<HealthComponent>();

  if (healthComponent->health <= 0) {
    std::cout << "Enemy is dead" << std::endl;

    auto player = getEntityManager()->getByTag("player")[0];
    int playerLuck = player->getComponent<SpecialComponent>()->getValue(LUCK);

    LevelUtility::addExperience(player);

    auto deadEntity = findDeadEnemy(entity->getComponent<Transform>());
    if (deadEntity == nullptr) deadEntity = createChest(entity);
    fillChest(deadEntity->getComponent<ChestComponent>(), entity, playerLuck);

    getSystemManager()->addEntity(deadEntity);
  }
}
Entity* DeadSystem::createChest(const Entity* entity) const {
  auto deadEntity = getEntityManager()->createEntity();
  deadEntity->addComponent<Transform>(entity->getComponent<Transform>()->position);
  deadEntity->addComponent<Graphic>(Display('&', entity->getComponent<Graphic>()->display.color));
  deadEntity->addComponent<ChestComponent>();
  deadEntity->getComponent<ChestComponent>()->isOpen = true;
  return deadEntity;
}
void DeadSystem::fillChest(ChestComponent* chest, Entity* enemy, int playerLuck) {
  chest->addItem<Weapon>(new Weapon(*dynamic_cast<Weapon*>(enemy->getComponent<WeaponComponent>()->weapon.get())));
  for (const auto& armor : enemy->getComponent<ArmorComponent>()->equipments) {
    chest->addItem<Armor>(new Armor(*dynamic_cast<Armor*>(armor.second.get())));
  }
  chest->addItem<CoinItem>(new CoinItem(Random::random(20 + playerLuck * 5, 90 + playerLuck * 5)));

  getSystemManager()->deleteEntity(enemy->getID());
  getEntityManager()->deleteEntity(enemy->getID());
}
Entity* DeadSystem::findDeadEnemy(Transform* const transform) {
  for (auto& deadEnemy : *getEntityManager()) {
    if (deadEnemy.hasComponent<ChestComponent>() &&
        deadEnemy.getComponent<Transform>()->position == transform->position) {
      return &deadEnemy;
    }
  }
  return nullptr;
}
