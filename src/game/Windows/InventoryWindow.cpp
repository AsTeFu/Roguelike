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
void InventoryWindow::render(Entity* const player) const {
  configurateTerminal();

  int leftIndent = 5;
  int topIndent = 2;
  int offsetX = _config.position.getX() + leftIndent;
  int offsetY = _config.position.getY() + topIndent;

  Terminal::printf(offsetX, offsetY++, "Rooms:   %d", Room::countRoom);
  offsetY += 1;

  Terminal::printf(offsetX, offsetY++, "Name:    %s", player->getComponent<NameComponent>()->name.c_str());
  Terminal::printf(offsetX, offsetY++, "Health:  [color=red]%d", player->getComponent<HealthComponent>()->health);
  Terminal::printf(offsetX, offsetY++, "Cash:    [color=yellow]%d", player->getComponent<WalletComponent>()->cash);
  Terminal::printf(offsetX, offsetY++, "Food:    [color=green]%d",
                   player->getComponent<StarvationComponent>()->currentFood);
  Terminal::printf(offsetX, offsetY++, "Steps:   %d", player->getComponent<StepsComponent>()->currentSteps);

  offsetY += 1;
  Terminal::printf(offsetX, offsetY++, "Level:   %d", player->getComponent<LevelComponent>()->currentLevel);
  Terminal::printf(offsetX, offsetY++, "Experience:   %d/%d", player->getComponent<LevelComponent>()->currentExperience,
                   player->getComponent<LevelComponent>()->maxExperience);

  offsetY += 1;
  SceneRenderUtility::horizontalLine(offsetX - leftIndent, offsetY, _config.size.getX());
  Terminal::print(offsetX, offsetY, "EQUIPMENTS");

  offsetY += 2;

  Terminal::print(offsetX, offsetY++, "EQUIPMENT STATS");

  int damage = player->getComponent<WeaponComponent>()->weapon->damage;
  // if (dto.abilities->hasAbility("Кровавая баня")) damage = static_cast<int>(120 * damage / 100.0);

  auto special = player->getComponent<SpecialComponent>();

  Terminal::printf(offsetX, offsetY++, "Average damage:  [color=red]%d", damage + special->getValue(STRENGTH) * 2);
  Terminal::printf(offsetX, offsetY++, "Average protect: [color=dark blue]%d",
                   player->getComponent<ArmorComponent>()->getProtect() + special->getValue(ENDURANCE) * 2);
  offsetY++;

  int critical = player->getComponent<WeaponComponent>()->weapon->chanceCritical;
  // if (dto.abilities->hasAbility("Точность")) critical += 15;
  Terminal::printf(offsetX, offsetY++, "Critical chance: %d", critical);
  Terminal::printf(offsetX, offsetY++, "Chance dodge:    %d", player->getComponent<ArmorComponent>()->getDodge());
  offsetY++;

  Terminal::print(offsetX, offsetY++, "EQUIPMENTS");
  player->getComponent<WeaponComponent>()->weapon->printItem(offsetX, offsetY++);
  for (const auto& pair : player->getComponent<ArmorComponent>()->equipments) {
    pair.second->printItem(offsetX, offsetY++);
  }
  offsetY += 4;

  Terminal::printf(offsetX, _config.position.getY(), _config.name.c_str());
}
InventoryWindow::InventoryWindow(const WindowConfig& config) : BaseGameWindow(config) {
  // terminal_layer(_config.layer);
  // terminal_crop(_config.position.getX(), _config.position.getY(), _config._size.getX(), _config._size.getY());
  std::cout << "Inv (layer: " << _config.layer << "); Position: " << _config.position << "; Size " << _config.size
            << std::endl;
}
