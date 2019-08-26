//
// Created by AsTeFu on 26.07.2019.
//

#include "game/Scenes/SpecialScene.h"
#include <game/Utility/DTO/SpecialDTO.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "game/Scenes/GameScene.h"
#include "game/Utility/ConfigTerminal.h"
#include "game/Utility/Input.h"

void SpecialScene::update(SceneManager* sceneManager) {
  inputMenu(sceneManager);
}
void SpecialScene::inputMenu(SceneManager* sceneManager) {
  if (Input::isPressed(TK_UP))
    increase();
  else if (Input::isPressed(TK_DOWN))
    decrease();

  if (Input::isPressed(TK_LEFT)) downStat();
  if (Input::isPressed(TK_RIGHT)) upStat();

  if (Input::isPressed(TK_ENTER) && _special.countPoints() == 0) {
    // GameScene::getInstance()->setSpicial(_special);
    _context->addObject<SpecialDTO>(_special);
    sceneManager->switchScene("Game");
  }
}

void SpecialScene::decrease() {
  _currentPos = std::min<int>(_special.size() - 1, _currentPos + 1);
}
void SpecialScene::increase() {
  _currentPos = std::max(0, _currentPos - 1);
}

void SpecialScene::start(SceneManager* sceneManager) {
  render();
}
void SpecialScene::end(SceneManager* sceneManager) {}
void SpecialScene::render() {
  terminal_clear();

  Vector2 size(ConfigTerminal::sizeTerminal.getX() - 20, 5);
  Vector2 position(10, 3);
  drawHeader(position, size, "S.P.E.C.I.A.L.");

  Vector2 offset(position.getX() + 3, position.getY() + size.getY() + 2);

  horizontalBorder(offset, {36, 20});
  verticalBorder(offset, {36, 20});
  offset.translate(3, 3);

  terminal_printf(offset.getX() + 5, offset.getY() - 1, "POINTS REMAINING: %d", _special.countPoints());
  offset.translate(0, 2);

  terminal_print(offset.getX(), _currentPos * 2 + offset.getY(), ">");
  for (const auto& stat : ConfigTerminal::statsSpecial) {
    if (_special.getValue(stat) >= 7)
      terminal_color(color_from_name("green"));
    else if (_special.getValue(stat) >= 4)
      terminal_color(color_from_name("yellow"));
    else
      terminal_color(color_from_name("red"));

    string tmp;
    for (const auto& symbol : stat) tmp.push_back(toupper(symbol));

    terminal_print(offset.getX() + 2, offset.getY(), tmp.c_str());
    terminal_printf(offset.getX() + 19, offset.getY(), "%d", _special.getValue(stat));

    terminal_color(color_from_name("white"));
    int offsetX = 0;
    if (_special.getValue(stat) > ConfigTerminal::minPointsSpecial) {
      terminal_printf(offset.getX() + 23, offset.getY(), "[[-]]");
      offsetX += 4;
    }
    if (_special.getValue(stat) < ConfigTerminal::maxPointsSpecial && _special.countPoints() > 0)
      terminal_printf(offset.getX() + 23 + offsetX, offset.getY(), "[[+]]");
    offset.translate(0, 2);
  }

  offset.translate(0, 5);

  drawHeader({20, offset.getY() - 3}, {ConfigTerminal::sizeTerminal.getX() - 40, 4},
             "Распредели все очки и нажми Enter");

  // Descriptions
  offset.set(offset.getX() + 36, position.getY() + size.getY() + 2);
  verticalBorder(offset, {ConfigTerminal::sizeTerminal.getX() - offset.getX() - 15, 20});
  horizontalBorder(offset, {ConfigTerminal::sizeTerminal.getX() - offset.getX() - 15, 20});

  terminal_printf(offset.getX() + 5, offset.getY() + 2, "DESCRIPTION:");

  std::vector<string> items = split(_desription[_currentPos], ' ');
  int line = 60;

  int currentlen = 0;
  int currentY = 0;
  for (const auto& item : items) {
    terminal_print(offset.getX() + 5 + currentlen, offset.getY() + 4 + currentY, item.c_str());
    currentlen += item.length() / 2 + 1;
    if (currentlen > line) {
      currentlen = 0;
      currentY++;
    }
  }
}
SpecialScene::SpecialScene(Context* context, SceneManager* sceneManager)
    : Scene(context, sceneManager),
      _currentPos(0),
      _special(ConfigTerminal::minPointsSpecial, ConfigTerminal::maxPointsSpecial, ConfigTerminal::pointsSpecial) {
  string buffer;
  std::ifstream file("Resource/Direction/Description.txt");

  if (file.is_open()) {
    while (getline(file, buffer)) {
      if (buffer.at(0) == '#') {
        continue;
      }
      _desription.push_back(buffer);
    }

    file.close();
  } else {
    std::cout << "File description doesn't exits!" << std::endl;
  }
  for (const auto& item : ConfigTerminal::statsSpecial) {
    for (int i = 0; i < 4; i++) {
      _special.addPoint(item);
    }
  }
}
void SpecialScene::upStat() {
  _special.addPoint(ConfigTerminal::statsSpecial[_currentPos]);
}
void SpecialScene::downStat() {
  _special.removePoint(ConfigTerminal::statsSpecial[_currentPos]);
}

std::vector<string> SpecialScene::split(const string& s, char regex) {
  std::stringstream ss(s);
  string item;
  vector<string> items;
  while (std::getline(ss, item, regex)) {
    items.push_back(std::move(item));
  }
  return items;
}
