//
// Created by AsTeFu on 24.07.2019.
//

#include "game/RoomManager/Builders/RoomBuilder.h"
#include <game/Components/AIController.h>
#include <game/Components/AttackComponent.h>
#include <game/Components/BaseComponent/CameraComponent.h>
#include <game/Components/BaseComponent/Collider.h>
#include <game/Components/BaseComponent/Graphic.h>
#include <game/Components/BaseComponent/Lighting.h>
#include <game/Components/BaseComponent/Movement.h>
#include <game/Components/BaseComponent/Transform.h>
#include <game/Components/BaseComponent/Trigger.h>
#include <game/Components/BaseComponent/VisibleComponent.h>
#include <game/Components/EnvironmentComponents/ChestComponent.h>
#include <game/Components/EnvironmentComponents/ExitComponent.h>
#include <game/Components/EnvironmentComponents/PointComponent.h>
#include <game/Components/EnvironmentComponents/ShopComponent.h>
#include <game/Components/EnvironmentComponents/WallComponent.h>
#include <game/Components/ItemComponents/ArmorComponent.h>
#include <game/Components/ItemComponents/CoinItemComponent.h>
#include <game/Components/ItemComponents/FoodItemComponent.h>
#include <game/Components/ItemComponents/HealthComponent.h>
#include <game/Components/ItemComponents/HealthItemComponent.h>
#include <game/Components/ItemComponents/InventoryComponent.h>
#include <game/Components/ItemComponents/SpecialComponent.h>
#include <game/Components/ItemComponents/WeaponComponent.h>
#include <game/Components/PlayerComponents/AbilitiesComponent.h>
#include <game/Components/PlayerComponents/InputKeyboard.h>
#include <game/Components/PlayerComponents/LevelComponent.h>
#include <game/Components/PlayerComponents/NameComponent.h>
#include <game/Components/PlayerComponents/PlayerComponent.h>
#include <game/Components/PlayerComponents/StarvationComponent.h>
#include <game/Components/PlayerComponents/StepsComponent.h>
#include <game/Components/PlayerComponents/WalletComponent.h>
#include <game/Components/PositionsComponent.h>
#include <game/Components/RenderType.h>
#include <game/Items/FoodItem.h>
#include <game/Items/MedkitItem.h>
#include <game/Utility/Config.h>
#include <game/Utility/DTO/NameDTO.h>
#include <utilities/Random.h>
#include <algorithm>
#include <vector>
#include "game/RoomManager/Room.h"
#include "game/RoomManager/RoomManager.h"

Room* RoomBuilder::build(StructureComponent* const structure, SceneManager* sceneManager, RoomManager* roomManager) {
  Room* room = new Room(structure->size.getX(), structure->size.getX(), sceneManager, roomManager);

  auto player = room->getEngine().getEntityManager()->createEntity("player");

  if (Room::countRoom == 1) startPlayer(player, sceneManager);

  auto camera = room->getEngine().getEntityManager()->createEntity("camera");
  camera->addComponent<CameraComponent>();

  auto wallPos = room->getEngine().getEntityManager()->createEntity("walls");
  wallPos->addComponent<PositionsComponent>(structure->size.getX());

  auto renderType = room->getEngine().getEntityManager()->createEntity("renderType");
  renderType->addComponent<RenderType>();

  for (int i = 0; i < structure->size.getX(); ++i) {
    for (int j = 0; j < structure->size.getY(); ++j) {
      if (structure->objects[i][j].graphic != '#')
        _builds['.'](i, j, Tile('.', Config::getInstance().disableColor), &room->getEngine());
      _builds[structure->objects[i][j].graphic](i, j, structure->objects[i][j], &room->getEngine());
    }
  }

  room->activateSystem();
  return room;
}
void RoomBuilder::startPlayer(Entity* player, SceneManager* sceneManager) {
  player->addComponent<NameComponent>(sceneManager->getContext()->getObject<NameDTO>()->name);
  player->addComponent<SpecialComponent>(sceneManager->getContext()->getObject<SpecialDTO>()->special);
  auto special = player->getComponent<SpecialComponent>()->special;

  int luck = special.getValue(LUCK);

  player->addComponent<WalletComponent>(100 * ((100.0 + 10.0 * special.getValue(CHARISMA)) / 100.0) +
                                        Random::random(luck * 5));
  player->addComponent<HealthComponent>(100 * ((100.0 + 10.0 * special.getValue(ENDURANCE)) / 100.0) +
                                        Random::random(luck * 2));
  player->addComponent<StarvationComponent>(100 * ((100.0 + 10.0 * special.getValue(ENDURANCE)) / 100.0) +
                                            Random::random(luck * 2));
  player->addComponent<StepsComponent>();
  player->addComponent<LevelComponent>(100);
  player->addComponent<AbilitiesComponent>();

  player->addComponent<WeaponComponent>(_generator.generateWeapon(Rare));
  player->addComponent<ArmorComponent>(_generator.generateEquipmnets(Usual, Rare));

  Special* specialPlayer = &player->getComponent<SpecialComponent>()->addictiveSpecial;
  for (const auto& armor : player->getComponent<ArmorComponent>()->equipments)
    for (const auto& effect : armor.second->effects) specialPlayer->addPoints(effect.first, effect.second);

  player->addComponent<InventoryComponent>(special.getValue(STRENGTH) / 2 + 2);
}

