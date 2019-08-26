//
// Created by AsTeFu on 14.07.2019.
//

#include "game/Windows/InventoryWindow.h"
#include <game/RoomManager/Room.h>
#include <game/Utility/ConfigTerminal.h>
#include <game/Utility/DTO/PlayerDTO.h>
#include <string>
void InventoryWindow::render(const PlayerDTO& dto) const {
  configurateTerminal();

  int leftIndent = 5;
  int topIndent = 2;
  int offsetX = _config.position.getX() + leftIndent;
  int offsetY = _config.position.getY() + topIndent;

  terminal_printf(offsetX, offsetY++, "Rooms:   %d", Room::countRoom);
  offsetY += 1;

  terminal_printf(offsetX, offsetY++, "Name:    %s", dto.name.c_str());
  terminal_printf(offsetX, offsetY++, "Health:  [color=red]%d", dto.health);
  terminal_printf(offsetX, offsetY++, "Cash:    [color=yellow]%d", dto.cash);
  terminal_printf(offsetX, offsetY++, "Food:    [color=green]%d", dto.food);
  terminal_printf(offsetX, offsetY++, "Steps:   %d", dto.steps);

  offsetY += 1;
  terminal_printf(offsetX, offsetY++, "Level:   %d", dto.level->currentLevel);
  terminal_printf(offsetX, offsetY++, "Experience:   %d/%d", dto.level->currentExperience, dto.level->maxExperience);

  offsetY += 1;
  horizontalLine({offsetX - leftIndent, offsetY}, _config.size);
  terminal_print(offsetX, offsetY, "EQUIPMENTS");

  offsetY += 2;

  int protect = 0;
  int dodge = 0;
  for (const auto& pair : dto.armor->equipments) {
    protect += pair.second->protect;
    dodge += pair.second->dodge;
  }

  terminal_print(offsetX, offsetY++, "EQUIPMENT STATS");

  int damage = dto.weapon->weapon->damage;
  if (dto.abilities->hasAbility("Кровавая баня")) damage = static_cast<int>(120 * damage / 100.0);

  terminal_printf(offsetX, offsetY++, "Average damage:  [color=red]%d", damage + dto.special->getValue(STRENGTH) * 2);
  terminal_printf(offsetX, offsetY++, "Average protect: [color=dark blue]%d",
                  protect + dto.special->getValue(ENDURANCE) * 2);
  offsetY++;

  int critical = dto.weapon->weapon->chanceCritical;
  if (dto.abilities->hasAbility("Точность")) critical += 15;
  terminal_printf(offsetX, offsetY++, "Critical chance: %d", critical);
  terminal_printf(offsetX, offsetY++, "Chance dodge:    %d", dodge);
  offsetY++;

  terminal_print(offsetX, offsetY++, "EQUIPMENTS");
  dto.weapon->weapon->printItem(offsetX, offsetY++);
  for (const auto& pair : dto.armor->equipments) {
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
void InventoryWindow::printWeapon(const Weapon* weapon, int posX, int posY) const {
  terminal_printf(posX, posY, "Weapon: [color=%s]%s[/color] DMG: [color=red]%d[/color], CR: %d",
                  ConfigTerminal::rarityName[weapon->rarity - 1].c_str(), weapon->name.c_str(), weapon->damage,
                  weapon->chanceCritical);
}
void InventoryWindow::printArmor(const ArmorComponent* armor, int posX, int posY) const {
  printArmor(*armor->equipments.at(Helmet), "Helmet:", posX, &posY);
  printArmor(*armor->equipments.at(Armour), "Armour:", posX, &posY);
  printArmor(*armor->equipments.at(Boots), "Boots: ", posX, &posY);
}
void InventoryWindow::printArmor(const Armor& armor, const std::string& slot, int x, int* y) const {
  terminal_printf(x, (*y)++, "%s [color=%s]%s[/color] PR: [color=dark blue]%d[/color], DG: %d", slot.c_str(),
                  ConfigTerminal::rarityName[armor.rarity - 1].c_str(), armor.name.c_str(), armor.protect, armor.dodge);

  int leftIndent = 4;
  for (const auto& effect : armor.effects) {
    terminal_printf(x + leftIndent, (*y)++, "%s: %d", effect.first.c_str(), effect.second);
  }
}
