//
// Created by AsTeFu on 26.07.2019.
//

#include "game/Items/Inventory/Generator/ReadersItems/ReaderItems.h"

#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

map<int, vector<string>> ReaderItems::readArmor() {
  return readNames("Resource/Inventory/armorNames.txt");
}

map<int, vector<string>> ReaderItems::readWeapon() {
  return readNames("Resource/Inventory/weaponNames.txt");
}
vector<Range> ReaderItems::readDamage() {
  return readRange("Resource/Inventory/weaponDamage.txt");
}
vector<Range> ReaderItems::readProtect() {
  return readRange("Resource/Inventory/armorProtect.txt");
}

map<int, vector<string>> ReaderItems::readNames(const std::string& path) {
  map<int, vector<string>> mp;

  string buffer;
  std::ifstream file(path);

  if (file.is_open()) {
    std::cout << "File names is opened: " << path << std::endl;

    int rarity = 0;
    while (getline(file, buffer)) {
      if (buffer.at(0) == '#') {
        rarity++;
        continue;
      }

      mp[rarity].push_back(buffer);
    }

    file.close();
  } else {
    std::cout << "File path: " << path << " doesn't exits!" << std::endl;
  }

  return mp;
}

vector<Range> ReaderItems::readRange(const std::string& path) {
  vector<Range> ranges;

  string buffer;
  std::ifstream file(path);

  if (file.is_open()) {
    std::cout << "File ranges is opened: " << path << std::endl;

    int rarity = 0;
    while (getline(file, buffer)) {
      if (buffer.at(0) == '#') {
        rarity++;
        continue;
      }

      int a, b;
      std::stringstream ss;
      ss << buffer;
      ss >> a >> b;
      ranges.emplace_back(a, b);
    }

    file.close();
  } else {
    std::cout << "File path: " << path << " doesn't exits!" << std::endl;
  }

  return ranges;
}
