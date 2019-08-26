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
#include "game/Utility/Vector2.h"

class Scene;
class Context;

class SceneManager {
 private:
  Scene* _currState;
  std::map<std::string, std::unique_ptr<Scene>> _scenes;
  Context* _context;

 public:
  explicit SceneManager(Context* context);
  void update();
  void start();
  void end();
  void render();

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
  void drawHeader(const Vector2& position, const Vector2& size, const std::string& name) const;
  void verticalBorder(const Vector2& position, const Vector2& size) const;
  void horizontalBorder(const Vector2& position, const Vector2& size) const;
  void horizontalLine(const Vector2& position, const Vector2& size) const;
  void verticalLine(const Vector2& position, const Vector2& size) const;

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
