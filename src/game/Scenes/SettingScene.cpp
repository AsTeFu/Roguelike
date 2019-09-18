//
// Created by AsTeFu on 22.07.2019.
//
#include "game/Scenes/SettingScene.h"
#include <BearLibTerminal.h>
#include <game/Scenes/SceneRenderUtility.h>
#include <game/Utility/DTO/RenderModeDTO.h>
#include <utilities/Terminal.h>
#include <string>
#include "game/Scenes/MenuScene.h"
#include "game/Utility/Config.h"
#include "game/Utility/Input.h"

void SettingScene::update(SceneManager* sceneManager) {
  if (Input::getKeyDown(KeyCode::Escape)) {
    Terminal::clearArea({}, Config::getInstance().sizeTerminal);
    sceneManager->getContext()->getObject<RenderModeDTO>()->mode = mode;
    sceneManager->switchScene(menuScene);
  }
  if (Input::getKeyDown(KeyCode::Enter)) {
    mode = !mode;
  }
}
void SettingScene::start(SceneManager* sceneManager) {
  sceneManager->getContext()->addObject<RenderModeDTO>(false);
}
void SettingScene::render() {
  Terminal::setColor(Color::White);

  Vector2 size(Config::getInstance().sizeTerminal.getX() - 20, 4);
  Vector2 position(10, 3);
  SceneRenderUtility::drawHeader(position, size, "Setting");

  int x = position.getX() + 5;
  int y = position.getY() + size.getY() + 3;

  if (mode)
    Terminal::printf(x, y, "Mode of graphic [[X]]");
  else
    Terminal::printf(x, y, "Mode of graphic [[ ]]");
}
SettingScene::SettingScene(Context* const context, SceneManager* sceneManager) : Scene(context, sceneManager) {
  sceneManager->getContext()->addObject<RenderModeDTO>(mode);
}
