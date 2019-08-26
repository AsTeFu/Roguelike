//
// Created by AsTeFu on 22.07.2019.
//

#include "game/Scenes/SceneManager.h"
#include <BearLibTerminal.h>
#include <string>
#include "game/Scenes/MenuScene.h"
#include "game/Utility/Input.h"

SceneManager::SceneManager(Context* context) : _context(context) {}

void SceneManager::update() {
  _currState->update(this);
}
void SceneManager::start() {
  _currState->start(this);
}
void SceneManager::end() {
  _currState->end(this);
}
void SceneManager::render() {
  _currState->render();
}
void SceneManager::switchScene(const std::string& nameScene) {
  if (!_scenes.count(nameScene)) {
    std::cout << "[WARNING] Scene: " << nameScene << " doesn't exist!" << std::endl;
    return;
  }

  std::cout << "switch scene to " << nameScene << std::endl;
  _currState = _scenes.at(nameScene).get();
  start();
}
void SceneManager::addScene(const std::string& nameScene, Scene* scene) {
  _scenes[nameScene] = std::unique_ptr<Scene>(scene);
}
Context* SceneManager::getContext() const {
  return _context;
}
void Scene::drawHeader(const Vector2& position, const Vector2& size, const std::string& name) const {
  terminal_printf(position.getX() + size.getX() / 2 - name.length() / 2, position.getY() - 1 + size.getY() / 2,
                  name.c_str());

  horizontalBorder(position, size);
  verticalBorder(position, size);
}
void Scene::horizontalBorder(const Vector2& position, const Vector2& size) const {
  for (int i = 0; i < size.getX(); i++) {
    terminal_put(position.getX() + i, position.getY(), '=');
    terminal_put(position.getX() + i, position.getY() + size.getY() - 1, '=');
  }
}
void Scene::verticalBorder(const Vector2& position, const Vector2& size) const {
  for (int i = 1; i < size.getY() - 1; i++) {
    terminal_put(position.getX(), position.getY() + i, '|');
    terminal_put(position.getX() + size.getX() - 1, position.getY() + i, '|');
  }
}

void Scene::horizontalLine(const Vector2& position, const Vector2& size) const {
  for (int i = 0; i < size.getX(); i++) {
    terminal_put(position.getX() + i, position.getY(), '=');
  }
}
void Scene::verticalLine(const Vector2& position, const Vector2& size) const {
  for (int i = 1; i < size.getY() - 1; i++) {
    terminal_put(position.getX(), position.getY() + i, '|');
  }
}
