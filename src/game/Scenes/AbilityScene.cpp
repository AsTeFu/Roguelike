//
// Created by AsTeFu on 20.08.2019.
//

#include "game/Scenes/AbilityScene.h"
#include <BearLibTerminal.h>
#include <game/Utility/ConfigTerminal.h>
#include <game/Utility/Input.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

AbilityScene::AbilityScene(Context *const context, SceneManager *sceneManager)
    : Scene(context, sceneManager), _side(LeftSide) {
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

  // TODO(ATF): в функцию
  string buffer1;
  string buffer2;
  std::ifstream file1("Resource/Abilities.txt");

  if (file1.is_open()) {
    while (getline(file1, buffer1)) {
      getline(file1, buffer2);
      _abilities.emplace_back(buffer1, buffer2);
      file1.ignore();
    }

    file1.close();
  } else {
    std::cout << "File abilities doesn't exits!" << std::endl;
  }
}

void AbilityScene::start(SceneManager *sceneManager) {
  enhanceDto = sceneManager->getContext()->getObject<EnhanceDTO>();
  _currentItem = 0;
}

void AbilityScene::update(SceneManager *sceneManager) {
  if (Input::isPressed(TK_ESCAPE)) {
    sceneManager->switchScene("Game");
  }

  if (Input::isPressed(TK_LEFT)) {
    _side = LeftSide;
    _currentItem = 0;
  }
  if (Input::isPressed(TK_RIGHT)) {
    _side = RightSide;
    _currentItem = 0;
  }

  if (_side == LeftSide) {
    if (Input::isPressed(TK_UP)) {
      if (_currentItem > 0) _currentItem--;
    }
    if (Input::isPressed(TK_DOWN)) {
      if (_currentItem + 1 < static_cast<int>(ConfigTerminal::statsSpecial.size())) _currentItem++;
    }
    if (Input::isPressed(TK_ENTER) || Input::isPressed(TK_SPACE)) {
      if (enhanceDto->specialComponent->special.getValue(ConfigTerminal::statsSpecial[_currentItem]) <
          ConfigTerminal::maxPointsSpecial) {
        enhanceDto->specialComponent->special.addPoint(ConfigTerminal::statsSpecial[_currentItem]);
      }
    }
  }

  if (_side == RightSide) {
    if (Input::isPressed(TK_UP)) {
      if (_currentItem > 0) _currentItem--;
    }
    if (Input::isPressed(TK_DOWN)) {
      if (_currentItem + 1 < static_cast<int>(_abilities.size())) _currentItem++;
    }
    if (Input::isPressed(TK_ENTER) || Input::isPressed(TK_SPACE)) {
      if (enhanceDto->abilitiesComponent->available &&
          !std::count(enhanceDto->abilitiesComponent->abilities.begin(),
                      enhanceDto->abilitiesComponent->abilities.end(), _abilities[_currentItem])) {
        enhanceDto->abilitiesComponent->available--;
        enhanceDto->abilitiesComponent->abilities.push_back(_abilities[_currentItem]);

        // TODO(ATF): убрать этот позор, переделать, делал в ночь перед демкой
        if (_abilities[_currentItem].name == "Интенсивная тренировка")
          enhanceDto->specialComponent->special.addAvailablePoint();
        else if (_abilities[_currentItem].name == "Фонтан жизни")
          enhanceDto->healthComponent->health += 300;
        else if (_abilities[_currentItem].name == "Прилежный ученик")
          enhanceDto->levelComponent->bonus = 25;
        else if (_abilities[_currentItem].name == "Здесь и сейчас") {
          enhanceDto->levelComponent->addExperience(enhanceDto->levelComponent->maxExperience -
                                                    enhanceDto->levelComponent->currentExperience + 1);
          enhanceDto->specialComponent->special.addAvailablePoint();
          enhanceDto->abilitiesComponent->available++;
        }
      }
    }
  }
}
void AbilityScene::render() {
  if (_side == LeftSide) leftRender();
  if (_side == RightSide) rightRender();
}

