//
// Created by AsTeFu on 22.07.2019.
//
#include "game/Scenes/SettingScene.h"
#include <BearLibTerminal.h>
#include <utilities/Terminal.h>
#include <string>
#include "game/Scenes/MenuScene.h"
#include "game/Utility/Config.h"
#include "game/Utility/Input.h"

void SettingScene::update(SceneManager* sceneManager) {
  if (Input::getKey(KeyCode::Enter) || Input::getKey(KeyCode::Escape)) {
    Terminal::clearArea({}, Config::getInstance().sizeTerminal);
    sceneManager->switchScene(menuScene);
  }
}
void SettingScene::start(SceneManager* sceneManager) {}
void SettingScene::render() {
  Terminal::setLayer(3);
  Terminal::setColor(Color::White);

  Vector2 size(Config::getInstance().sizeTerminal.getX() - 20, 3);
  Vector2 position(10, 3);
  // drawHeader(position, size, "Setting");

  std::string message1 = "Напиши, чтобы ты хотел здесь настроить в гугл форму";
  std::string message2 = "Back (Enter or Escape)";
  Terminal::print(position.getX() + size.getX() / 2 - message1.size() / 4 + 1, position.getY() + 4, message1);
  Terminal::print(position.getX() + size.getX() / 2 - message2.size(), position.getY() + 5, message2);
}
SettingScene::SettingScene(Context* const context, SceneManager* sceneManager) : Scene(context, sceneManager) {}
