//
// Created by AsTeFu on 26.07.2019.
//

#ifndef INCLUDE_GAME_ITEMS_INVENTORY_GENERATOR_READERSITEMS_READERITEMS_H_
#define INCLUDE_GAME_ITEMS_INVENTORY_GENERATOR_READERSITEMS_READERITEMS_H_

#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

class Range {
 public:
  int minValue;
  int maxValue;
  Range(int min, int max) : minValue(min), maxValue(max) {}
};

class ReaderItems {
 private:
  static map<int, vector<string>> readNames(const string& path);

 public:
  static map<int, vector<string>> readArmor();
  static map<int, vector<string>> readWeapon();
  static vector<Range> readRange(const string& path);
  static vector<Range> readDamage();
  static vector<Range> readProtect();
};

#endif  // INCLUDE_GAME_ITEMS_INVENTORY_GENERATOR_READERSITEMS_READERITEMS_H_
