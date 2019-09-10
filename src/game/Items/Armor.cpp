//
// Created by AsTeFu on 31.08.2019.
//
#include <game/Components/EnvironmentComponents/ChestComponent.h>
#include <game/Components/ItemComponents/ArmorComponent.h>
#include <game/Components/ItemComponents/InventoryComponent.h>
#include <game/Components/ItemComponents/SpecialComponent.h>
#include <game/Items/Armor.h>
#include <utilities/Terminal.h>
#include <map>
#include <string>

void Armor::printItem(int x, int y) const {
  Terminal::printf(x, y, "%s [color=%s]%s[/color] PR: %d, DG: %d", getSlotName().c_str(),
                   Config::getInstance().rarityNames[rarity - 1].c_str(), name.c_str(), protect, dodge);
}
int Armor::printItemExtended(int x, int y) const {
  int leftIndent = 4;
  printItem(x, y);
  int i = 0;
  for (const auto& effect : effects) {
    Terminal::printf(x + leftIndent, ++y, "%s: %d", effect.first.c_str(), effect.second);
    i++;
  }
  return i;
}
std::string Armor::getSlotName() const {
  if (slot == Helmet) return "Helmet:";
  if (slot == Armour) return "Armour:";
  if (slot == Boots) return "Boots: ";
  return "Unknown";
}
void Armor::equipItem(Entity* player, ChestComponent* chestComponent, int index) {
  auto armorComponent = player->getComponent<ArmorComponent>();

  auto* newItem = new Armor(*this);
  auto* oldItem = new Armor(*armorComponent->equipments[newItem->slot]);
  chestComponent->items[index] = std::unique_ptr<Armor>(oldItem);
  armorComponent->equipments[newItem->slot] = std::unique_ptr<Armor>(newItem);

  updateEffects(player, newItem, oldItem);
}
void Armor::equipItem(Entity* player, int indexItem) {
  auto* newItem = new Armor(*this);
  auto* oldItem = new Armor(*player->getComponent<ArmorComponent>()->equipments[newItem->slot]);
  player->getComponent<InventoryComponent>()->items[indexItem] = std::unique_ptr<Armor>(oldItem);
  player->getComponent<ArmorComponent>()->equipments[newItem->slot] = std::unique_ptr<Armor>(newItem);

  updateEffects(player, newItem, oldItem);
}

void Armor::addItemToInventory(InventoryComponent* inventory) {
  inventory->addItem<Armor>(new Armor(*this));
}

void Armor::takeItem(Entity* player) {
  auto* armor = new Armor(*this);
  player->getComponent<InventoryComponent>()->items.push_back(std::unique_ptr<Armor>(armor));
}

void Armor::updateEffects(const Entity* player, const Armor* newItem, const Armor* oldItem) const {
  auto special = player->getComponent<SpecialComponent>();
  special->addictiveSpecial.removePoints(oldItem->effects);
  special->addictiveSpecial.addPoints(newItem->effects);
}
Armor::Armor(const std::string& name, Rarity rarity, int cost, Slot slot, int protect, int dodge,
             std::map<std::string, int> effects)
    : InventoryItem(name, rarity, cost),
      slot(slot),
      protect(protect),
      dodge(dodge),
      effects(std::move(effects)) {}
