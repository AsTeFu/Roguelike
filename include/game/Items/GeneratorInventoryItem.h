//
// Created by AsTeFu on 10.08.2019.
//

#ifndef INCLUDE_GAME_ITEMS_GENERATORINVENTORYITEM_H_
#define INCLUDE_GAME_ITEMS_GENERATORINVENTORYITEM_H_

#include <game/Components/ItemComponents/ArmorComponent.h>
#include <game/Components/ItemComponents/SpecialComponent.h>
#include <game/Components/ItemComponents/WeaponComponent.h>
#include <game/Items/Inventory/Generator/ReadersItems/ReaderItems.h>
#include <map>
#include <string>
#include <utility>
#include <vector>

using std::map;
using std::string;
using std::vector;

// TODO(AsTeFu): возможно разнести по разным файлам

class ItemGenerator {
 protected:
  // static map<int, vector<string>> names;

  Rarity getRarity(Rarity maxRarity);
  virtual int getCost(Rarity rarity, int mainStat);

 public:
  // explicit ItemGenerator(const map<int, vector<string>>& name) : names(name) {}
};

class WeaponGenerator : public ItemGenerator {
 private:
  static map<int, vector<string>> names;
  static vector<Range> damageRanges;

  std::string& getRandomName(int rarity);
  int getDamage(Rarity rarity);

 public:
  // WeaponGenerator() : ItemGenerator(ReaderItems::readWeapon()), damageRanges(ReaderItems::readDamage()) {}
  Weapon* generateWeapon(Rarity maxRarity);
  Weapon* generateWeapon(Rarity minRarity, Rarity maxRarity);
};

class ArmorGenerator : public ItemGenerator {
 private:
  static map<int, vector<string>> names;
  static vector<Range> protectRanges;

  static std::string& getRandomName(int rarity);
  int getProtect(int rarity);
  std::map<std::string, int> setEffects(Rarity rarity);

 public:
  // ArmorGenerator() : ItemGenerator(ReaderItems::readArmor()), protectRanges(ReaderItems::readProtect()) {}
  Slot getSlot();
  Armor* generateArmor(Slot slot, Rarity maxRarity);
  Armor* generateArmor(Slot slot, Rarity minRarity, Rarity maxRarity);
  int getDodge(Rarity rarity) const;
};

class GeneratorInventoryItem {
  ArmorGenerator _armorGenerator;
  WeaponGenerator _weaponGenerator;

 public:
  Armor* generateArmor();
  Armor* generateArmor(Rarity maxRarity);
  Armor* generateArmor(Rarity minRarity, Rarity maxRarity);
  Armor* generateArmor(Slot slot, Rarity maxRarity);
  Armor* generateArmor(Slot slot, Rarity minRarity, Rarity maxRarity);
  vector<Armor*> generateEquipmnets(Rarity minRarity, Rarity maxRarity);
  Weapon* generateWeapon();
  Weapon* generateWeapon(Rarity maxRarity);
  Weapon* generateWeapon(Rarity minRarity, Rarity maxRarity);
  int generateCoin();
  int generateFood();
  int generateMedkit();
};

#endif  // INCLUDE_GAME_ITEMS_GENERATORINVENTORYITEM_H_
