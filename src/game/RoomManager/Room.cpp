//
// Created by AsTeFu on 24.07.2019.
//

#include <game/RoomManager/Builders/RoomBuilder.h>
#include <game/RoomManager/Room.h>
#include <game/Systems/AIMovementSystem.h>
#include <game/Systems/AbilityOpenSystem.h>
#include <game/Systems/AttackSystem.h>
#include <game/Systems/BackpackOpenSystem.h>
#include <game/Systems/CameraSystem.h>
#include <game/Systems/CashTriggerSystem.h>
#include <game/Systems/CheatPlayerSystem.h>
#include <game/Systems/ChestOpenSystem.h>
#include <game/Systems/CollisionSystem.h>
#include <game/Systems/DeadSystem.h>
#include <game/Systems/ExitSystem.h>
#include <game/Systems/FindEventSystem.h>
#include <game/Systems/FoodTriggerSystem.h>
#include <game/Systems/GameOverSystem.h>
#include <game/Systems/InputSystem.h>
#include <game/Systems/MedkitTriggerSystem.h>
#include <game/Systems/MovementSystem.h>
#include <game/Systems/PointRenderSystem.h>
#include <game/Systems/RenderMoveableSystem.h>
#include <game/Systems/RenderPlayerSystem.h>
#include <game/Systems/RenderSystem.h>
#include <game/Systems/ShopOpenSystem.h>
#include <game/Systems/StarvationSystem.h>
#include <game/Systems/StepsSystem.h>
#include <game/Systems/WallRenderSystem.h>
#include "game/RoomManager/RoomManager.h"

int Room::countRoom = 0;

Room::Room(int width, int height, SceneManager* sceneManager, RoomManager* roomManager)
    : id(++countRoom), _width(width), _height(height), _engine(sceneManager), _roomManager(roomManager) {}

void Room::start() {
  _engine.update();
}
void Room::update() {
  _engine.update();
}

void Room::activateSystem() {
  _engine.getSystemManager()->addSystem<InputSystem>();
  _engine.getSystemManager()->addSystem<CheatPlayerSystem>();
  _engine.getSystemManager()->addSystem<BackpackOpenSystem>();
  _engine.getSystemManager()->addSystem<AbilityOpenSystem>();
  _engine.getSystemManager()->addSystem<AIMovementSystem>();

  _engine.getSystemManager()->addSystem<CollisionSystem>();
  _engine.getSystemManager()->addSystem<MovementSystem>();
  _engine.getSystemManager()->addSystem<StepsSystem>();
  _engine.getSystemManager()->addSystem<StarvationSystem>();
  _engine.getSystemManager()->addSystem<GameOverSystem>(_roomManager);

  _engine.getSystemManager()->addSystem<ChestOpenSystem>();
  _engine.getSystemManager()->addSystem<ShopOpenSystem>();

  _engine.getSystemManager()->addSystem<AttackSystem>();
  _engine.getSystemManager()->addSystem<DeadSystem>();

  _engine.getSystemManager()->addSystem<CashTriggerSystem>();
  _engine.getSystemManager()->addSystem<MedkitTriggerSystem>();
  _engine.getSystemManager()->addSystem<FoodTriggerSystem>();

  _engine.getSystemManager()->addSystem<CameraSystem>();
  _engine.getSystemManager()->addSystem<PointRenderSystem>();
  _engine.getSystemManager()->addSystem<WallRenderSystem>();
  _engine.getSystemManager()->addSystem<RenderSystem>();
  _engine.getSystemManager()->addSystem<RenderMoveableSystem>();
  _engine.getSystemManager()->addSystem<RenderPlayerSystem>();
  _engine.getSystemManager()->addSystem<FindEventSystem>();
  _engine.getSystemManager()->addSystem<ExitSystem>(_roomManager);
}
/*
PlayerDTO Room::getPlayerDTO() {
  auto player = _engine.getEntityManager()->getByTag("player")[0];
  return {player->getComponent<NameComponent>()->name,
          player->getComponent<WalletComponent>()->cash,
          player->getComponent<StarvationComponent>()->currentFood,
          player->getComponent<HealthComponent>()->health,
          player->getComponent<StepsComponent>()->currentSteps,
          player->getComponent<WeaponComponent>(),
          player->getComponent<ArmorComponent>(),
          player->getComponent<InventoryComponent>(),
          player->getComponent<SpecialComponent>(),
          player->getComponent<LevelComponent>(),
          player->getComponent<AbilitiesComponent>()};
}

void Room::addSpecial(const SpecialDTO& specialDto) {
  auto player = _engine.getEntityManager()->getByTag("player")[0];
  player->addComponent<SpecialComponent>(specialDto.special);
  // if (!player->hasComponent<SpecialComponent>()) {
  // player->addComponent<SpecialComponent>(specialDto.special);
  // auto special = player->getComponent<SpecialComponent>();
  // for (const auto& armor : player->getComponent<ArmorComponent>()->equipments) {
  //  for (const auto& effect : armor.second->effects) {
  //    special->addictiveSpecial.addPoints(effect.first, effect.second);
  //  }
  // }
  // Start health
  // player->getComponent<HealthComponent>()->health +=
  //    special->getValue(ENDURANCE) * 10 + 2 * Random::random(special->getValue(LUCK));
  // Грузоподъемность
  // player->getComponent<InventoryComponent>()->maxItems = special->getValue(STRENGTH) / 2;
  // }
}
 */
