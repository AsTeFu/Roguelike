//
// Created by AsTeFu on 22.07.2019.
//

#include "game/Scenes/GameScene.h"
#include <BearLibTerminal.h>
#include <game/Utility/DTO/NameDTO.h>
#include <game/Utility/Input.h>

void GameScene::update(SceneManager* sceneManager) {
  if (Input::getKeyDown(KeyCode::Escape) && Input::check(KeyCode::CTRL)) sceneManager->switchScene(menuScene);

  _windowsManager.update(&roomManager);
}
void GameScene::start(SceneManager* sceneManager) {
  // terminal_set("input.filter = [keyboard+]");
  _windowsManager.start();

  roomManager.start();
  // roomManager.addName(sceneManager->getContext()->getObject<NameDTO>()->name);
  // roomManager.addSpecial(*sceneManager->getContext()->getObject<SpecialDTO>());

  _windowsManager.update(&roomManager);
}
void GameScene::end(SceneManager* sceneManager) {
  // game.end(sceneManager);
}
void GameScene::render() {
  // _windowsManager.update();
}
void GameScene::newGame() {
  // game.newGame();
}

void GameScene::continueGame() {
  // game.continueGame();
}
void GameScene::setSpicial(const Special& special) {
  // game.setSpecial(special);
}
