//
// Created by AsTeFu on 14.07.2019.
//

#include "game/Windows/InventoryWindow.h"
#include <game/Components/HealthComponent.h>
#include <game/Components/NameComponent.h>
#include <game/Components/StarvationComponent.h>
#include <game/Components/StepsComponent.h>
#include <game/Components/WalletComponent.h>
#include <game/RoomManager/Room.h>
#include <game/Utility/ConfigTerminal.h>
#include <game/Utility/DTO/PlayerDTO.h>
#include <string>
void InventoryWindow::render(Entity* const player) const {
  configurateTerminal();

  int leftIndent = 5;
  int topIndent = 2;
  int offsetX = _config.position.getX() + leftIndent;
  int offsetY = _config.position.getY() + topIndent;

  terminal_printf(offsetX, offsetY++, "Rooms:   %d", Room::countRoom);
  offsetY += 1;

  terminal_printf(offsetX, offsetY++, "Name:    %s", player->getComponent<NameComponent>()->name.c_str());
  terminal_printf(offsetX, offsetY++, "Health:  [color=red]%d", player->getComponent<HealthComponent>()->health);
  terminal_printf(offsetX, offsetY++, "Cash:    [color=yellow]%d", player->getComponent<WalletComponent>()->cash);
  terminal_printf(offsetX, offsetY++, "Food:    [color=green]%d",
                  player->getComponent<StarvationComponent>()->currentFood);
  terminal_printf(offsetX, offsetY++, "Steps:   %d", player->getComponent<StepsComponent>()->currentSteps);

  offsetY += 1;
  terminal_printf(offsetX, offsetY++, "Level:   %d", player->getComponent<LevelComponent>()->currentLevel);
  terminal_printf(offsetX, offsetY++, "Experience:   %d/%d", player->getComponent<LevelComponent>()->currentExperience,
                  player->getComponent<LevelComponent>()->maxExperience);

  offsetY += 1;
  horizontalLine({offsetX - leftIndent, offsetY}, _config.size);
  terminal_print(offsetX, offsetY, "EQUIPMENTS");

  offsetY += 2;

  terminal_print(offsetX, offsetY++, "EQUIPMENT STATS");

  int damage = player->getComponent<WeaponComponent>()->weapon->damage;
  // if (dto.abilities->hasAbility("Кровавая баня")) damage = static_cast<int>(120 * damage / 100.0);

  auto special = player->getComponent<SpecialComponent>();

  terminal_printf(offsetX, offsetY++, "Average damage:  [color=red]%d", damage + special->getValue(STRENGTH) * 2);
  terminal_printf(offsetX, offsetY++, "Average protect: [color=dark blue]%d",
                  player->getComponent<ArmorComponent>()->getProtect() + special->getValue(ENDURANCE) * 2);
  offsetY++;

  int critical = player->getComponent<WeaponComponent>()->weapon->chanceCritical;
  // if (dto.abilities->hasAbility("Точность")) critical += 15;
  terminal_printf(offsetX, offsetY++, "Critical chance: %d", critical);
  terminal_printf(offsetX, offsetY++, "Chance dodge:    %d", player->getComponent<ArmorComponent>()->getDodge());
  offsetY++;

  terminal_print(offsetX, offsetY++, "EQUIPMENTS");
  player->getComponent<WeaponComponent>()->weapon->printItem(offsetX, offsetY++);
  for (const auto& pair : player->getComponent<ArmorComponent>()->equipments) {
    pair.second->printItem(offsetX, offsetY++);
  }
  offsetY += 4;

  verticalBorder();
  horizontalBorder();
  terminal_print(offsetX, _config.position.getY(), _config.name.c_str());
}
InventoryWindow::InventoryWindow(const WindowConfig& config) : BaseGameWindow(config) {
  // terminal_layer(_config.layer);
  // terminal_crop(_config.position.getX(), _config.position.getY(), _config._size.getX(), _config._size.getY());
  std::cout << "Inv (layer: " << _config.layer << "); Position: " << _config.position << "; Size " << _config.size
            << std::endl;
}
