//
// Created by  on 11.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_ITEMCOMPONENTS_INVENTORYCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_ITEMCOMPONENTS_INVENTORYCOMPONENT_H_

#include <game/Items/InventoryItem.h>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "ecs/IComponent.h"

class InventoryComponent : public IComponent {
 public:
  std::vector<std::unique_ptr<InventoryItem>> items;
  size_t maxItems;

  explicit InventoryComponent(size_t maxItems) : maxItems(maxItems) {}

  InventoryComponent(const InventoryComponent& inventoryComponent) : maxItems(inventoryComponent.maxItems) {
    for (const auto& item : inventoryComponent.items) {
      item->addItemToInventory(this);
      // if (item->itemType == ArmorType) addItem<Armor>(dynamic_cast<Armor*>(item.get()));
      // if (item->itemType == WeaponType) addItem<Weapon>(dynamic_cast<Weapon*>(item.get()));
    }
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
  void setInventory(InventoryComponent* inventoryComponent) {
    maxItems = inventoryComponent->maxItems;
    items.clear();
    /* for (const auto& item : inventoryComponent->items) {

      if (item->itemType == ArmorType) addItem<Armor>(dynamic_cast<Armor*>(item.get()));
      if (item->itemType == WeaponType) addItem<Weapon>(dynamic_cast<Weapon*>(item.get()));
    } */
  }
};

#endif  // INCLUDE_GAME_COMPONENTS_ITEMCOMPONENTS_INVENTORYCOMPONENT_H_
