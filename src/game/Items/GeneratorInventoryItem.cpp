//
// Created by AsTeFu on 10.08.2019.
//

#include "game/Items/GeneratorInventoryItem.h"
#include <game/Items/Weapon.h>
#include <utilities/Random.h>
#include <map>
#include <string>
#include <vector>

vector<Range> ArmorGenerator::protectRanges = ReaderItems::readProtect();
map<int, vector<string>> ArmorGenerator::names = ReaderItems::readArmor();

vector<Range> WeaponGenerator::damageRanges = ReaderItems::readDamage();
map<int, vector<string>> WeaponGenerator::names = ReaderItems::readWeapon();

Rarity ItemGenerator::getRarity(Rarity maxRarity) {
  int rnd = Random::random(100) + 1;
  int currentChance = 0;
  int rRarity = 1;
  for (const auto& chance : Config::getInstance().rarityChances) {
    currentChance += chance;

    if (rRarity == maxRarity) return static_cast<Rarity>(rRarity);
    if (rnd <= currentChance) return static_cast<Rarity>(rRarity);

    rRarity++;
  }

  return static_cast<Rarity>(rRarity);
}
std::string& WeaponGenerator::getRandomName(int rarity) {
  return names[rarity][Random::random(names[rarity].size())];
}
std::string& ArmorGenerator::getRandomName(int rarity) {
  return names[rarity][Random::random(names[rarity].size())];
}
int ItemGenerator::getCost(Rarity rarity, int mainStat) {
  return Random::random(100 * rarity + mainStat, 100 + 100 * rarity + mainStat);
}

// Weapon
int WeaponGenerator::getDamage(Rarity rarity) {
  return Random::random(damageRanges[rarity - 1].minValue, damageRanges[rarity - 1].maxValue);
}

Weapon* WeaponGenerator::generateWeapon(Rarity maxRarity) {
  return generateWeapon(Usual, maxRarity);
}
Weapon* WeaponGenerator::generateWeapon(Rarity minRarity, Rarity maxRarity) {
  Rarity rarity = getRarity(maxRarity);
  if (rarity < minRarity) rarity = minRarity;
  int damage = getDamage(rarity);
  int critical = 4 + rarity * 5;
  int cost = getCost(rarity, damage);

  return new Weapon(getRandomName(rarity), rarity, cost, damage, critical);
}

// Armor
Slot ArmorGenerator::getSlot() {
  int rnd = Random::random(0, 2);
  return static_cast<Slot>(rnd);
}
map<string, int> ArmorGenerator::setEffects(Rarity rarity) {
  map<string, int> effects;
  int rnd = Random::random(rarity * 6, 100);

  int indexState = 0;
  if (rnd > 75) {
    indexState = Random::random(Config::getInstance().statsSpecial.size());
    effects[Config::getInstance().statsSpecial[indexState]] = Random::random(1 + (rarity / 4), 2 + (rarity / 4));
  }
  if (rnd > 90) {
    int secondIndexState = 0;
    while ((secondIndexState = (Random::random(Config::getInstance().statsSpecial.size()))) == indexState) {
    }
    effects[Config::getInstance().statsSpecial[secondIndexState]] = Random::random(1 + (rarity / 4), 3 + (rarity / 5));
  }

  return effects;
}
int ArmorGenerator::getProtect(int rarity) {
  return Random::random(protectRanges[rarity - 1].minValue, protectRanges[rarity - 1].maxValue);
}
Armor* ArmorGenerator::generateArmor(Slot slot, Rarity maxRarity) {
  return generateArmor(slot, Usual, maxRarity);
}
int ArmorGenerator::getDodge(Rarity rarity) const {
  return Random::random(1 + rarity * 2, 5 + rarity * 2);
}
Armor* ArmorGenerator::generateArmor(Slot slot, Rarity minRarity, Rarity maxRarity) {
  Rarity rarity = getRarity(maxRarity);
  if (rarity < minRarity) rarity = minRarity;

  int protect = getProtect(rarity);
  int dodge = getDodge(rarity);
  map<string, int> effects = setEffects(rarity);
  int cost = getCost(rarity, protect);

  return new Armor(getRandomName(rarity), rarity, cost, slot, protect, dodge, effects);
}

// GeneratorInventoryItem
Armor* GeneratorInventoryItem::generateArmor() {
  return _armorGenerator.generateArmor(_armorGenerator.getSlot(), Sublime);
}
Armor* GeneratorInventoryItem::generateArmor(Slot slot, Rarity maxRarity) {
  return _armorGenerator.generateArmor(slot, maxRarity);
}
Armor* GeneratorInventoryItem::generateArmor(Slot slot, Rarity minRarity, Rarity maxRarity) {
  return _armorGenerator.generateArmor(slot, minRarity, maxRarity);
}
Weapon* GeneratorInventoryItem::generateWeapon() {
  return _weaponGenerator.generateWeapon(Sublime);
}
Weapon* GeneratorInventoryItem::generateWeapon(Rarity maxRarity) {
  return _weaponGenerator.generateWeapon(maxRarity);
}
int GeneratorInventoryItem::generateCoin() {
  return Random::random(20, 50);
}
int GeneratorInventoryItem::generateFood() {
  return Random::random(30, 60);
}
int GeneratorInventoryItem::generateMedkit() {
  return Random::random(30, 50);
}
Armor* GeneratorInventoryItem::generateArmor(Rarity maxRarity) {
  return generateArmor(_armorGenerator.getSlot(), maxRarity);
}
Weapon* GeneratorInventoryItem::generateWeapon(Rarity minRarity, Rarity maxRarity) {
  return _weaponGenerator.generateWeapon(minRarity, maxRarity);
}
Armor* GeneratorInventoryItem::generateArmor(Rarity minRarity, Rarity maxRarity) {
  return generateArmor(_armorGenerator.getSlot(), minRarity, maxRarity);
}
vector<Armor*> GeneratorInventoryItem::generateEquipmnets(Rarity minRarity, Rarity maxRarity) {
  return vector<Armor*>{generateArmor(Slot::Helmet, minRarity, maxRarity),
                        generateArmor(Slot::Armour, minRarity, maxRarity),
                        generateArmor(Slot::Boots, minRarity, maxRarity)};
}
