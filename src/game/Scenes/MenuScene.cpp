//
// Created by AsTeFu on 21.07.2019.
//

#include "game/Scenes/MenuScene.h"
#include <utilities/MathUtility.h>
#include <utilities/Terminal.h>
#include <algorithm>
#include "game/Scenes/SceneManager.h"
#include "game/Utility/Config.h"
#include "game/Utility/Input.h"

MenuScene::MenuScene(Context* context, SceneManager* sceneManager) : Scene(context, sceneManager), _currentElement(0) {
  _menuElements.insert(make_pair("Start", bind(&MenuScene::newGame, this, _1)));
  // _menuElements.insert(make_pair("Continue", bind(&MenuScene::continueGame, this, _1)));
  _menuElements.insert(make_pair("Editor", bind(&MenuScene::editor, this, _1)));
  _menuElements.insert(make_pair("Viewer", bind(&MenuScene::viewer, this, _1)));
  // _menuElements.insert(make_pair("Setting", bind(&MenuScene::setting, this, _1)));
  _menuElements.insert(make_pair("Exit", bind(&MenuScene::exit, this, _1)));

  // TODO(AsTeFu): я не придумал, как объединить мапу и вектор, так чтобы сохранился порядок в векторе.
  // Не могу создать мапу на основе вектора, а вектор на основе мапы теряет порядок
  _namesMenuElements = {"Start", "Editor", "Viewer", "Exit"};
}
void MenuScene::start(SceneManager* sceneManager) {
  position = {Config::getInstance().sizeTerminal.getX() / 2 - 10, Config::getInstance().sizeTerminal.getY() / 2 - 5};
  render();
}
void MenuScene::end(SceneManager* sceneManager) {}

void MenuScene::update(SceneManager* sceneManager) {
  if (Input::getKeyDown(KeyCode::UpArrow) || Input::getKeyDown(KeyCode::W)) upward();
  if (Input::getKeyDown(KeyCode::DownArrow) || Input::getKeyDown(KeyCode::S)) downward();
  if (Input::getKey(KeyCode::Enter)) enterMenuItem(sceneManager);
}
void MenuScene::downward() {
  _currentElement = MathUtility::clamp(_currentElement + 1, 0, _namesMenuElements.size() - 1);
}
void MenuScene::upward() {
  _currentElement = MathUtility::clamp(_currentElement - 1, 0, _namesMenuElements.size() - 1);
}

void MenuScene::enterMenuItem(SceneManager* sceneManager) {
  Terminal::clearArea({}, Config::getInstance().sizeTerminal);
  std::cout << "Menu element: " << _namesMenuElements[_currentElement] << std::endl;
  _menuElements[_namesMenuElements[_currentElement]](sceneManager);
}

void MenuScene::render() {
  Terminal::setLayer(_layer);
  Terminal::clearArea({}, Config::getInstance().sizeTerminal);
  Terminal::setColor(Color::White);

  drawPica();
  Terminal::print(position.getX(), position.getY() - 5, "Roguelike by ATF");

  int y = 0;
  for (const auto& name : _namesMenuElements) Terminal::print(position.getX(), position.getY() + y++, name);
  drawCursor();
}
void MenuScene::drawCursor() const {
  Terminal::print(position.getX() - static_cast<int>(cursor.size()) - 1, position.getY() + _currentElement, cursor);
}
void MenuScene::drawPica() const {
  Terminal::print(positionPica,
                  "{\\__/}\n"
                  "( ●_●) держи вкусняшку\n"
                  "( >>[color=green]*[/color])");
}

void MenuScene::newGame(SceneManager* sceneManager) {
  sceneManager->switchScene(inputnameScene);
}
void MenuScene::continueGame(SceneManager* sceneManager) {
  sceneManager->switchScene(inputnameScene);
}
void MenuScene::editor(SceneManager* sceneManager) {
  sceneManager->switchScene(editorScene);
}
void MenuScene::setting(SceneManager* sceneManager) {
  sceneManager->switchScene(settingScene);
}
void MenuScene::exit(SceneManager* sceneManager) {
  Terminal::close();
}
void MenuScene::viewer(SceneManager* sceneManager) {
  sceneManager->switchScene("Viewer");
}
