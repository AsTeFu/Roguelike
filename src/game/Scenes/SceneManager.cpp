//
// Created by AsTeFu on 22.07.2019.
//

#include "game/Scenes/SceneManager.h"
#include <string>
#include "game/Scenes/MenuScene.h"
#include "game/Utility/Input.h"

SceneManager::SceneManager(Context* context) : _context(context) {}

void SceneManager::update() {
  _currentScene->update(this);
}
void SceneManager::start() {
  _currentScene->start(this);
}
void SceneManager::end() {
  _currentScene->end(this);
}
void SceneManager::render() {
  _currentScene->render();
}
void SceneManager::switchScene(const std::string& nameScene) {
  if (!_scenes.count(nameScene)) {
    std::cout << "[WARNING] Scene: " << nameScene << " doesn't exist!" << std::endl;
    return;
  }

  end();
  std::cout << "switch scene to " << nameScene << std::endl;
  _currentScene = _scenes.at(nameScene).get();
  start();
}
void SceneManager::addScene(const std::string& nameScene, Scene* scene) {
  _scenes[nameScene] = std::unique_ptr<Scene>(scene);
  if (_scenes.size() == 1) _currentScene = _scenes.at(nameScene).get();
}
Context* SceneManager::getContext() const {
  return _context;
}