void AbilityScene::leftRender() {
  terminal_clear();

  int topIndent = 2;
  int leftIndent = 10;
  Vector2 position(0, 0);
  Vector2 size(ConfigTerminal::sizeTerminal.getX() - leftIndent * 2, 20);

  int offsetX = leftIndent + position.getX();
  int offsetY = topIndent + position.getY();

  drawHeader({offsetX, offsetY}, {ConfigTerminal::sizeTerminal.getX() - leftIndent * 2, 4}, "Enhance");

  offsetY += 5;

  horizontalBorder({offsetX, offsetY}, size);
  verticalBorder({offsetX, offsetY}, size);

  int rightSideOffsetX = (size.getX() - leftIndent) / 2;
  verticalLine({rightSideOffsetX, offsetY}, {1, size.getY()});

  size.setY(15);
  horizontalBorder({offsetX, offsetY + 20}, size);
  verticalBorder({offsetX, offsetY + 20}, size);

  offsetX += leftIndent / 2 + 4;
  offsetY += 2;

  int startOffsetY = offsetY;

  terminal_printf(offsetX, offsetY++, "S.P.E.C.I.A.L.");
  if (enhanceDto->specialComponent->special.countPoints())
    terminal_printf(offsetX + 4, offsetY, "available points: %d", enhanceDto->specialComponent->special.countPoints());

  offsetY += 2;

  int i = 0;
  for (const auto &stat : ConfigTerminal::statsSpecial) {
    if (_currentItem == i) {
      terminal_print(offsetX - 3, offsetY, "=>");
    }

    if (enhanceDto->specialComponent->special.getValue(stat) >= 7)
      terminal_color(color_from_name("green"));
    else if (enhanceDto->specialComponent->special.getValue(stat) >= 4)
      terminal_color(color_from_name("yellow"));
    else
      terminal_color(color_from_name("red"));

    if (i == _currentItem) terminal_color("white");

    string tmp;
    for (const auto &symbol : stat) tmp.push_back(toupper(symbol));

    if (enhanceDto->specialComponent->special.countPoints() &&
        enhanceDto->specialComponent->special.getValue(stat) < ConfigTerminal::maxPointsSpecial)
      terminal_printf(offsetX, offsetY, "%s - %d [color=white][[+]]", tmp.c_str(),
                      enhanceDto->specialComponent->special.getValue(stat));
    else
      terminal_printf(offsetX, offsetY, "%s - %d", tmp.c_str(), enhanceDto->specialComponent->special.getValue(stat));

    i++;
    offsetY += 1;
    terminal_color(color_from_name("white"));
  }

  offsetY = startOffsetY + 20;
  offsetX = position.getX() + leftIndent + leftIndent / 2;

  terminal_print(offsetX, offsetY, "DESCRIPTION:");
  offsetY += 2;
  offsetX += 3;

  std::vector<string> items = split(_desription[_currentItem], ' ');
  int line = 100;

  int currentlen = 0;
  int currentY = 0;
  for (const auto &item : items) {
    terminal_print(offsetX + currentlen, offsetY + currentY, item.c_str());
    currentlen += item.length() / 2 + 1;
    if (currentlen > line) {
      currentlen = 0;
      currentY++;
    }
  }

  offsetX = rightSideOffsetX + leftIndent / 2;
  offsetY = startOffsetY;

  terminal_print(offsetX, offsetY++, "[color=gray]ABILITIES");
  if (enhanceDto->abilitiesComponent->available)
    terminal_printf(offsetX + 4, offsetY, "[color=gray]available ability: %d",
                    enhanceDto->abilitiesComponent->available);

  offsetX += 4;
  offsetY += 2;

  for (const auto &ability : _abilities) {
    terminal_color("gray");
    terminal_printf(offsetX, offsetY++, "%s", ability.name.c_str());
  }

  // terminal_printf(offsetX + 4, offsetY, "available ability: %d", 6);

  terminal_color("white");
}

