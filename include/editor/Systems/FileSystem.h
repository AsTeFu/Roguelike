//
// Created by  on 22.08.2019.
//

#ifndef INCLUDE_EDITOR_SYSTEMS_FILESYSTEM_H_
#define INCLUDE_EDITOR_SYSTEMS_FILESYSTEM_H_

#include <editor/Components/FileNameComponent.h>
#include <string>
#include <utility>
#include "ecs/ISystem.h"

class FileSystem : public ISystem {
 private:
  Vector2 _position;
  int _currentPos{};
  int _currentFile{};
  int _maxDisplayFile{10};
  const std::string _roomsPath;

  void selectFile(const Entity *entity) const;
  void saveFile(const Entity *entity) const;
  void newFile(const Entity *entity);

 protected:
  void update(Entity *entity) override;
  void postUpdate(Entity *entity) override;

 public:
  FileSystem(EntityManager *const entityManager, SystemManager *const systemManager, SceneManager *const sceneManager,
             const Vector2 &position, std::string path)
      : ISystem(entityManager, systemManager, sceneManager), _position(position), _roomsPath(std::move(path)) {
    updateComponents();
  }
  bool filter(Entity *entity) const override;
  void deleteFile(const Entity *entity);
};

#endif  // INCLUDE_EDITOR_SYSTEMS_FILESYSTEM_H_
