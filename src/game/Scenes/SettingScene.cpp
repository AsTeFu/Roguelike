//
// Created by AsTeFu on 22.07.2019.
//
#include "game/Scenes/SettingScene.h"
#include <BearLibTerminal.h>
#include <string>
#include "game/Scenes/MenuScene.h"
#include "game/Utility/ConfigTerminal.h"
#include "game/Utility/Input.h"

void SettingScene::update(SceneManager* context) {
  if (Input::isPressed(TK_ENTER) || Input::isPressed(TK_ESCAPE)) {
    terminal_clear_area(0, 0, ConfigTerminal::sizeTerminal.getX(), ConfigTerminal::sizeTerminal.getY());
    // context->switchScene(MenuScene::getInstance());
  }
}
void SettingScene::start(SceneManager* context) {}
void SettingScene::end(SceneManager* context) {}
void SettingScene::render() {
  terminal_layer(3);
  terminal_color(color_from_argb(255, 255, 255, 255));

  Vector2 size(ConfigTerminal::sizeTerminal.getX() - 20, 3);
  Vector2 position(10, 3);
  drawHeader(position, size, "Setting");

  std::string message1 = "Напиши, чтобы ты хотел здесь настроить в гугл форму";
  std::string message2 = "Back (Enter or Escape)";
  terminal_printf(position.getX() + size.getX() / 2 - message1.length() / 4 + 1, position.getY() + 4, message1.c_str());
  terminal_printf(position.getX() + size.getX() / 2 - message2.length(), position.getY() + 5, message2.c_str());
}