void AbilityScene::rightRender() {
  terminal_clear();

  int topIndent = 2;
  int leftIndent = 10;
  Vector2 position(0, 0);
  Vector2 size(ConfigTerminal::sizeTerminal.getX() - leftIndent * 2, 20);

  int offsetX = leftIndent + position.getX();
  int offsetY = topIndent + position.getY();

  drawHeader({offsetX, offsetY}, {ConfigTerminal::sizeTerminal.getX() - leftIndent * 2, 4}, "Enhance");

  offsetY += 5;

  horizontalBorder({offsetX, offsetY}, size);
  verticalBorder({offsetX, offsetY}, size);

  int rightSideOffsetX = (size.getX() - leftIndent) / 2;
  verticalLine({rightSideOffsetX, offsetY}, {1, size.getY()});

  size.setY(15);
  horizontalBorder({offsetX, offsetY + 20}, size);
  verticalBorder({offsetX, offsetY + 20}, size);

  offsetX += leftIndent / 2 + 4;
  offsetY += 2;

  int startOffsetY = offsetY;

  terminal_printf(offsetX, offsetY++, "[color=gray]S.P.E.C.I.A.L.");
  if (enhanceDto->specialComponent->special.countPoints())
    terminal_printf(offsetX + 4, offsetY, "[color=gray]available points: %d",
                    enhanceDto->specialComponent->special.countPoints());

  offsetY += 2;

  for (const auto &stat : ConfigTerminal::statsSpecial) {
    terminal_color("gray");

    string tmp;
    for (const auto &symbol : stat) tmp.push_back(toupper(symbol));

    terminal_printf(offsetX, offsetY, "%s - %d", tmp.c_str(), enhanceDto->specialComponent->special.getValue(stat));

    offsetY += 1;
    terminal_color(color_from_name("white"));
  }

  offsetY = startOffsetY + 20;
  offsetX = position.getX() + leftIndent + leftIndent / 2;

  terminal_print(offsetX, offsetY, "DESCRIPTION:");
  offsetY += 2;
  offsetX += 3;

  std::vector<string> items = split(_abilities[_currentItem].description, ' ');
  int line = 100;

  int currentlen = 0;
  int currentY = 0;
  for (const auto &item : items) {
    terminal_print(offsetX + currentlen, offsetY + currentY, item.c_str());
    currentlen += item.length() / 2 + 1;
    if (currentlen > line) {
      currentlen = 0;
      currentY++;
    }
  }

  offsetX = rightSideOffsetX + leftIndent / 2;
  offsetY = startOffsetY;

  terminal_print(offsetX, offsetY++, "ABILITIES");
  if (enhanceDto->abilitiesComponent->available)
    terminal_printf(offsetX + 4, offsetY, "available ability: %d", enhanceDto->abilitiesComponent->available);

  offsetX += 4;
  offsetY += 2;

  int i = 0;
  for (const auto &ability : _abilities) {
    if (i == _currentItem) terminal_print(offsetX - 3, offsetY, "[color=white]=>");

    if (std::count(enhanceDto->abilitiesComponent->abilities.begin(), enhanceDto->abilitiesComponent->abilities.end(),
                   ability))
      terminal_color("green");
    else
      terminal_color("gray");

    if (i == _currentItem) terminal_color("white");

    terminal_printf(offsetX, offsetY, "%s", ability.name.c_str());

    i++;
    offsetY += 1;
  }
  terminal_color("white");

  // terminal_printf(offsetX + 4, offsetY, "available ability: %d", 6);
}

std::vector<string> AbilityScene::split(const string &s, char regex) {
  std::stringstream ss(s);
  string item;
  std::vector<string> items;
  while (std::getline(ss, item, regex)) {
    items.push_back(std::move(item));
  }
  return items;
}
