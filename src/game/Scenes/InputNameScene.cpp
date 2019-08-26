//
// Created by AsTeFu on 11.08.2019.
//

#include "game/Scenes/InputNameScene.h"
#include <BearLibTerminal.h>
#include <game/Utility/ConfigTerminal.h>
#include <game/Utility/DTO/NameDTO.h>
#include <game/Utility/Input.h>

void InputNameScene::update(SceneManager *sceneManager) {
  if (Input::isPressed(TK_ESCAPE)) {
    terminal_clear();
    sceneManager->switchScene("Menu");
  }

  if (terminal_read_str(32, 12, name, sizeof(name) - 1) > 4) {
    terminal_clear();
    sceneManager->getContext()->addObject<NameDTO>(name);
    sceneManager->switchScene("Special");
  }
}
void InputNameScene::render() {
  drawHeader({10, 3}, {ConfigTerminal::sizeTerminal.getX() - 20, 5}, "Познокомимся?");

  terminal_print(15, 12, "Input your name: ");
  terminal_print(15, 13, "Больше 4 букв и без пробелов");

  terminal_print(ConfigTerminal::sizeTerminal.getX() - 30, ConfigTerminal::sizeTerminal.getY() - 10,
                 "                 {\\__/} \n"
                 "введи свое имя   (●_● ) \n"
                 "без пробелов pls (< < )");
}
InputNameScene::InputNameScene(Context *const context, SceneManager *sceneManager) : Scene(context, sceneManager) {}
