//
// Created by AsTeFu on 22.07.2019.
//

#ifndef INCLUDE_GAME_SCENES_SCENEMANAGER_H_
#define INCLUDE_GAME_SCENES_SCENEMANAGER_H_

#include <game/Utility/DTO/ObjectDTO.h>
#include <map>
#include <memory>
#include <string>
#include <typeindex>
#include "utilities/Vector2.h"

#define menuScene "Menu"
#define gameScene "Game"
#define inputnameScene "InputName"
#define specialScene "Special"
#define abilityScene "Ability"
#define chestScene "Chest"
#define shopScene "Shop"
#define backpackScene "Backpack"
#define gameOverScene "GameOver"
#define editorScene "Editor"
#define settingScene "Setting"

class Scene;
class Context;

class SceneManager {
 private:
  Scene* _currentScene;
  std::map<std::string, std::unique_ptr<Scene>> _scenes;
  Context* _context;

 public:
  explicit SceneManager(Context* context);
  void update();  // Вызывается у текущей сцены пря налиции ввода
  void start();   // Вызывается один раз при переходе на сцену
  void end();     // Вызывается один раз при выходе со сцены
  void render();  // Вызывается сразу после update

  void addScene(const std::string& nameScene, Scene* scene);
  void switchScene(const std::string& nameScene);
  Context* getContext() const;
};

class Scene {
 private:
  SceneManager* _sceneManager;

 protected:
  Context* const _context;

 public:
  explicit Scene(Context* const context, SceneManager* sceneManager) : _sceneManager(sceneManager), _context(context) {}
  virtual ~Scene() = default;
  virtual void update(SceneManager* sceneManager) {}
  virtual void start(SceneManager* sceneManager) {}
  virtual void end(SceneManager* sceneManager) {}
  virtual void render() {}
};

class Context {
 private:
  std::map<std::type_index, std::unique_ptr<ObjectDTO>> _dtoObjects;

 public:
  template<typename TypeDTO, typename... Args>
  void addObject(Args&&... args) {
    _dtoObjects[typeid(TypeDTO)] = std::make_unique<TypeDTO>(std::forward<Args>(args)...);
  }
  template<typename TypeDTO>
  TypeDTO* getObject() const {
    auto dto = _dtoObjects.at(typeid(TypeDTO)).get();
    return dynamic_cast<TypeDTO*>(dto);
  }
};

#endif  // INCLUDE_GAME_SCENES_SCENEMANAGER_H_