/*
void Room::addName(const string& name) {
  _engine.getEntityManager()->getByTag("player")[0]->addComponent<NameComponent>(name);
} */
Engine& Room::getEngine() {
  return _engine;
}
/*
void Room::setPlayerDTO(const PlayerDTO& dto) {

auto player = _engine.getEntityManager()->getByTag("player")[0];
player->addComponent<NameComponent>(dto.name);
player->getComponent<WalletComponent>()->cash = dto.cash;
player->getComponent<StarvationComponent>()->currentFood = dto.food;
player->getComponent<HealthComponent>()->health = dto.health;
player->getComponent<StepsComponent>()->currentSteps = dto.steps;
player->getComponent<WeaponComponent>()->weapon = std::make_unique<Weapon>(*dto.weapon->weapon);
for (auto& equipment : player->getComponent<ArmorComponent>()->equipments) {
  equipment.second = std::make_unique<Armor>(*dto.armor->equipments.at(equipment.first));
}
for (auto& item : dto.inventory->items) {
  if (item->itemType == WeaponType)
    player->getComponent<InventoryComponent>()->addItem<Weapon>(dynamic_cast<Weapon*>(item.get()));
  if (item->itemType == ArmorType)
    player->getComponent<InventoryComponent>()->addItem<Armor>(dynamic_cast<Armor*>(item.get()));
}
player->addComponent<SpecialComponent>(dto.special->special);

player->getComponent<SpecialComponent>()->addictiveSpecial.clear();
for (const auto& armor : player->getComponent<ArmorComponent>()->equipments) {
  for (const auto& effect : armor.second->effects) {
    for (int i = 0; i < effect.second; ++i) {
      player->getComponent<SpecialComponent>()->addictiveSpecial.addPoint(effect.first);
    }
  }
}

auto abilities = player->getComponent<AbilitiesComponent>();
for (const auto& ability : dto.abilities->abilities) {
  abilities->abilities.push_back(ability);
}
abilities->available = dto.abilities->available;

player->getComponent<LevelComponent>()->currentLevel = dto.level->currentLevel;
player->getComponent<LevelComponent>()->maxExperience = dto.level->maxExperience;
player->getComponent<LevelComponent>()->currentExperience = dto.level->currentExperience;
player->getComponent<LevelComponent>()->upgrade = dto.level->upgrade;
player->getComponent<LevelComponent>()->bonus = dto.level->bonus;

} */
int Room::getID() {
  return id;
}