RoomBuilder::RoomBuilder() {
  _builds.insert(make_pair('$', bind(&RoomBuilder::addCoin, this, _1, _2, _3, _4)));
  _builds.insert(make_pair('*', bind(&RoomBuilder::addFood, this, _1, _2, _3, _4)));
  _builds.insert(make_pair('+', bind(&RoomBuilder::addHealth, this, _1, _2, _3, _4)));
  _builds.insert(make_pair('.', bind(&RoomBuilder::addPoint, this, _1, _2, _3, _4)));
  _builds.insert(make_pair('#', bind(&RoomBuilder::addWall, this, _1, _2, _3, _4)));
  _builds.insert(make_pair('X', bind(&RoomBuilder::addChest, this, _1, _2, _3, _4)));
  _builds.insert(make_pair('M', bind(&RoomBuilder::addShop, this, _1, _2, _3, _4)));
  _builds.insert(make_pair('@', bind(&RoomBuilder::addPlayer, this, _1, _2, _3, _4)));
  _builds.insert(make_pair('>', bind(&RoomBuilder::addNextRoomExit, this, _1, _2, _3, _4)));
  _builds.insert(make_pair('<', bind(&RoomBuilder::addPreviousRoomExit, this, _1, _2, _3, _4)));
  _builds.insert(make_pair('E', bind(&RoomBuilder::addEnemy, this, _1, _2, _3, _4)));
}
void RoomBuilder::addCoin(int x, int y, Tile tile, Engine* engine) {
  auto coin = engine->getEntityManager()->createEntity();
  coin->addComponent<Transform>(x, y);
  coin->addComponent<Graphic>(tile.graphic, tile.color, 3);
  coin->addComponent<Lighting>(x, y);
  coin->addComponent<Trigger>();
  coin->addComponent<CoinItemComponent>(_generator.generateCoin());
}
void RoomBuilder::addFood(int x, int y, Tile tile, Engine* engine) {
  auto food = engine->getEntityManager()->createEntity();
  food->addComponent<Transform>(x, y);
  food->addComponent<Graphic>(tile.graphic, tile.color, 3);
  food->addComponent<Trigger>();
  food->addComponent<Lighting>(x, y);
  food->addComponent<FoodItemComponent>(_generator.generateFood());
}
void RoomBuilder::addHealth(int x, int y, Tile tile, Engine* engine) {
  auto health = engine->getEntityManager()->createEntity();
  health->addComponent<Transform>(x, y);
  health->addComponent<Graphic>(tile.graphic, tile.color, 3);
  health->addComponent<Trigger>();
  health->addComponent<Lighting>(x, y);
  health->addComponent<HealthItemComponent>(_generator.generateMedkit());
}
void RoomBuilder::addWall(int x, int y, Tile tile, Engine* engine) {
  auto wall = engine->getEntityManager()->createEntity();
  wall->addComponent<Transform>(x, y);
  wall->addComponent<Graphic>(tile.graphic, tile.color, 0);
  wall->addComponent<Collider>();
  wall->addComponent<Lighting>(x, y);
  wall->addComponent<WallComponent>();

  engine->getEntityManager()->getByTag("walls")[0]->getComponent<PositionsComponent>()->addWall(x, y);
}
void RoomBuilder::addNextRoomExit(int x, int y, Tile tile, Engine* engine) {
  auto exit = engine->getEntityManager()->createEntity(">");
  exit->addComponent<Transform>(x, y);
  exit->addComponent<Graphic>(tile.graphic, tile.color, 4);
  exit->addComponent<Trigger>();
  exit->addComponent<Lighting>(x, y);
  exit->addComponent<ExitComponent>(true);
}
void RoomBuilder::addPreviousRoomExit(int x, int y, Tile tile, Engine* engine) {
  auto exit = engine->getEntityManager()->createEntity("<");
  exit->addComponent<Transform>(x, y);
  exit->addComponent<Graphic>(tile.graphic, tile.color, 4);
  exit->addComponent<Trigger>();
  exit->addComponent<Lighting>(x, y);
  exit->addComponent<ExitComponent>(false);
}
void RoomBuilder::addEnemy(int x, int y, Tile tile, Engine* engine) {
  auto enemy = engine->getEntityManager()->createEntity();
  enemy->addComponent<Transform>(x, y);
  enemy->addComponent<Graphic>(tile.graphic, tile.color, 4);
  enemy->addComponent<Movement>();
  enemy->addComponent<AIController>();
  enemy->addComponent<VisibleComponent>();
  enemy->addComponent<Collider>();
  enemy->addComponent<Lighting>(x, y);
  enemy->addComponent<AttackComponent>();

  auto minRarity = static_cast<Rarity>(Usual + Room::countRoom / 3);
  auto maxRarity = static_cast<Rarity>(Rare + Room::countRoom / 2);

  enemy->addComponent<WeaponComponent>(_generator.generateWeapon(minRarity, maxRarity));
  enemy->addComponent<ArmorComponent>(_generator.generateEquipmnets(minRarity, maxRarity));

  enemy->addComponent<SpecialComponent>(generateSpecialEnemy());
  auto special = enemy->getComponent<SpecialComponent>();

  double startHealth = 100 * (100.0 + 10.0 * special->getValue(ENDURANCE)) / 100.0;
  enemy->addComponent<HealthComponent>(static_cast<int>(startHealth));

  // special->addictiveSpecial.clear();
  for (const auto& armor : enemy->getComponent<ArmorComponent>()->equipments) {
    for (const auto& effect : armor.second->effects) {
      special->addictiveSpecial.addPoints(effect.first, effect.second);
    }
  }
}
Special RoomBuilder::generateSpecialEnemy() const {
  Special special(Config::getInstance().pointSpecialRange, Config::getInstance().maxPointsSpecial);
  special.addPoints(STRENGTH, Random::random(3, 7));
  special.addPoints(ENDURANCE, Random::random(3, 7));
  special.addPoints(PERCEPTION, Random::random(3, 7));

  int rnd = Random::random(std::max(5 + Room::countRoom * 2, Config::getInstance().maxPointsSpecial - 1),
                           std::max(15 + Room::countRoom * 2, Config::getInstance().maxPointsSpecial));

  for (int i = 0; i < rnd; i++) special.addPoint(Config::getInstance().statsSpecial[Random::random(7)]);
  return special;
}
void RoomBuilder::addChest(int x, int y, Tile tile, Engine* engine) {
  auto chest = engine->getEntityManager()->createEntity("chest");
  chest->addComponent<Transform>(x, y);
  chest->addComponent<Graphic>(tile.graphic, tile.color, 1);
  chest->addComponent<ChestComponent>();
  chest->addComponent<Lighting>(x, y);
  chest->addComponent<VisibleComponent>();
}
void RoomBuilder::addShop(int x, int y, Tile tile, Engine* engine) {
  auto shop = engine->getEntityManager()->createEntity("shop");
  shop->addComponent<Transform>(x, y);
  shop->addComponent<Graphic>(tile.graphic, tile.color, 1);
  shop->addComponent<ShopComponent>();
  shop->addComponent<Lighting>(x, y);
  shop->addComponent<VisibleComponent>();

  auto shopComp = shop->getComponent<ShopComponent>();

  auto minRarity = static_cast<Rarity>(Rare + Room::countRoom / 3);
  auto maxRarity = static_cast<Rarity>(Epic + Room::countRoom / 2);

  int maxGoods = Random::random(3, 5);
  for (int i = 0; i < maxGoods; i++) {
    int rnd = Random::random(100);
    if (rnd < 50)
      shopComp->addItem<Armor>(_generator.generateArmor(minRarity, maxRarity));
    else if (rnd < 80)
      shopComp->addItem<Weapon>(_generator.generateWeapon(minRarity, maxRarity));
    else if (rnd < 90)
      shopComp->addItem<FoodItem>(new FoodItem(_generator.generateFood() + Room::countRoom, Random::random(70, 120)));
    else if (rnd < 100)
      shopComp->addItem<MedkitItem>(
          new MedkitItem(_generator.generateMedkit() + Room::countRoom, Random::random(50, 90)));
  }
}
void RoomBuilder::addPoint(int x, int y, Tile tile, Engine* engine) {
  auto point = engine->getEntityManager()->createEntity();
  point->addComponent<Transform>(x, y);
  point->addComponent<Lighting>(x, y);
  point->addComponent<Graphic>(tile.graphic, Color::Gray, 0);
  point->addComponent<PointComponent>();
}
void RoomBuilder::addPlayer(int x, int y, Tile tile, Engine* engine) {
  auto player = engine->getEntityManager()->getByTag("player")[0];
  player->addComponent<Graphic>(tile.graphic, tile.color, 5);
  player->addComponent<Transform>(x, y);
  player->addComponent<Movement>();
  player->addComponent<InputKeyboard>();
  player->addComponent<Collider>();
  player->addComponent<Lighting>(x, y);
  player->addComponent<PlayerComponent>();
  player->addComponent<AttackComponent>();

  engine->getEntityManager()->getByTag("camera")[0]->addComponent<Transform>(x, y);
}
