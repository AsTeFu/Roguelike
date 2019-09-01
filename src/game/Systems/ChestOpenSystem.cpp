//
// Created by AsTeFu on 10.08.2019.
//

#include "game/Systems/ChestOpenSystem.h"
#include <game/Components/BaseComponent/Collider.h>
#include <game/Components/BaseComponent/Graphic.h>
#include <game/Components/BaseComponent/Transform.h>
#include <game/Components/BaseComponent/Trigger.h>
#include <game/Components/EnvironmentComponents/ChestComponent.h>
#include <game/Components/ItemComponents/InventoryComponent.h>
#include <game/Items/CoinItem.h>
#include <game/Items/FoodItem.h>
#include <game/Items/GeneratorInventoryItem.h>
#include <game/Items/MedkitItem.h>
#include <game/RoomManager/Room.h>
#include <game/Utility/DTO/ChestDTO.h>
#include <game/Utility/Input.h>
#include <utilities/Random.h>
#include <algorithm>
#include "ecs/EntityManager.h"
#include "ecs/SystemManager.h"

bool ChestOpenSystem::filter(Entity* entity) const {
  return entity->hasComponent<ChestComponent>() && entity->hasComponent<Transform>();
}
void ChestOpenSystem::update(Entity* entity) {
  auto player = getEntityManager()->getByTag("player")[0];
  auto chest = entity->getComponent<ChestComponent>();

  if (!chest->isOpen) {
    chest->isOpen = true;

    auto special = player->getComponent<SpecialComponent>();
    GeneratorInventoryItem generator;

    int amount = Random::random(1, std::min(special->getValue(LUCK) / 2 + 1, 5));
    for (int i = 0; i < amount; ++i) {
      int rnd = Random::random(100);
      if (rnd < 50)
        chest->addItem<Armor>(
            generator.generateArmor(static_cast<Rarity>(Rare + Room::countRoom / 2 + special->getValue(LUCK) / 8)));
      else if (rnd < 80)
        chest->addItem<Weapon>(
            generator.generateWeapon(static_cast<Rarity>(Rare + Room::countRoom / 2 + special->getValue(LUCK) / 8)));
      else if (rnd < 87)
        chest->addItem<CoinItem>(
            new CoinItem(generator.generateCoin() + Room::countRoom * (special->getValue(LUCK) / 2 + 1)));
      else if (rnd < 94)
        chest->addItem<FoodItem>(
            new FoodItem(generator.generateFood() + Room::countRoom * (special->getValue(LUCK) / 2 + 1), 100));
      else if (rnd < 100)
        chest->addItem<MedkitItem>(
            new MedkitItem(generator.generateMedkit() + Room::countRoom * (special->getValue(LUCK) / 2 + 1), 100));
    }
  }

  if (chest->items.empty()) {
    std::cout << "Delete chest" << std::endl;
    auto emptyChest = getEntityManager()->createEntity();
    emptyChest->addComponent<Transform>(entity->getComponent<Transform>()->position);
    emptyChest->addComponent<Graphic>(
        Display(entity->getComponent<Graphic>()->display.graphic, Config::getInstance().disableColor));
    getSystemManager()->addEntity(emptyChest);

    getSystemManager()->deleteEntity(entity->getID());
    getEntityManager()->deleteEntity(entity->getID());
  }

  if (Input::getKey(KeyCode::Enter) &&
      player->getComponent<Transform>()->position == entity->getComponent<Transform>()->position) {
    getSceneManager()->getContext()->addObject<ChestDTO>(player, chest);

    getSceneManager()->switchScene("Chest");
  }
}
