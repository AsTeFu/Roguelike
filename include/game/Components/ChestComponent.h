//
// Created by  on 10.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_CHESTCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_CHESTCOMPONENT_H_

#include <map>
#include <memory>
#include <typeindex>
#include <utility>
#include <vector>
#include "ecs/IComponent.h"
#include "game/Components/ArmorComponent.h"

class ChestComponent : public IComponent {
 public:
  bool isOpen;
  std::vector<std::unique_ptr<InventoryItem>> items;

  ChestComponent() : isOpen(false) {}

  template<typename Type>
  void addItem(Type* item) {
    items.push_back(std::unique_ptr<Type>(item));
  }

  template<typename Type>
  Type* getItem(int i) {
    auto item = items[i].get();
    return dynamic_cast<Type*>(item);
  }
  void deleteItem(int i) {
    items.erase(items.begin() + i);
  }
};

#endif  // INCLUDE_GAME_COMPONENTS_CHESTCOMPONENT_H_
