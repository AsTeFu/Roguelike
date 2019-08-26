//
// Created by AsTeFu on 21.07.2019.
//

#include "game/Scenes/MenuScene.h"
#include <BearLibTerminal.h>
#include <algorithm>
#include "game/Scenes/GameScene.h"
#include "game/Scenes/SceneManager.h"
#include "game/Scenes/SettingScene.h"
#include "game/Scenes/SpecialScene.h"
#include "game/Utility/ConfigTerminal.h"
#include "game/Utility/Input.h"
#include "game/Utility/Vector2.h"

void MenuScene::update(SceneManager* sceneManager) {
  inputMenu(sceneManager);
}
void MenuScene::start(SceneManager* sceneManager) {
  // update(sceneManager);
  render();
}
void MenuScene::end(SceneManager* sceneManager) {}
void MenuScene::render() {
  terminal_layer(47);
  terminal_clear_area(0, 0, ConfigTerminal::sizeTerminal.getX(), ConfigTerminal::sizeTerminal.getY());
  terminal_color(color_from_argb(255, 255, 255, 255));

  Vector2 firstPos = {ConfigTerminal::sizeTerminal.getX() / 2 - 10, ConfigTerminal::sizeTerminal.getY() / 2 - 5};

  terminal_printf(firstPos.getX(), firstPos.getY() - 5, "Roguelike by ATF");

  int offsetY = 0;
  for (const auto& item : _menuItems) terminal_printf(firstPos.getX(), firstPos.getY() + offsetY++, item.c_str());

  terminal_printf(firstPos.getX() - 2, firstPos.getY() + _menuItem, ">");

  terminal_print(5, 2,
                 "{\\__/}\n"
                 "( ●_●) держи вкусняшку\n"
                 "( >>[color=green]*[/color])");
}
void MenuScene::inputMenu(SceneManager* context) {
  if (Input::isPressed(TK_UP))
    increase();
  else if (Input::isPressed(TK_DOWN))
    decrease();

  if (Input::isPressed(TK_ENTER)) enterMenuItem(context);
}

void MenuScene::decrease() {
  _menuItem = std::min<int>(_menuItems.size() - 1, _menuItem + 1);
}
void MenuScene::increase() {
  _menuItem = std::max(0, _menuItem - 1);
}

void MenuScene::enterMenuItem(SceneManager* context) {
  std::cout << _menuItems[_menuItem] << std::endl;
  terminal_clear_area(0, 0, ConfigTerminal::sizeTerminal.getX(), ConfigTerminal::sizeTerminal.getY());

  if (_menuItem == NewGame) {
    context->switchScene("InputName");
    // GameScene::getInstance()->newGame();
  }
  if (_menuItem == Continue) {
    context->switchScene("Creator");
    // context->switchScene(SpecialScene::getInstance());
    // context->switchScene(GameScene::getInstance());
    // GameScene::getInstance()->continueGame();
  }
  if (_menuItem == Setting) {
    // context->switchScene(SettingScene::getInstance());
  }
  if (_menuItem == Exit) {
    terminal_close();
  }
}
