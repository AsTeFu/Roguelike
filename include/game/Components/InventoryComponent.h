//
// Created by  on 11.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_INVENTORYCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_INVENTORYCOMPONENT_H_

#include <map>
#include <memory>
#include <string>
#include <vector>
#include "ecs/IComponent.h"
#include "game/Components/ArmorComponent.h"
#include "game/Components/WeaponComponent.h"

class InventoryComponent : public IComponent {
 public:
  std::vector<std::unique_ptr<InventoryItem>> items;
  size_t maxItems;

  explicit InventoryComponent(size_t maxItems) : maxItems(maxItems) {}
  InventoryComponent(const std::vector<InventoryItem*>& items, size_t maxItems) : maxItems(maxItems) {
    for (const auto& item : items) {
      if (item->itemType == ArmorType) addItem<Armor>(dynamic_cast<Armor*>(item));
      if (item->itemType == WeaponType) addItem<Weapon>(dynamic_cast<Weapon*>(item));
    }
  }
  InventoryComponent(const InventoryComponent& inventoryComponent) : maxItems(inventoryComponent.maxItems) {
    for (const auto& item : inventoryComponent.items) {
      if (item->itemType == ArmorType) addItem<Armor>(dynamic_cast<Armor*>(item.get()));
      if (item->itemType == WeaponType) addItem<Weapon>(dynamic_cast<Weapon*>(item.get()));
    }
  }

  std::vector<InventoryItem*> getItems() {
    std::vector<InventoryItem*> tmp;
    for (const auto& item : items) tmp.push_back(item.get());
    return tmp;
  }

  template<typename Type>
  void addItem(Type* item) {
    if (items.size() < maxItems) items.push_back(std::unique_ptr<Type>(item));
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

#endif  // INCLUDE_GAME_COMPONENTS_INVENTORYCOMPONENT_H_
