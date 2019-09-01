//
// Created by  on 19.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_ENVIRONMENTCOMPONENTS_SHOPCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_ENVIRONMENTCOMPONENTS_SHOPCOMPONENT_H_

#include <memory>
#include <vector>
#include "ecs/IComponent.h"
#include "game/Components/ItemComponents/ArmorComponent.h"

class ShopComponent : public IComponent {
 public:
  int loyalty{};
  std::vector<std::unique_ptr<InventoryItem>> items;

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

#endif  // INCLUDE_GAME_COMPONENTS_ENVIRONMENTCOMPONENTS_SHOPCOMPONENT_H_
