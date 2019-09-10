//
// Created by AsTeFu on 14.07.2019.
//

#include "game/Windows/InventoryWindow.h"
#include <game/Components/ItemComponents/HealthComponent.h>
#include <game/Components/PlayerComponents/NameComponent.h>
#include <game/Components/PlayerComponents/StarvationComponent.h>
#include <game/Components/PlayerComponents/StepsComponent.h>
#include <game/Components/PlayerComponents/WalletComponent.h>
#include <game/RoomManager/Room.h>
#include <game/Scenes/SceneRenderUtility.h>
#include <game/Utility/Config.h>
#include <game/Utility/DTO/PlayerDTO.h>
#include <string>

InventoryWindow::InventoryWindow(const WindowConfig& config) : BaseGameWindow(config) {
  Terminal::setLayer(_config.layer);
  Terminal::crop(_config.position, _config.size);
  std::cout << "Inv (layer: " << _config.layer << "); Position: " << _config.position << "; Size " << _config.size
            << std::endl;
}

void InventoryWindow::render(Entity* const player) const {
  configurateTerminal();

  int x = _config.position.getX() + leftMargin;
  int y = _config.position.getY() + topMargin;

  Terminal::printf(x, y, "Rooms:   %d", Room::countRoom);
  y += 2;

  y = drawPlayerStats(player, x, y) + 1;
  y = drawPlayerLevel(player, x, y) + 1;

  SceneRenderUtility::horizontalLine(x - leftMargin, y, _config.size.getX());
  Terminal::print(x, y, "EQUIPMENTS");

  y += 2;
  Terminal::print(x, y++, "EQUIPMENT STATS");
  y = drawEquipmentStats(player, x, y);
  y = drawPlayerEquipments(player, x, y);

  SceneRenderUtility::drawBorder(_config.position, _config.size);
  Terminal::printf(x, _config.position.getY(), _config.name.c_str());
}

int InventoryWindow::drawPlayerStats(const Entity* player, int x, int y) const {
  Terminal::printf(x, y++, "Name:    %s", getName(player).c_str());
  Terminal::printf(x, y++, "Health:  [color=red]%d", getHealth(player));
  Terminal::printf(x, y++, "Cash:    [color=yellow]%d", getCash(player));
  Terminal::printf(x, y++, "Food:    [color=green]%d", getFood(player));
  Terminal::printf(x, y++, "Steps:   %d", getSteps(player));
  return y;
}
int InventoryWindow::drawPlayerLevel(const Entity* player, int x, int y) const {
  Terminal::printf(x, y++, "Level:   %d", getLevel(player));
  Terminal::printf(x, y++, "Experience:   %d/%d", getExperience(player), getMaxExperience(player));
  return y;
}

int InventoryWindow::getSteps(const Entity* player) const {
  return player->getComponent<StepsComponent>()->currentSteps;
}
int InventoryWindow::getFood(const Entity* player) const {
  return player->getComponent<StarvationComponent>()->currentFood;
}
int InventoryWindow::getCash(const Entity* player) const {
  return player->getComponent<WalletComponent>()->cash;
}
int InventoryWindow::getHealth(const Entity* player) const {
  return player->getComponent<HealthComponent>()->health;
}
string& InventoryWindow::getName(const Entity* player) const {
  return player->getComponent<NameComponent>()->name;
}

int InventoryWindow::getMaxExperience(const Entity* player) const {
  return player->getComponent<LevelComponent>()->maxExperience;
}
int InventoryWindow::getExperience(const Entity* player) const {
  return player->getComponent<LevelComponent>()->currentExperience;
}
int InventoryWindow::getLevel(const Entity* player) const {
  return player->getComponent<LevelComponent>()->currentLevel;
}

int InventoryWindow::drawEquipmentStats(const Entity* player, int x, int y) const {
  auto weapon = player->getComponent<WeaponComponent>()->weapon.get();
  auto special = player->getComponent<SpecialComponent>();

  Terminal::printf(x, y++, "Average damage:  [color=red]%d", weapon->damage + special->getValue(STRENGTH) * 2);
  Terminal::printf(x, y++, "Average protect: [color=dark blue]%d",
                   player->getComponent<ArmorComponent>()->getProtect() + special->getValue(ENDURANCE) * 2);

  y += 1;

  Terminal::printf(x, y++, "Critical chance: %d", weapon->chanceCritical);
  Terminal::printf(x, y++, "Chance dodge:    %d", player->getComponent<ArmorComponent>()->getDodge());
  return y + 1;
}
int InventoryWindow::drawPlayerEquipments(const Entity* player, int x, int y) const {
  Terminal::print(x, y++, "EQUIPMENTS");
  player->getComponent<WeaponComponent>()->weapon->printItem(x, y++);
  for (const auto& pair : player->getComponent<ArmorComponent>()->equipments) pair.second->printItem(x, y++);
  return y;
}
